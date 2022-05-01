#ifndef _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_MOVING_BALLS_BORDERED_SCENE_H
#define _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_MOVING_BALLS_BORDERED_SCENE_H

#include <QGraphicsScene>

class BorderedScene : public QGraphicsScene {
public:
  explicit BorderedScene(QRectF borderRect, unsigned int numBalls = 10,
                         QObject *parent = nullptr);

public slots:
  void advance();

private:
  void drawSceneBorder();
};

#endif // _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_MOVING_BALLS_BORDERED_SCENE_H
