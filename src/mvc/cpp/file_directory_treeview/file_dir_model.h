#ifndef TREEMODEL_H
#define TREEMODEL_H
#include <QFileSystemModel>

class FileDirModel : public QFileSystemModel {
  Q_OBJECT

public:
  FileDirModel(QObject *parent = 0);
  ~FileDirModel();
  void setRootPath(const QString &path);
  QModelIndex mkdir(const QModelIndex &parent, const QString &name);
  bool touch(const QModelIndex &index, const QString &name);
  bool paste(const QModelIndex &index, const QString &path);
  bool appendToDestination(QModelIndex sourceIndex,
                           QModelIndex destinationIndex);

private:
  QModelIndex firstDirAncestor(const QModelIndex &index);
  static QString getUniqueName(const QString &dirPath, const QString &name);
  static bool copyFile(const QString &sourcePath, const QString &destPath);
  static bool copyDirectory(const QString &sourcePath, const QString &destPath);
};
#endif // TREEMODEL_H
