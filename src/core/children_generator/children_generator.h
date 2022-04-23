#ifndef CHILDRENGENERATOR_H
#define CHILDRENGENERATOR_H

#include <QObject>
#include <QString>

class ChildrenGenerator: public QObject
{
    Q_OBJECT
public:
    ChildrenGenerator(QString name, QObject *parent = nullptr);
    ~ChildrenGenerator();
    QObject * createChild(QString name);
    void deleteChild(QString name);
};

#endif // CHILDRENGENERATOR_H
