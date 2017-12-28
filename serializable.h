#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QVariant>

class Serializable {
public:
  virtual ~Serializable() {}
  virtual QVariant toVariant() const = 0;
  virtual void fromVariant(const QVariant &variant) = 0;
};
#endif // SERIALIZER_H
