#ifndef TREEMODEL_H
#define TREEMODEL_H
#include <QFileSystemModel>

class FileDirModel : public QFileSystemModel
{
    Q_OBJECT

    public:
        FileDirModel(QObject *parent = 0);
        ~FileDirModel();
        void setRootPath(const QString &path);
};
#endif // TREEMODEL_H
