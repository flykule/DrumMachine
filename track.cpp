#include "track.h"

Track::Track(QObject *parent)
    : QObject(parent), mDuration(), mSoundEvents(), mTimer(), mState(),
      mPreviousState() {}

Track::~Track() {}

Track::State Track::state() const { return mState; }

void Track::setState(const State &state) {
  setPreviousState(mState);
  mState = state;
  emit stateChanged(state);
}

Track::State Track::previousState() const { return mPreviousState; }

void Track::setPreviousState(const State &previousState) {
  mPreviousState = previousState;
}

qint64 Track::duration() const { return mDuration; }

const std::vector<std::unique_ptr<SoundEvent>> &Track::soundEvents() const {
  return mSoundEvents;
}

quint64 Track::elapsedTime() const { return mTimer.elapsed(); }

void Track::play() {
  setState(Track::State::PLAYING);
  mTimer.start();
}

void Track::record() {
  clearSoundEvents();
  setState(Track::State::RECORDING);
  mTimer.start();
}

void Track::stop() {
  if (mState == Track::State::RECORDING) {
    mDuration = mTimer.elapsed();
  }
  setState(Track::State::STOPPED);
}

void Track::addSountEvent(int soundEventId) {
  if (mState != Track::State::RECORDING) {
    return;
  }
  mSoundEvents.push_back(
      std::make_unique<SoundEvent>(mTimer.elapsed(), soundEventId));
}

void Track::clear() {
  mSoundEvents.clear();
  mDuration = 0;
}

void Track::clearSoundEvents() { mSoundEvents.clear(); }

QVariant Track::toVariant() const {
  QVariantMap map;
  map.insert("duration", mDuration);

  QVariantList list;
  for (const auto &soundEvent : mSoundEvents) {
    list.append(soundEvent->toVariant());
  }
  map.insert("soundEvents", list);
  return map;
}

void Track::fromVariant(const QVariant &variant) {
  QVariantMap map = variant.toMap();
  mDuration = map.value("duration").toLongLong();

  QVariantList list = map.value("soundEvents").toList();
  for (const QVariant &data : list) {
    auto soundEvent = std::make_unique<SoundEvent>();
    soundEvent->fromVariant(data);
    mSoundEvents.push_back(std::move(soundEvent));
  }
}
