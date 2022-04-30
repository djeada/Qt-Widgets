#include <QCoreApplication>
#include <QDebug>
#include <QList>
#include <QObject>

void fillList(QList<QObject *> &list, int size) {
  list.clear();
  for (int i = 0; i < size; i++) {
    auto obj = new QObject();
    obj->setObjectName(QString("obj%1").arg(i));
    list.append(obj);
  }
}

void displayList(QList<QObject *> &list) {
  qDebug() << "List:";
  for (auto obj : list) {
    qDebug() << obj->objectName();
  }
}

auto findObject(QList<QObject *> &list, QString name) -> int {
  int index = -1;
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i)->objectName() == name) {
      index = i;
      break;
    }
  }
  return index;
}

void deleteObject(QList<QObject *> &list, QString name) {
  int index = 0 = findObject(list, name);
  if (index != -1) {
    delete list.at(index);
    list.removeAt(index);
  }
}

auto main(int /*argc*/, char * /*argv*/[]) -> int {

  QList<QObject *> list;
  fillList(list, 10);
  displayList(list);

  deleteObject(list, "obj5");
  displayList(list);

  qDebug() << "Index of obj3: " << findObject(list, "obj3");
  qDebug() << "Index of obj5: " << findObject(list, "obj5");

  qDebug() << "List size: " << list.size();

  qDeleteAll(list); // delete all objects in list
  qDebug() << "List size: "
           << list.size(); // the objects are still in the list, but the
                           // pointers are invalid

  list.clear();
  qDebug() << "List size: "
           << list.size(); // the objects are deleted, the list is empty
  return 0;
}
