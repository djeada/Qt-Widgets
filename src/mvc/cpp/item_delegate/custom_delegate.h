
#ifndef CUSTOM_DELEGATE_H
#define CUSTOM_DELEGATE_H

#include <QStyledItemDelegate>

class CustomDelegate : public QStyledItemDelegate {
  Q_OBJECT

public:
  CustomDelegate(QObject *parent = nullptr);
  ~CustomDelegate();

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const;
  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const;

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const;

private:
  QLineEdit *editor;
};

#endif // CUSTOM_DELEGATE_H
