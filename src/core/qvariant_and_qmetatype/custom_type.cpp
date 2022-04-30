#include "custom_type.h"

Person::Person() : name(""), age(0) {}

Person::Person(const QString &name, int age) : name(name), age(age) {}

Person::Person(const Person &other) : name(other.name), age(other.age) {}

Person::~Person() {}