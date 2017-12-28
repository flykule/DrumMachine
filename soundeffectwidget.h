#ifndef SOUNDEFFECTWIDGET_H
#define SOUNDEFFECTWIDGET_H

#include <QSoundEffect>
#include <QWidget>

namespace Ui {
class SoundEffectWidget;
}

class SoundEffectWidget : public QWidget {
  Q_OBJECT

public:
  explicit SoundEffectWidget(QWidget *parent = 0);
  ~SoundEffectWidget();

  Qt::Key triggerKey() const;
  void setTriggerKey(const Qt::Key &triggerKey);

  void setSoundEffectName(const QString &name);

  void setSoundEffect(const QString &effectPath);

public slots:
  void triggerPlayButton();
  void play();

private:
  Ui::SoundEffectWidget *ui;
  QString soundName;
  Qt::Key mTriggerKey;
  QSoundEffect mSoundEffect;
};

#endif // SOUNDEFFECTWIDGET_H
