#ifndef _HOME_ADAM_QT_WIDGETS_SRC_CORE_QVARIANT_AND_QMETATYPE_CUSTOM_TYPE_H
#define _HOME_ADAM_QT_WIDGETS_SRC_CORE_QVARIANT_AND_QMETATYPE_CUSTOM_TYPE_H

#include <QMetaType>
#include <QObject>
#include <QString>

class Person {
public:
  Person();
  Person(const QString &name, int age);
  Person(const Person &other);
  ~Person();

  QString name;
  int age;
};

Q_DECLARE_METATYPE(Person)

#endif
