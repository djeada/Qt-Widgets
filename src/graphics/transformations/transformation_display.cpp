#include "transformation_display.h"
#include <QPainter>

TransformationDisplay::TransformationDisplay(QWidget *parent) : QWidget(parent), translation(0, 0), rotation(0), scale(1)
{
}

TransformationDisplay::~TransformationDisplay()
{
}


void TransformationDisplay::setTranslate(int x, int y)
{
    translation.setX(x);
    translation.setY(y);
    update();
}


void TransformationDisplay::setScale(float scale)
{
    this->scale = scale;
    update();
}


void TransformationDisplay::setRotate(float angle)
{
    rotation = angle;
    update();
}


QPoint TransformationDisplay::getTranslate()
{
    return translation;
}


float TransformationDisplay::getScale()
{
    return scale;
}


float TransformationDisplay::getRotate()
{
    return rotation;
}


void TransformationDisplay::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    
    //apply transformations
    painter.translate(translation);
    painter.rotate(rotation);
    painter.scale(scale, scale);

    // set font size to heigth of widget / 3
    painter.setFont(QFont("Arial", this->height() / 3));

    // Draw Qt text in the center of the widget
    // Make sure the whole text is visible
    painter.drawText(rect(), Qt::AlignCenter, "Qt");

}



QSize TransformationDisplay::sizeHint() const
{
    if (width() < 20 || height() < 20)
        return QSize(20, 20);
    
    return QSize(width(), height());
}
