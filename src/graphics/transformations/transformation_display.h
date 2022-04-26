#ifndef TransformationDisplay_H
#define TransformationDisplay_H

#include <QWidget>

class TransformationDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit TransformationDisplay(QWidget *parent = nullptr);
    ~TransformationDisplay();
    void setTranslate(int x, int y);
    void setScale(float scale);
    void setRotate(float angle);
    QPoint getTranslate();
    float getScale();
    float getRotate();

protected:
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent *e);

private:
    QPoint translation;
    float rotation;
    float scale;
};

#endif // TransformationDisplay_H
