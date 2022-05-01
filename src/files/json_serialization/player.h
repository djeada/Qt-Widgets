#ifndef _HOME_ADAM_QT_WIDGETS_SRC_FILES_JSON_SERIALIZATION_PLAYER_H
#define _HOME_ADAM_QT_WIDGETS_SRC_FILES_JSON_SERIALIZATION_PLAYER_H

#include "json_serializable_interface.h"
#include <QString>

class Player : public JsonSerializableInterface {

private:
  QString name;
  int score;

public:
  Player(QString name, int score);
  Player(const Player &other);
  Player();
  auto operator=(const Player &other) -> Player &;
  virtual ~Player();

  QString getName() const;
  auto getScore() const -> int;

  virtual void toJson(QJsonObject &root) const;
  virtual void fromJson(const QJsonObject &root);

  auto operator==(const Player &other) const -> bool;
  friend QDebug operator<<(QDebug dbg, const Player &player);
};

#endif
