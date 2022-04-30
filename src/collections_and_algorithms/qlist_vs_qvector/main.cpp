#include <QCoreApplication>
#include <QDebug>
#include <QList>
#include <QObject>
#include <QVector>

template <typename T> void fillContainer(T &container, int size) {
  for (int i = 0; i < size; ++i) {
    auto obj = new QObject();
    obj->setObjectName(QString("Obj%1").arg(i));
    container.append(obj);
  }
}

template <class T> void displayDistances(T &container) {

  qDebug() << "Displaying distances for container " << container;

  for (int i = 1; i < container.length(); i++) {
    auto previous = reinterpret_cast<std::uintptr_t>(&container.at(i - 1));
    auto current = reinterpret_cast<std::uintptr_t>(&container.at(i));
    auto distance = current - previous;

    qDebug() << "Distance between " << i - 1 << " and " << i << " is "
             << distance;
  }
}

auto main(int /*argc*/, char * /*argv*/[]) -> int {

  QList<QObject *> list;
  fillContainer(list, 10);
  displayDistances(list);

  QVector<QObject *> vector;
  fillContainer(vector, 10);
  displayDistances(vector);

  return 0;
}
