#include "children_generator.h"
#include <QDebug>

ChildrenGenerator::ChildrenGenerator(QString name, QObject *parent)
    : QObject(parent) {
  qDebug() << "Creating ChildrenGenerator object with name: " << name;
  this->setObjectName(name);
}

ChildrenGenerator::~ChildrenGenerator() {
  qDebug() << "Destroying ChildrenGenerator object with name: "
           << this->objectName();
}

QObject *ChildrenGenerator::createChild(QString /*name*/) {
  qDebug() << "Creating child with name: " << name;
  try {
    auto child = new ChildrenGenerator(name, this);
    return child;
  } catch (...) {
    qDebug() << "Error creating child with name: " << name;
    return nullptr;
  }
}

static void ChildrenGenerator::deleteChild(QString /*name*/) {
  qDebug() << "Attempting to delete child with name: " << name;
  auto child = this->findChild<QObject *>(name);
  if (child) {
    child->deleteLater();
  } else {
    qDebug() << "Child not found";
  }
}
