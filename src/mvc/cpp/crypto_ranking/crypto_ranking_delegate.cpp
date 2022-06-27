#include "crypto_ranking_delegate.h"
#include <QApplication>
#include <QDialog>
#include <QLineEdit>
#include <QPainter>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

CryptoRankingDelegate::CryptoRankingDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

CryptoRankingDelegate::~CryptoRankingDelegate() {}

void CryptoRankingDelegate::paint(QPainter *painter,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const {
  auto column = index.column();

  if (column == 2) {
    auto value = index.data().toDouble();
    auto oldPen = painter->pen();
    if (value < 0) {
      painter->setPen("#8b0000");
    } else {
      painter->setPen("#006600");
    }
    auto icon = index.data(Qt::DecorationRole).value<QIcon>();
    auto pixmap = icon.pixmap(option.decorationSize);
    painter->drawPixmap(option.rect.x() + 1,
                        option.rect.y() + option.rect.height() / 2 -
                            pixmap.height() / 2,
                        pixmap);
    painter->drawText(option.rect, Qt::AlignCenter,
                      QString::number(value, 'f', 0) + "%");
    painter->setPen(oldPen);
  } else if (column == 1 || column == 3 || column == 4) {
    auto value = index.data().toDouble();
    auto rect = option.rect;
    rect.setX(rect.x() + 3);
    painter->drawText(rect, option.displayAlignment,
                      "$" + QString::number(value, 'f', 0));
  } else {
    QStyledItemDelegate::paint(painter, option, index);
  }
}

QSize CryptoRankingDelegate::sizeHint(const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const {
  // make it twice as long as the default
  auto originalSize = QStyledItemDelegate::sizeHint(option, index);
  return QSize(originalSize.width(), originalSize.height() * 2);
}
