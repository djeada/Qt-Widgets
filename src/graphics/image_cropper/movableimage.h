#ifndef MOVABLEIMAGE_H
#define MOVABLEIMAGE_H

#include <QLabel>
#include <QWidget>

class MovableImage : public QLabel {
  Q_OBJECT
public:
  MovableImage(QWidget *parent);
};

#endif // MOVABLEIMAGE_H
