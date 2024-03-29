#ifndef _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_MOVING_BALLS_MOVABLE_IMAGE_H
#define _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_MOVING_BALLS_MOVABLE_IMAGE_H

#include <QGraphicsItem>

class MovableImage : public QObject, public QGraphicsItem {
  Q_OBJECT
public:
  MovableImage(QRectF rectBorder, QObject *parent);
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
  QPointF getSpeed();
  void setSpeed(QPointF point);
  void reverseSpeed();

protected:
  void advance(int phase);

private:
  QPointF speed;
  void collideWithWall();
};

#endif // _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_MOVING_BALLS_MOVABLE_IMAGE_H
