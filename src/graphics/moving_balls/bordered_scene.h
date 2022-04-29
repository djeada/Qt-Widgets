#ifndef BORDEREDSCENE_H
#define BORDEREDSCENE_H

#include <QGraphicsScene>

class BorderedScene : public QGraphicsScene
{
public:
    explicit BorderedScene(QRectF borderRect, unsigned int numBalls = 10, QObject *parent = nullptr);

public slots:
    void advance();

private:
    void drawSceneBorder();
};

#endif // BORDEREDSCENE_H
