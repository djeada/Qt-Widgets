#include "movable_image.h"
#include <QPainter>

const int rectSize = 100;

MovableImage::MovableImage(QObject *parent) : QObject(parent), QGraphicsItem() {

  this->setFlag(QGraphicsItem::ItemIsMovable);
  this->setFlag(QGraphicsItem::ItemIsSelectable);
  this->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

QRectF MovableImage::boundingRect() const {
  return QRectF(-rectSize / 2, -rectSize / 2, rectSize, rectSize);
}

void MovableImage::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);

  auto brushColor = isSelected() ? Qt::darkBlue : Qt::darkGray;
  painter->setPen(Qt::black);
  painter->setBrush(brushColor);
  painter->drawRect(-rectSize / 2, -rectSize / 2, rectSize, rectSize);
}
