#include "file_dir_model.h"
#include <QDebug>

FileDirModel::FileDirModel(QObject *parent) : QFileSystemModel(parent)
{
}


FileDirModel::~FileDirModel()
{
}

void FileDirModel::setRootPath(const QString &path)
{
    QFileSystemModel::setRootPath(path);

}
