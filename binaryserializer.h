#ifndef BINARYSERIALIZER_H
#define BINARYSERIALIZER_H

#include "serializer.h"

class BinarySerializer : public Serializer {
public:
  BinarySerializer();

  // Serializer interface
public:
  void save(const Serializable &serializable, const QString &filepath,
            const QString &rootName);
  void load(Serializable &serializable, const QString &filepath);
};

#endif // BINARYSERIALIZER_H
