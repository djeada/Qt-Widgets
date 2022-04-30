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
