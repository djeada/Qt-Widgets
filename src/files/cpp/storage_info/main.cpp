#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QStorageInfo>

void displaySubDirInfo(QDir rootDir) {
  qDebug() << "Following subdirs found in : " << rootDir.absolutePath();
  auto dirs = rootDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

  for (auto &dir : dirs) {
    qDebug() << dir.fileName();
  }
}

void displayStorageInfo(QStorageInfo storageInfo) {
  qDebug() << "Root: " << storageInfo.isRoot();
  qDebug() << "Device: " << storageInfo.device();
  qDebug() << "Name: " << storageInfo.displayName();
  qDebug() << "Type: " << storageInfo.fileSystemType();
  qDebug() << "Total space: " << storageInfo.bytesTotal() / 1024 / 1024 << "MB";
  qDebug() << "Available space: " << storageInfo.bytesAvailable() / 1024 / 1024
           << "MB";
}

auto main(int argc, char *argv[]) -> int {

  auto volumes = QStorageInfo::mountedVolumes();
  for (auto &volume : volumes) {
    displayStorageInfo(volume);
  }

  auto root = QStorageInfo::root();
  displaySubDirInfo(root.rootPath());
}
