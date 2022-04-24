#include <QCoreApplication>
#include <QObject>
#include <QDebug>
#include <QMap>
#include <algorithm>
#include <cstdlib>

void fillMap(QMap<QObject*, int> &map, int size)
{
    for (int i = 0; i < size; ++i) {
        QObject *obj = new QObject;
        obj->setObjectName(QString("Obj%1").arg(i));
        map.insert(obj, i);
    }
}

void displayMap(const QMap<QObject*, int> &map)
{
    qDebug() << "Map:";
    for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
        qDebug() << "  " << it.key()->objectName() << ": " << it.value();
    }
}

void shuffle(QMap<QObject*, int> &map)
{
    for (auto it = map.begin(); it != map.end(); ++it) {
        it.value() = std::rand() % map.size();
    }
}

QList<QObject*> sortedKeys(const QMap<QObject*, int> &map)
{
    QList<QObject*> keys;
    for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
        keys.append(it.key());
    }
    std::sort(keys.begin(), keys.end(), [](QObject *a, QObject *b) {
        return a->objectName() < b->objectName();
    });
    return keys;
}


QList<int> sortedValues(const QMap<QObject*, int> &map)
{
    QList<int> values;
    for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
        values.append(it.value());
    }
    std::sort(values.begin(), values.end());
    return values;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QMap<QObject*, int> map;
    fillMap(map, 10);

    qDebug() << "Initial map:";
    displayMap(map);

    qDebug() << "Shuffling map...";
    shuffle(map);
    displayMap(map);

    qDebug() << "Sorting map by key...";
    auto keys = sortedKeys(map);
    for (auto key : keys) {
        qDebug() << "  " << key->objectName() << ": " << map.value(key);
    }

    qDebug() << "Sorting map by value...";
    auto values = sortedValues(map);
    for (auto value : values) {
        qDebug() << "  " << value;
    }

    return a.exec();
}
