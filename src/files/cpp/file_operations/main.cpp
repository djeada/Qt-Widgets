#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QString>
#include <stdexcept>

void createDir(QString path, QString name) {
  QDir dir(path);
  if (!dir.exists(name)) {
    if (!dir.mkdir(name)) {
      throw std::runtime_error("Cannot create directory");
    }
    qDebug() << "Directory created successfully";

  } else {
    qDebug() << "Directory already exists";
  }
}

void removeDir(QString path, QString name) {
  QDir dir(path);
  if (dir.exists(name)) {
    if (!dir.rmdir(name)) {
      throw std::runtime_error("Cannot remove directory");
    }
    qDebug() << "Directory removed successfully";

  } else {
    qDebug() << "Directory does not exist";
  }
}

void renameDir(QString path, QString oldName, QString newName) {

  QDir dir(path);

  if (dir.exists(oldName)) {
      QString oldPathAbsolute = dir.absolutePath() + "/" + oldName;

      // check if it exists 
      if (!QFileInfo(oldPathAbsolute).isDir()) {
        throw std::runtime_error("Dir does not exist");
      }

      QString newPathAbsolute = dir.absolutePath() + "/" + newName;

      // check if it exists
      if (QFileInfo(newPathAbsolute).isDir()) {
        throw std::runtime_error("New name is already in use");
      }

    if (!dir.rename(oldName, newName)) {
      throw std::runtime_error("Cannot rename dir");
    }
    qDebug() << "Dir renamed successfully";

  } else {
    qDebug() << "Directory does not exist";
  }
}

void createFile(QString path, QString name, QVector<QString> content) {
  QDir dir(path);
  if (!dir.exists(name)) {
    QFile file(path + "/" + name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      throw std::runtime_error("Cannot create file");
    }
    QTextStream out(&file);
    for (int i; i < content.size(); i++) {
      out << content[i] << '\n';
    }
    file.close();
    qDebug() << "File created successfully";

  } else {
    qDebug() << "File already exists";
  }
}

void removeFile(QString path, QString name) {
  QDir dir(path);
  if (dir.exists(name)) {
    if (!dir.remove(name)) {
      throw std::runtime_error("Cannot remove file");
    }
    qDebug() << "File removed successfully";

  } else {
    qDebug() << "File does not exist";
  }
}

auto main(int argc, char *argv[]) -> int {

  QString path = QDir::tempPath();
  QString dir_name = "test_dir";
  QString new_dir_name = "new_test_dir";
  QString file_name = "test_file_1";
  QString file_name_2 = "test_file_2";
  QVector<QString> content = {"Hello", "World"};

  try {
    createDir(path, dir_name);
    renameDir(path, dir_name, new_dir_name);

    auto new_path = path + QDir::separator() + new_dir_name;

    createFile(new_path, file_name, content);
    createFile(new_path, file_name_2, content);

    removeFile(new_path, file_name);
    removeFile(new_path, file_name_2);

    removeDir(path, new_dir_name);
  } catch (std::runtime_error &e) {
    qDebug() << e.what();
  }
}
