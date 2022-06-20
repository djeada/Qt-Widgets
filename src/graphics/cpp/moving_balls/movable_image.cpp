#include "movable_image.h"
#include <QGraphicsScene>
#include <QPainter>
#include <cstdlib>

const int rectSize = 100;

MovableImage::MovableImage(QRectF rectBorder, QObject *parent)
    : QObject(parent), QGraphicsItem() {

  // random between -5 and 5
  auto speedX = (std::rand() % 10) - 5;
  auto speedY = (std::rand() % 10) - 5;
  speed = QPointF(speedX, speedY);

  // random start position
  auto startX =
      (std::rand() % (int)(rectBorder.width() - rectSize)) + rectBorder.x();
  auto startY =
      (std::rand() % (int)(rectBorder.height() - rectSize)) + rectBorder.y();

  QPointF point(startX, startY);
  setPos(point);

  // make selectable and movable
  setFlag(QGraphicsItem::ItemIsSelectable);
  setFlag(QGraphicsItem::ItemIsMovable);
}

QRectF MovableImage::boundingRect() const { return QRect(0, 0, 20, 20); }

void MovableImage::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
  // gl shade model for smooth edges
  painter->setRenderHint(QPainter::SmoothPixmapTransform);
  auto rect = boundingRect();
  QBrush brush = painter->brush();

  // collision detection
  if (scene()->collidingItems(this).isEmpty()) {
    QPen pen(Qt::green, 5);
    brush = QBrush(Qt::green);
    painter->setPen(pen);
  } else {
    QPen pen(Qt::red, 5);
    painter->setPen(pen);
    brush = QBrush(Qt::red);
    collideWithWall();
  }

  painter->setBrush(brush);
  painter->drawEllipse(rect);
}

void MovableImage::advance(int phase) {
  setPos(x() + speed.x(), y() + speed.y());
}

void MovableImage::collideWithWall() {
  auto x = pos().x();
  auto y = pos().y();

  // get the position of the walls
  auto sceneRect = scene()->sceneRect();
  auto leftWall = sceneRect.x();
  auto rightWall = sceneRect.x() + sceneRect.width();
  auto topWall = sceneRect.y();
  auto bottomWall = sceneRect.y() + sceneRect.height();

  // if the ball hits the left wall
  if (x <= leftWall) {
    // bounce the ball off the wall
    speed = QPointF(-speed.x(), speed.y());
    x = leftWall + 1;
  }

  // if the ball hits the right wall
  if (x + boundingRect().width() >= rightWall) {
    // bounce the ball off the wall
    speed = QPointF(-speed.x(), speed.y());
    x = rightWall - boundingRect().width() - 1;
  }

  // if the ball hits the top wall
  if (y <= topWall) {
    // bounce the ball off the wall
    speed = QPointF(speed.x(), -speed.y());
    y = topWall + 1;
  }

  // if the ball hits the bottom wall
  if (y + boundingRect().height() >= bottomWall) {
    // bounce the ball off the wall
    speed = QPointF(speed.x(), -speed.y());
    y = bottomWall - boundingRect().height() - 1;
  }

  // set the position
  setPos(x, y);
}

QPointF MovableImage::getSpeed() { return speed; }

void MovableImage::setSpeed(QPointF newSpeed) { speed = newSpeed; }

void MovableImage::reverseSpeed() { speed = QPointF(-speed.x(), -speed.y()); }
