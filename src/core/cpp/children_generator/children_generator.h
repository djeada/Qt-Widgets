#ifndef _HOME_ADAM_QT_WIDGETS_SRC_CORE_CHILDREN_GENERATOR_CHILDREN_GENERATOR_H
#define _HOME_ADAM_QT_WIDGETS_SRC_CORE_CHILDREN_GENERATOR_CHILDREN_GENERATOR_H

#include <QObject>
#include <QString>

class ChildrenGenerator : public QObject {
  Q_OBJECT
public:
  ChildrenGenerator(QString name, QObject *parent = nullptr);
  ~ChildrenGenerator();
  QObject *createChild(QString name);
  void deleteChild(QString name);
};

#endif // _HOME_ADAM_QT_WIDGETS_SRC_CORE_CHILDREN_GENERATOR_CHILDREN_GENERATOR_H
