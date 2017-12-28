#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mSoundEffectWidgets(), mTrack(), mPlaybackThread(),
      mPlaybackWorker(), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->kickWidget->setSoundEffectName("KICK");
  ui->snareWidget->setSoundEffectName("SNARE");
  ui->hihatWidget->setSoundEffectName("HIHAT");
  ui->crashWidget->setSoundEffectName("CRASH");

  ui->kickWidget->setTriggerKey(Qt::Key_H);
  ui->snareWidget->setTriggerKey(Qt::Key_J);
  ui->hihatWidget->setTriggerKey(Qt::Key_K);
  ui->crashWidget->setTriggerKey(Qt::Key_L);

  ui->kickWidget->setSoundEffect("qrc:/sounds/kick.wav");
  ui->snareWidget->setSoundEffect("qrc:/sounds/snare.wav");
  ui->hihatWidget->setSoundEffect("qrc:/sounds/hihat.wav");
  ui->crashWidget->setSoundEffect("qrc:/sounds/crash.wav");

  mSoundEffectWidgets.push_back(ui->kickWidget);
  mSoundEffectWidgets.push_back(ui->snareWidget);
  mSoundEffectWidgets.push_back(ui->hihatWidget);
  mSoundEffectWidgets.push_back(ui->crashWidget);

  installEventFilter(this);
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    for (SoundEffectWidget *widget : mSoundEffectWidgets) {
      if (keyEvent->key() == widget->triggerKey()) {
        widget->triggerPlayButton();
        return true;
      }
    }
  }
  return QObject::eventFilter(watched, event);
}

void MainWindow::startPlayback() {
  clearPlayback();

  mPlaybackThread = new QThread();

  mPlaybackWorker = new PlaybackWorker(mTrack);
  mPlaybackWorker->moveToThread(mPlaybackThread);

  connect(mPlaybackThread, &QThread::started, mPlaybackWorker,
          &PlaybackWorker::play);
  connect(mPlaybackThread, &QThread::finished, mPlaybackWorker,
          &QObject::deleteLater);

  connect(mPlaybackWorker, &PlaybackWorker::playSound, this,
          &MainWindow::playSoundEffect);

  connect(mPlaybackWorker, &PlaybackWorker::trackFinished, &mTrack,
          &Track::stop);
  mPlaybackThread->start(QThread::HighPriority);
}
