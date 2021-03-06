#include "xmlserializer.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

XmlSerializer::XmlSerializer() {}

void XmlSerializer::save(const Serializable &serializable,
                         const QString &filepath, const QString &rootName) {
  QFile file(filepath);
  QXmlStreamWriter stream(&file);
  stream.setAutoFormatting(true);
  writerVariantToStream(rootName, serializable.toVariant(), stream);
  stream.writeStartDocument();
  file.close();
}

void XmlSerializer::load(Serializable &serializable, const QString &filepath) {
  QFile file(filepath);
  file.open(QFile::ReadOnly);
  QXmlStreamReader stream(&file);
  stream.readNextStartElement();
  serializable.fromVariant(readVariantFromStream(stream));
}

QVariant XmlSerializer::readVariantFromStream(QXmlStreamReader &stream) {
  QXmlStreamAttributes attributes = stream.attributes();
  QString typeString = attributes.value("type").toString();

  QVariant variant;
  switch (QVariant::nameToType(typeString.toStdString().c_str())) {
  case QMetaType::QVariantList:
    variant = readVariantListFromStream(stream);
    break;
  case QMetaType::QVariantMap:
    variant = readVariantMapFromStream(stream);
    break;
  default:
    variant = readVariantValueFromStream(stream);
    break;
  }
  return variant;
}

QVariant XmlSerializer::readVariantListFromStream(QXmlStreamReader &stream) {
  QVariantList list;
  while (stream.readNextStartElement()) {
    list.append(readVariantFromStream(stream));
  }
  return list;
}

QVariant XmlSerializer::readVariantMapFromStream(QXmlStreamReader &stream) {
  QVariantMap map;
  while (stream.readNextStartElement()) {
    map.insert(stream.name().toString(), readVariantFromStream(stream));
  }
  return map;
}

QVariant XmlSerializer::readVariantValueFromStream(QXmlStreamReader &stream) {
  QXmlStreamAttributes attributes = stream.attributes();
  QString typeString = attributes.value("type").toString();
  QString dataString = stream.readElementText();

  QVariant variant(dataString);
  variant.convert(QVariant::nameToType(typeString.toStdString().c_str()));
  return variant;
}

void XmlSerializer::writerVariantToStream(const QString &nodeName,
                                          const QVariant &variant,
                                          QXmlStreamWriter &stream) {
  stream.writeStartElement(nodeName);
  stream.writeAttribute("type", variant.typeName());

  switch (variant.type()) {
  case QMetaType::QVariantList:
    writerVariantListToStream(variant, stream);
    break;
  case QMetaType::QVariantMap:
    writerVariantMapToStream(variant, stream);
    break;
  default:
    writerVariantValueToStream(variant, stream);
    break;
  }

  stream.writeEndElement();
}

void XmlSerializer::writerVariantValueToStream(const QVariant &variant,
                                               QXmlStreamWriter &stream) {
  stream.writeCharacters(variant.toString());
}

void XmlSerializer::writerVariantListToStream(const QVariant &variant,
                                              QXmlStreamWriter &stream) {
  QList<QVariant> list = variant.toList();

  for (const QVariant &element : list) {
    writerVariantToStream("item", element, stream);
  }
}

void XmlSerializer::writerVariantMapToStream(const QVariant &variant,
                                             QXmlStreamWriter &stream) {
  QMap<QString, QVariant> map = variant.toMap();
  QMapIterator<QString, QVariant> i(map);

  while (i.hasNext()) {
    i.next();
    writerVariantToStream(i.key(), i.value(), stream);
  }
}
