#ifndef SOUNDEVENT_H
#define SOUNDEVENT_H

#include <QMetaType>
#include <QtGlobal>

class SoundEvent {
public:
  SoundEvent(qint64 timestamp = 0, int soundId = 0);
  ~SoundEvent();

  qint64 timestamp;
  int soundId;
};

Q_DECLARE_METATYPE(SoundEvent)
#endif // SOUNDEVENT_H
