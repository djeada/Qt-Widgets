#include "image_cropper.h"
#include <QDebug>
#include <QMessageBox>
#include <QMimeData>
#include <QPainter>
#include <QPainterPath>
#include <QWheelEvent>
#include <QtMath>

ImageCropper::ImageCropper(QWidget *parent) : QWidget(parent) {
  // accept droped images
  setAcceptDrops(true);
}

void ImageCropper::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter;

  // draw a black circle in the center of the widget
  // with empty fill
  painter.begin(this);
  painter.setPen(Qt::black);
  painter.setBrush(Qt::NoBrush);
  painter.drawEllipse(rect().center(), rect().width() / 2, rect().height() / 2);
  painter.end();

  if (pixmap.isNull()) {
    // draw text: "Drag and drop an image here"
    painter.begin(this);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);
    painter.drawText(rect(), Qt::AlignCenter, "Drag and drop an image here");
    painter.end();
  }

  else {
    // draw pixmap within the circle drawn above
    // it should not go out of the circle bounds
    // the picture has to be cropped with clip path ellipse
    QPainterPath path;
    path.addEllipse(rect().center(), rect().width() / 2, rect().height() / 2);
    painter.begin(this);
    painter.setClipPath(path);
    painter.drawPixmap(rect(), pixmap);
    painter.end();
  }
}

void ImageCropper::dropEvent(QDropEvent *event) {
  // get the file name of the dropped image
  auto fileName = event->mimeData()->urls().first().toLocalFile();

  // set the pixmap from the file
  setPixmapFromFile(fileName);
}

void ImageCropper::setPixmapFromFile(QString fileName) {
  QPixmap newPix(fileName);

  if (newPix.isNull()) {
    QMessageBox::warning(this, tr("Invalid Image"),
                         tr("You tried loading an invalid file."));
    return;
  }

  pixmap = newPix;
  update();
}

void ImageCropper::dragEnterEvent(QDragEnterEvent *event) {
  // accept the event if the mime data contains a url
  if (event->mimeData()->hasUrls()) {
    event->acceptProposedAction();
  }
}

void ImageCropper::dragMoveEvent(QDragMoveEvent *event) {
  // accept the event if the mime data contains a url
  if (event->mimeData()->hasUrls()) {
    event->acceptProposedAction();
  }
}
