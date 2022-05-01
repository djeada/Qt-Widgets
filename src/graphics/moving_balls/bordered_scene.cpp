#include "bordered_scene.h"
#include "movable_image.h"
#include <QHash>
#include <QPainter>

BorderedScene::BorderedScene(QRectF borderRect, unsigned int numBalls,
                             QObject *parent)
    : QGraphicsScene(parent) {
  setSceneRect(borderRect);
  drawSceneBorder();

  for (int i; i < numBalls; i++) {
    addItem(new MovableImage(sceneRect(), this));
  }
}

void BorderedScene::drawSceneBorder() {
  QLineF topLine(sceneRect().topLeft(), sceneRect().topRight());
  QLineF leftLine(sceneRect().topLeft(), sceneRect().bottomLeft());
  QLineF rightLine(sceneRect().topRight(), sceneRect().bottomRight());
  QLineF bottomLine(sceneRect().bottomLeft(), sceneRect().bottomRight());

  QPen myPen = QPen(Qt::red);

  addLine(topLine, myPen);
  addLine(leftLine, myPen);
  addLine(rightLine, myPen);
  addLine(bottomLine, myPen);
}

void BorderedScene::advance() {
  QGraphicsScene::advance();

  QHash<MovableImage *, bool> objectsToCheck;

  // fill with all items that are QMovableImage
  for (auto item : items()) {
    // use dynamic cast to check if item is MovableImage
    auto movableImage = dynamic_cast<MovableImage *>(item);
    if (movableImage != nullptr) {
      objectsToCheck.insert(movableImage, true);
    }
  }

  // check for collisions
  for (auto it = objectsToCheck.constBegin(); it != objectsToCheck.constEnd();
       ++it) {
    auto comparedObject = it.key();
    if (!it.value()) {
      continue;
    }
    objectsToCheck[comparedObject] = false;
    for (auto otherItem : collidingItems(comparedObject)) {

      auto otherObject = dynamic_cast<MovableImage *>(otherItem);
      if (otherItem == nullptr || !objectsToCheck[otherObject]) {
        continue;
      }
      // reverse the speed
      otherObject->reverseSpeed();
      comparedObject->reverseSpeed();
      // move them apart so they don't collide
      while (comparedObject->collidesWithItem(otherObject)) {
        otherObject->setPos(otherObject->pos() + otherObject->getSpeed());
        comparedObject->setPos(comparedObject->pos() +
                               comparedObject->getSpeed());
      }

      objectsToCheck[otherObject] = false;
    }
  }
}
