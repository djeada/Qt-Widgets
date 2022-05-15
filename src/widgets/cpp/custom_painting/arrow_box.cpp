#include "arrow_box.h"
#include <QPainter>

ArrowBox::ArrowBox(QWidget *parent) : QWidget(parent) {}

void ArrowBox::paintEvent(QPaintEvent *e) {
  // Draw an arrow pointing downwards

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  // Draw a straight line
  painter.setPen(QPen(Qt::black, 0.1 * width()));
  painter.drawLine(width() / 2, 0, width() / 2, 0.8 * height());

  // Draw the arrow head
  painter.setPen(QPen(Qt::black, 1));
  painter.setBrush(Qt::black);
  painter.drawPolygon(QPolygonF()
                      << QPointF(width() / 2, height())
                      << QPointF(width() / 2 - 0.2 * width(), 0.8 * height())
                      << QPointF(width() / 2 + 0.2 * width(), 0.8 * height()));
}

QSize ArrowBox::sizeHint() const {
  if (width() < 20 || height() < 20)
    return QSize(20, 20);

  return QSize(width(), height());
}
