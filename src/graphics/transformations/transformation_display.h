#ifndef _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_TRANSFORMATIONS_TRANSFORMATION_DISPLAY_H
#define _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_TRANSFORMATIONS_TRANSFORMATION_DISPLAY_H

#include <QWidget>

class TransformationDisplay : public QWidget {
  Q_OBJECT
public:
  explicit TransformationDisplay(QWidget *parent = nullptr);
  ~TransformationDisplay();
  void setTranslate(int x, int y);
  void setScale(float scale);
  void setRotate(float angle);
  QPoint getTranslate();
  auto getScale() const -> float;
  auto getRotate() const -> float;

protected:
  QSize sizeHint() const override;
  void paintEvent(QPaintEvent *e);

private:
  QPoint translation;
  float rotation;
  float scale;
};

#endif // _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_TRANSFORMATIONS_TRANSFORMATION_DISPLAY_H
