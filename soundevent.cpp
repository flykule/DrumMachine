#include "soundevent.h"

SoundEvent::SoundEvent(qint64 timestamp, int soundId)
    : timestamp(timestamp), soundId(soundId) {}

SoundEvent::~SoundEvent() {}
