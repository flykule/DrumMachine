#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H
#include "serializer.h"

class QXmlStreamWriter;
class QXmlStreamReader;

class XmlSerializer : public Serializer {
public:
  XmlSerializer();

  // Serializer interface
public:
  void save(const Serializable &serializable, const QString &filepath,
            const QString &rootName);
  void load(Serializable &serializable, const QString &filepath);

private:
  // helper method to read
  QVariant readVariantFromStream(QXmlStreamReader &stream);

  QVariant readVariantListFromStream(QXmlStreamReader &stream);
  QVariant readVariantMapFromStream(QXmlStreamReader &stream);
  QVariant readVariantValueFromStream(QXmlStreamReader &stream);

  void writerVariantToStream(const QString &nodeNmae, const QVariant &variant,
                             QXmlStreamWriter &stream);

  void writerVariantValueToStream(const QVariant &variant,
                                  QXmlStreamWriter &stream);
  void writerVariantListToStream(const QVariant &variant,
                                 QXmlStreamWriter &stream);
  void writerVariantMapToStream(const QVariant &variant,
                                QXmlStreamWriter &stream);
};

#endif // XMLSERIALIZER_H
