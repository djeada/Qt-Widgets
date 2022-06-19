#include <QString>
#include <QList>

struct EmojiData {
    QString name;
    QString iconPath;
    QList<QString> tags;

    EmojiData(const QString& name, const QString& iconPath, const QList<QString>& tags)
        : name(name), iconPath(iconPath), tags(tags) {}
};

struct EmojiCategory {
    QString name;
    QList<EmojiData> emojis;

    EmojiCategory(const QString& name, const QList<EmojiData>& emojis)
        : name(name), emojis(emojis) {}
};