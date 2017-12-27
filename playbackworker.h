#ifndef PLAYBACKWORKER_H
#define PLAYBACKWORKER_H

#include <QAtomicInteger>
#include <QObject>

class Track;

class PlaybackWorker : public QObject {
  Q_OBJECT
public:
  explicit PlaybackWorker(const Track &track, QObject *parent = 0);

signals:
  void playSound(int sountId);
  void trackFinished();

public slots:
  void play();
  void stop();

private:
  const Track &mTrack;
  QAtomicInteger<bool> mIsPlaying;
};

#endif // PLAYBACKWORKER_H
