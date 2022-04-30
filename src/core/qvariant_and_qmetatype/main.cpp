#include "custom_type.h"
#include <QCoreApplication>
#include <QDebug>

auto main(int /*argc*/, char * /*argv*/[]) -> int {

  QVariant variant = 0;
  variant = 42;
  qDebug() << variant.toInt();

  variant = QString("Hello");
  qDebug() << variant.toString();

  variant = QVariant::fromValue(Person("John", 42));
  qDebug() << variant.value<Person>().name;
  qDebug() << variant.value<Person>().age;
  return 0;
}
