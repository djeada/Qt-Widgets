#include <QJsonObject>

class JsonSerializableInterface {
public:
  virtual void toJson(QJsonObject &root) const = 0;
  virtual void fromJson(const QJsonObject &root) = 0;
};