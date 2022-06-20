#ifndef _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_IMAGE_CROPPER_IMAGE_CROPPER_H
#define _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_IMAGE_CROPPER_IMAGE_CROPPER_H

#include <QWidget>

class ImageCropper : public QWidget {
  Q_OBJECT
public:
  explicit ImageCropper(QWidget *parent = nullptr);
  void setPixmapFromFile(QString fileName);

signals:

private:
  QPixmap pixmap;
  void paintEvent(QPaintEvent *event);
  void dropEvent(QDropEvent *event);
  void dragEnterEvent(QDragEnterEvent *event);
  void dragMoveEvent(QDragMoveEvent *event);
};

#endif // _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_IMAGE_CROPPER_IMAGE_CROPPER_H
