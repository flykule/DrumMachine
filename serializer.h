#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "serializable.h"

#include <QString>

class Serializer {
public:
  virtual ~Serializer() {}
  virtual void save(const Serializable &serializable, const QString &filepath,
                    const QString &rootName = "") = 0;
  virtual void load(Serializable &serializable, const QString &filepath) = 0;
};
#endif // SERIALIZER_H
