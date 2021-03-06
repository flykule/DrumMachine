#include "playbackworker.h"
#include "track.h"
#include <QThread>

PlaybackWorker::PlaybackWorker(const Track &track, QObject *parent)
    : QObject(parent), mTrack(track) {}

void PlaybackWorker::play() {
  mIsPlaying.store(true);
  QElapsedTimer timer;
  size_t soundEventIndex = 0;
  const auto &soundEvents = mTrack.soundEvents();

  timer.start();
  while (timer.elapsed() <= mTrack.duration() && mIsPlaying.load()) {
    if (soundEventIndex < soundEvents.size()) {
      const auto &soundEvent = soundEvents.at(soundEventIndex);
      if (timer.elapsed() >= soundEvent->timestamp) {
        emit playSound(soundEvent->soundId);
        soundEventIndex++;
      }
    }
    QThread::msleep(1);
  }

  if (soundEventIndex >= soundEvents.size()) {
    emit trackFinished();
  }
}

void PlaybackWorker::stop() {}
