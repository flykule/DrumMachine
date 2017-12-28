#include "soundeffectwidget.h"
#include "ui_soundeffectwidget.h"

SoundEffectWidget::SoundEffectWidget(QWidget *parent)
    : QWidget(parent), mSoundEffect(), ui(new Ui::SoundEffectWidget) {
  ui->setupUi(this);
  ui->nameLabel->setText(soundName);
  connect(ui->playButton, &QPushButton::clicked, this,
          &SoundEffectWidget::play);
}

SoundEffectWidget::~SoundEffectWidget() { delete ui; }

Qt::Key SoundEffectWidget::triggerKey() const { return mTriggerKey; }

void SoundEffectWidget::setTriggerKey(const Qt::Key &triggerKey) {
  mTriggerKey = triggerKey;
}

void SoundEffectWidget::setSoundEffectName(const QString &name) {
  ui->nameLabel->setText(name);
}

void SoundEffectWidget::triggerPlayButton() { ui->playButton->animateClick(); }

void SoundEffectWidget::play() {
  if (mSoundEffect.source().isEmpty()) {
    return;
  }
  mSoundEffect.setVolume(1.0);
  mSoundEffect.play();
}

void SoundEffectWidget::setSoundEffect(const QString &resource) {
  if (resource.isEmpty()) {
    return;
  }
  QUrl localQUrl(resource);
  mSoundEffect.setSource(localQUrl);
}
