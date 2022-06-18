
#ifndef CUSTOM_DELEGATE_H
#define CUSTOM_DELEGATE_H

#include <QStyledItemDelegate>

class CryptoRankingDelegate : public QStyledItemDelegate {
  Q_OBJECT

public:
  CryptoRankingDelegate(QObject *parent = nullptr);
  ~CryptoRankingDelegate();

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const;
  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const;

};

#endif // CUSTOM_DELEGATE_H
