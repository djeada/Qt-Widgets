
#ifndef CUSTOM_DELEGATE_H
#define CUSTOM_DELEGATE_H

#include <QStyledItemDelegate>

class EmojiPickerDelegate : public QStyledItemDelegate {
  Q_OBJECT

public:
  EmojiPickerDelegate(QObject *parent = nullptr);
  ~EmojiPickerDelegate();

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const;
  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const;
};

#endif // CUSTOM_DELEGATE_H
