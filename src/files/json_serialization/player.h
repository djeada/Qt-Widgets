#include "json_serializable_interface.h"
#include <QString>

class JsonSerializableInterface;

class Player : public JsonSerializableInterface {

private:
  QString name;
  int score;

public:
  Player(QString name, int score);
  Player(const Player &other);
  Player();
  Player &operator=(const Player &other);
  virtual ~Player();

  QString getName() const;
  int getScore() const;

  virtual void toJson(QJsonObject &root) const;
  virtual void fromJson(const QJsonObject &root);

  bool operator==(const Player &other) const;
  friend QDebug operator<<(QDebug dbg, const Player &player);
};
