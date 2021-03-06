#ifndef SOUNDEVENT_H
#define SOUNDEVENT_H

#include "serializable.h"
#include <QMetaType>
#include <QtGlobal>

class SoundEvent : public Serializable {
public:
  SoundEvent(qint64 timestamp = 0, int soundId = 0);
  ~SoundEvent();

  qint64 timestamp;
  int soundId;

  // Serializable interface
public:
  QVariant toVariant() const override;
  void fromVariant(const QVariant &variant) override;
};

Q_DECLARE_METATYPE(SoundEvent)
#endif // SOUNDEVENT_H
