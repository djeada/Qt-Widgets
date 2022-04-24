#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDateTime>
#include <QDebug>


void displaySubDirInfo(QDir rootDir) {
    qDebug() << "Following subdirs found in : " << rootDir.absolutePath();
    auto dirs = rootDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(auto& dir : dirs) {
        qDebug() << dir.fileName();
    }
}

void displayChildFilesInfo(QDir rootDir) {
    qDebug() << "Following files found in : " << rootDir.absolutePath();
    auto files = rootDir.entryInfoList(QDir::Files);

    for(auto& file : files) {
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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //displayFileInfo(QDir::tempPath());
    displayFileInfo(QDir::homePath());

    return a.exec();
}
