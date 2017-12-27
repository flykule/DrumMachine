#ifndef TRACK_H
#define TRACK_H

#include <QElapsedTimer>
#include <QObject>
#include <QVector>
#include <memory>
#include <vector>

#include "soundevent.h"

class Track : public QObject {
  Q_OBJECT

public:
  enum class State {
    STOPPED,
    PLAYING,
    RECORDING,
  };

  explicit Track(QObject *parent = 0);
  ~Track();

  State state() const;
  void setState(const State &state);

  State previousState() const;
  void setPreviousState(const State &previousState);

  qint64 duration() const;

  const std::vector<std::unique_ptr<SoundEvent>> &soundEvents() const;

  quint64 elapsedTime() const;
signals:
  void stateChanged(State state);

public slots:
  void play();
  void record();
  void stop();
  void addSountEvent(int soundEventId);

private:
  void clear();
  //  void setState(Track::State state);
  void clearSoundEvents();

private:
  qint64 mDuration;
  std::vector<std::unique_ptr<SoundEvent>> mSoundEvents;
  QElapsedTimer mTimer;
  State mState;
  State mPreviousState;
};

#endif // TRACK_H
