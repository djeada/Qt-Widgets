#include "file_dir_model.h"
#include <QDebug>
#include <regex>

FileDirModel::FileDirModel(QObject *parent) : QFileSystemModel(parent) {
  setReadOnly(false);
}

FileDirModel::~FileDirModel() {}

void FileDirModel::setRootPath(const QString &path) {
  QFileSystemModel::setRootPath(path);
}

QModelIndex FileDirModel::firstDirAncestor(const QModelIndex &index) {
  // check if index represents a directory if not climb up till we find one
  auto parentIndex = index;
  while (!isDir(parentIndex)) {
    parentIndex = parentIndex.parent();
  }
  return parentIndex;
}

QString FileDirModel::getUniqueName(const QString &dirPath,
                                    const QString &name) {
  auto uniqueName(name);
  if (uniqueName.isEmpty()) {
    uniqueName = "New File";
  }

  if (!QDir(dirPath).exists(uniqueName)) {
    return uniqueName;
  }

  uniqueName = uniqueName + " (1)";

  while (QFile::exists(dirPath + "/" + uniqueName)) {
    // extract the number from last parentheses using std::regex
    std::regex re("\\(([0-9]+)\\)$");
    std::string str(uniqueName.toStdString());
    std::smatch match;

    if (std::regex_search(str, match, re)) {
      auto number = std::stoi(match[1]);
      number++;
      // remove everything from the last occurrence of ( to the end
      uniqueName.replace(uniqueName.lastIndexOf("("), uniqueName.length(), "");
      uniqueName = uniqueName + "(" + QString::number(number) + ")";
    } else {
      uniqueName = uniqueName + " (1)";
    }
  }

  return uniqueName;
}

bool FileDirModel::touch(const QModelIndex &index, const QString &name) {
  auto parentIndex = firstDirAncestor(index);

  auto path = fileInfo(parentIndex).absoluteFilePath();
  auto newPath = path + "/" + getUniqueName(path, name);

  QFile file(newPath);
  if (!file.open(QIODevice::WriteOnly))
    return false;
  file.close();
  return true;
}

QModelIndex FileDirModel::mkdir(const QModelIndex &parent,
                                const QString &name) {
  // check if index represents a directory if not climb up till we find one
  auto parentIndex = firstDirAncestor(parent);

  auto path = fileInfo(parentIndex).absoluteFilePath();
  auto uniqueName = getUniqueName(path, name.isEmpty() ? "New Folder" : name);

  return QFileSystemModel::mkdir(parentIndex, uniqueName);
}

bool FileDirModel::copyFile(const QString &sourcePath,
                            const QString &destPath) {
  QFile sourceFile(sourcePath);
  QFile destFile(destPath);

  if (!sourceFile.open(QIODevice::ReadOnly)) {
    return false;
  }

  if (!destFile.open(QIODevice::WriteOnly)) {
    sourceFile.close();
    return false;
  }

  auto data = sourceFile.readAll();
  destFile.write(data);
  sourceFile.close();
  destFile.close();
  return true;
}

bool FileDirModel::copyDirectory(const QString &sourcePath,
                                 const QString &destPath) {
  QDir sourceDir(sourcePath);
  QDir destDir(destPath);

  if (!sourceDir.exists()) {
    return false;
  }

  if (!destDir.exists()) {
    destDir.mkpath(destPath);
  }

  auto files = sourceDir.entryInfoList(QDir::Files);
  for (auto &file : files) {
    auto destFilePath = destPath + "/" + file.fileName();
    if (!copyFile(file.absoluteFilePath(), destFilePath)) {
      return false;
    }
  }

  auto subDirs = sourceDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
  for (auto &subDir : subDirs) {
    auto destSubDirPath = destPath + "/" + subDir.fileName();
    if (!copyDirectory(subDir.absoluteFilePath(), destSubDirPath)) {
      return false;
    }
  }

  return true;
}

bool FileDirModel::paste(const QModelIndex &index, const QString &path) {
  // check if path exists
  if (!QFile::exists(path)) {
    return false;
  }

  // check if index represents a directory if not climb up till we find one
  auto parentIndex = firstDirAncestor(index);

  // if path represents a file copy a file to parentIndex
  if (QFileInfo(path).isFile()) {
    auto uniqueName = getUniqueName(fileInfo(parentIndex).absoluteFilePath(),
                                    QFileInfo(path).fileName());
    auto destPath = fileInfo(parentIndex).absoluteFilePath() + "/" + uniqueName;
    return copyFile(path, destPath);
  }

  // if path represents a directory copy a directory to parentIndex
  if (QFileInfo(path).isDir()) {
    auto uniqueName = getUniqueName(fileInfo(parentIndex).absoluteFilePath(),
                                    QFileInfo(path).fileName());
    auto destPath = fileInfo(parentIndex).absoluteFilePath() + "/" + uniqueName;
    return copyDirectory(path, destPath);
  }

  return false;
}
