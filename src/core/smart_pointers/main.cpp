#include <QCoreApplication>
#include <QDebug>
#include <QObject>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto obj = new QObject;

    //It will be automatically set to nullptr if the pointed to object is destroyed.
    QPointer<QObject> ptr = nullptr;
    qDebug() << "ptr value: " << ptr;

    ptr =  QPointer<QObject>(obj);
    qDebug() << "ptr value: " << ptr;

    ptr->setObjectName("test");
    qDebug() << "ptr value: " << ptr;
    qDebug() << "obj value: " << obj;

    QPointer<QObject> childPtr(new QObject(obj));
    qDebug() << "childPtr value: " << ptr;
    qDebug() << "child obj parent: " << childPtr->parent();

    // remove the parent
    // see what happens to the child
    delete obj; // don't try it at home

    qDebug() << ptr;
    qDebug() << childPtr;

    auto obj2 = new QObject;
    QSharedPointer<QObject> sharedPtr1(obj2);
    //QSharedPointer<QObject> sharedPtr2(obj2); <- bad
    QSharedPointer<QObject> sharedPtr2(sharedPtr1);
    qDebug() << "sharedPtr1 value: " << sharedPtr1;
    qDebug() << "sharedPtr2 value: " << sharedPtr2;
    qDebug() << "obj2 value: " << obj2;

    // shared pointers point to the same object but are not the same object
    // if one get's cleared, the other won't
    sharedPtr1.clear();
    qDebug() << "sharedPtr1 value: " << sharedPtr1 << sharedPtr1.isNull();
    qDebug() << "sharedPtr2 value: " << sharedPtr2 << sharedPtr2.isNull();
    qDebug() << "obj2 value: " << obj2;

    sharedPtr2.clear();
    qDebug() << "sharedPtr1 value: " << sharedPtr1 << sharedPtr1.isNull();
    qDebug() << "sharedPtr2 value: " << sharedPtr2 << sharedPtr2.isNull();
    qDebug() << "obj2 value: " << obj2;

    // weak pointers are like shared pointers but they don't prevent the object from being destroyed
    // and they can only be created from a shared pointer
    sharedPtr1 = QSharedPointer<QObject>(new QObject);
    QWeakPointer<QObject> weakPtr1(sharedPtr1);
    qDebug() << "weakPtr1 value: " << weakPtr1.isNull();

    sharedPtr1.clear();
    qDebug() << "weakPtr1 value: " << weakPtr1.isNull();
    qDebug() << "sharedPtr1 value: " << sharedPtr1;
    
    return a.exec();
}
