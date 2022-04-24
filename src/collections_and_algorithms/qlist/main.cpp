#include <QCoreApplication>
#include <QObject>
#include <QDebug>
#include <QList>

void fillList(QList<QObject*> &list, int size)
{
    list.clear();
    for (int i = 0; i < size; i++)
    {
        QObject *obj = new QObject();
        obj->setObjectName(QString("obj%1").arg(i));
        list.append(obj);
    }
}

void displayList(QList<QObject*> &list)
{
    qDebug() << "List:";
    for (auto obj : list)
    {
        qDebug() << obj->objectName();
    }
}

int findObject(QList<QObject*> &list, QString name)
{
    int index = -1;
    for (int i = 0; i < list.size(); i++)
    {
        if (list.at(i)->objectName() == name)
        {
            index = i;
            break;
        }
    }
    return index;
}

void deleteObject(QList<QObject*> &list, QString name)
{
    int index = findObject(list, name);
    if (index != -1)
    {
        delete list.at(index);
        list.removeAt(index);
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<QObject*> list;
    fillList(list, 10);
    displayList(list);

    deleteObject(list, "obj5");
    displayList(list);

    qDebug() << "Index of obj3: " << findObject(list, "obj3");
    qDebug() << "Index of obj5: " << findObject(list, "obj5");

    qDebug() << "List size: " << list.size();

    qDeleteAll(list); // delete all objects in list
    qDebug() << "List size: " << list.size(); // the objects are still in the list, but the pointers are invalid

    list.clear();
    qDebug() << "List size: " << list.size(); // the objects are deleted, the list is empty

    return a.exec();
}
