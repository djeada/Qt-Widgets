#include <QCoreApplication>
#include <QObject>
#include <QDebug>
#include <QSet>

void fillSet(QSet<QObject*> &set, int size)
{
    for (int i = 0; i < size; ++i) {
        QObject *obj = new QObject;
        obj->setObjectName(QString("Obj%1").arg(i));
        set.insert(obj);
    }
}

void displaySet(const QSet<QObject*> &set)
{
    qDebug() << "Set:";
    foreach (QObject *obj, set) {
        qDebug() << obj->objectName();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSet<QObject*> set;
    fillSet(set, 10);
    displaySet(set); // not in order

    // what will happen if we insert the same object twice?
    QObject *obj = new QObject;
    obj->setObjectName("ObjX");
    set.insert(obj);
    set.insert(obj);
    displaySet(set); // not in order

    return a.exec();
}
