#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "serializer.h"

class JsonSerializer : public Serializer {
public:
  JsonSerializer();

  // Serializer interface
public:
  void save(const Serializable &serializable, const QString &filepath,
            const QString &rootName);
  void load(Serializable &serializable, const QString &filepath);
};

#endif // JSONSERIALIZER_H
