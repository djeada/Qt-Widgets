#ifndef MOVABLEIMAGE_H
#define MOVABLEIMAGE_H

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

#endif // MOVABLEIMAGE_H
