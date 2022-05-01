#ifndef _HOME_ADAM_QT_WIDGETS_SRC_FILES_JSON_SERIALIZATION_JSON_SERIALIZABLE_INTERFACE_H
#define _HOME_ADAM_QT_WIDGETS_SRC_FILES_JSON_SERIALIZATION_JSON_SERIALIZABLE_INTERFACE_H

#include <QJsonObject>

class JsonSerializableInterface {
public:
  virtual void toJson(QJsonObject &root) const;
  virtual void fromJson(const QJsonObject &root);
};
#endif
