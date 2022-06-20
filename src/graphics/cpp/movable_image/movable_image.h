#ifndef _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_MOVABLE_IMAGE_MOVABLE_IMAGE_H
#define _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_MOVABLE_IMAGE_MOVABLE_IMAGE_H

#include <QGraphicsItem>

class MovableImage : public QObject, public QGraphicsItem {
  Q_OBJECT
public:
  MovableImage(QObject *parent);

private:
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
};

#endif // _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_MOVABLE_IMAGE_MOVABLE_IMAGE_H
