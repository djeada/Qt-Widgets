#ifndef _HOME_ADAM_QT_WIDGETS_SRC_FILES_JSON_SERIALIZATION_JSON_SERIALIZABLE_INTERFACE_H
#define _HOME_ADAM_QT_WIDGETS_SRC_FILES_JSON_SERIALIZATION_JSON_SERIALIZABLE_INTERFACE_H

#include <QJsonObject>

class JsonSerializableInterface {
public:
  virtual void toJson(QJsonObject &root) const = 0;
  virtual void fromJson(const QJsonObject &root) = 0;
};
#endif
