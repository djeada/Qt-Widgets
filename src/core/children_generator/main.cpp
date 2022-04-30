#include "children_generator.h"
#include <QCoreApplication>
#include <QDebug>

auto main(int /*argc*/, char * /*argv*/[]) -> int {

  auto root = new ChildrenGenerator("root");

  for (int i = 0; i < 10; ++i) {
    auto child = root->createChild("child" + QString::number(i));
    if (child) {
      qDebug() << "Created child with name: " << child->objectName();
    } else {
      qDebug() << "Error creating child with name: "
               << "child" + QString::number(i);
    }
  }

  // Display number of children
  qDebug() << "Number of children: " << root->children().size();

  // Delete all children
  for (auto child : root->children()) {
    root->deleteChild(child->objectName());
  }

  // Display number of children
  qDebug() << "Number of children: " << root->children().size();
  return 0;
}
