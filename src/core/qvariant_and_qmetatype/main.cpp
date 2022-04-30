#include "custom_type.h"
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[]) {

  QVariant variant;
  variant = 42;
  qDebug() << variant.toInt();

  variant = QString("Hello");
  qDebug() << variant.toString();

  variant = QVariant::fromValue(Person("John", 42));
  qDebug() << variant.value<Person>().name;
  qDebug() << variant.value<Person>().age;
  return 0;
}
