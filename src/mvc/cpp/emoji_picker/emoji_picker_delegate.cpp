#include "emoji_picker_delegate.h"
#include <QApplication>
#include <QDialog>
#include <QLineEdit>
#include <QPainter>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

EmojiPickerDelegate::EmojiPickerDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

EmojiPickerDelegate::~EmojiPickerDelegate() {}

void EmojiPickerDelegate::paint(QPainter *painter,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index) const {

      auto rect = option.rect;
      // make the rect to be square
      rect.setWidth(rect.height());
      
      auto icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));

      if (!icon.isNull()) {
        //check if item is hovered
        if(option.state & QStyle::State_MouseOver) {
            painter->save();
            QLinearGradient gradient(rect.topLeft(), rect.bottomLeft());
            gradient.setColorAt(0, QColor(0, 0, 255, 50));
            gradient.setColorAt(1, QColor(0, 0, 255, 50));
            painter->fillRect(rect, gradient);
            painter->restore();
        }
        // draw icon as pixmap at the center of the option rect
        auto pixmapRect = rect;
        pixmapRect.setWidth(rect.width() * 0.8);
        pixmapRect.setHeight(rect.height() * 0.8);
        pixmapRect.moveCenter(rect.center());
        auto pixmap = icon.pixmap(pixmapRect.size());
        painter->drawPixmap(pixmapRect, pixmap);
      }
      else {
        // remove selection from option
        auto option_copy = option;
        option_copy.state = QStyle::State_Enabled;
        QStyledItemDelegate::paint(painter, option_copy, index);
      }
}

QSize EmojiPickerDelegate::sizeHint(const QStyleOptionViewItem &option,
                               const QModelIndex &index) const {
  // make it twice as long as the default
  auto originalSize = QStyledItemDelegate::sizeHint(option, index);
  return QSize(originalSize.width(), originalSize.height() * 2);
}
