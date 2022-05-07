#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>

void displaySubDirInfo(QDir rootDir) {
  qDebug() << "Following subdirs found in : " << rootDir.absolutePath();
  auto dirs = rootDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

  for (auto &dir : dirs) {
    qDebug() << dir.fileName();
  }
}

void displayChildFilesInfo(QDir rootDir) {
  qDebug() << "Following files found in : " << rootDir.absolutePath();
  auto files = rootDir.entryInfoList(QDir::Files);

  for (auto &file : files) {
    qDebug() << "Name: " << file.fileName();
    qDebug() << "Size: " << file.size();
    qDebug() << "Created: " << file.birthTime();
    qDebug() << "Modified: " << file.lastModified();
  }
}

void displayFileInfo(QString path) {

  QDir rootDir(path);

  displaySubDirInfo(rootDir);
  displayChildFilesInfo(rootDir);
}

auto main(int argc, char *argv[]) -> int {

  // displayFileInfo(QDir::tempPath());
  displayFileInfo(QDir::homePath());
}
