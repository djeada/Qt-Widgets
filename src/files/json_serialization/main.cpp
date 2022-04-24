#include "player.h"
#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  Player player("John", 100);
  QJsonObject root;
  player.toJson(root);
  qDebug() << root;

  QString path = "player.json";
  QFile file(path);
  if (!file.open(QIODevice::WriteOnly)) {
    qDebug() << "Could not open file for writing";
    return 1;
  }
  QJsonDocument doc(root);
  file.write(doc.toJson());
  file.close();

  // open file and read json
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Could not open file for reading";
    return 1;
  }

  QByteArray data = file.readAll();
  QJsonDocument doc2 = QJsonDocument::fromJson(data);
  QJsonObject root2 = doc2.object();
  file.close();

  Player player2;
  player2.fromJson(root2);
  qDebug() << player2;
  qDebug() << (player == player2);

  // remove temp file
  QFile::remove(path);

  return a.exec();
}
