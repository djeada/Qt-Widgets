#include "player.h"

Player::Player(QString name, int score) : name(name), score(score) {}

Player::Player(const Player &other) : name(other.name), score(other.score) {}

Player::Player() : name(""), score(0) {}

auto Player::operator=(const Player &other) -> Player & {
  name = other.name;
  score = other.score;
  return *this;
}

Player::~Player() {}

QString Player::getName() const { return name; }

auto Player::getScore() const -> int { return score; }

void Player::toJson(QJsonObject &root) const {
  root["name"] = name;
  root["score"] = score;
}

void Player::fromJson(const QJsonObject &root) {
  name = root["name"].toString();
  score = root["score"].toInt();
}

QDebug operator<<(QDebug dbg, const Player &player) {
  dbg.nospace() << "Player(" << player.name << ", " << player.score << ")";
  return dbg.space();
}

auto Player::operator==(const Player &other) const -> bool {
  return name == other.name && score == other.score;
}