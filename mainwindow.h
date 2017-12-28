#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "playbackworker.h"
#include "track.h"
#include <QMainWindow>
#include <QThread>

class SoundEffectWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  bool eventFilter(QObject *watched, QEvent *event) override;
private slots:
  void playSoundEffect(int soundId);
  void clearPlayback();
  void stopPlayback();

private:
  void startPlayback();

private:
  Ui::MainWindow *ui;
  QVector<SoundEffectWidget *> mSoundEffectWidgets;
  PlaybackWorker *mPlaybackWorker;
  QThread *mPlaybackThread;
  Track mTrack;
};

#endif // MAINWINDOW_H
