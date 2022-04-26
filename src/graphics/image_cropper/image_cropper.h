#ifndef IMAGE_CROPPER_H
#define IMAGE_CROPPER_H

#include <QWidget>

class ImageCropper : public QWidget
{
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

#endif // IMAGE_CROPPER_H
