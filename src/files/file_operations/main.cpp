#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QString>
#include <QFileInfo>
#include <stdexcept>

void createDir(QString path, QString name)
{
    QDir dir(path);
    if (!dir.exists(name))
    {
        if(!dir.mkdir(name))
        {
            throw std::runtime_error("Cannot create directory");
        }
        else {
            qDebug() << "Directory created successfully";
        }
    }
    else {
        qDebug() << "Directory already exists";
    }
}

void removeDir(QString path, QString name)
{
    QDir dir(path);
    if (dir.exists(name))
    {
        if(!dir.rmdir(name))
        {
            throw std::runtime_error("Cannot remove directory");
        }
        else {
            qDebug() << "Directory removed successfully";
        }
    }
    else {
        qDebug() << "Directory does not exist";
    }
}

void renameDir(QString path, QString oldName, QString newName)
{
    QDir dir(path);
    if (dir.exists(oldName))
    {
        if(!dir.rename(oldName, newName))
        {
            throw std::runtime_error("Cannot rename directory");
        }
        else {
            qDebug() << "Directory renamed successfully";
        }
    }
    else {
        qDebug() << "Directory does not exist";
    }
}


void createFile(QString path, QString name, QVector<QString> content)
{
    QDir dir(path);
    if (!dir.exists(name))
    {
        QFile file(path + "/" + name);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            throw std::runtime_error("Cannot create file");
        }
        else {
            QTextStream out(&file);
            for (int i = 0; i < content.size(); i++)
            {
                out << content[i] << '\n';
            }
            file.close();
            qDebug() << "File created successfully";
        }
    }
    else {
        qDebug() << "File already exists";
    }
}

void removeFile(QString path, QString name)
{
    QDir dir(path);
    if (dir.exists(name))
    {
        if(!dir.remove(name))
        {
            throw std::runtime_error("Cannot remove file");
        }
        else {
            qDebug() << "File removed successfully";
        }
    }
    else {
        qDebug() << "File does not exist";
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

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

        removeDir(path, dir_name);
    }
    catch (std::runtime_error &e)
    {
        qDebug() << e.what();
    }

    return a.exec();
}
