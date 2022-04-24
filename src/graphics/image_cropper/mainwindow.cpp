#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QPainterPath>
#include <QWheelEvent>
#include <QtMath>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  picSize = ui->image->size();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter;
  painter.begin(this);

  if (!pixmap.isNull()) {
    QPainterPath path;
    double width = ui->image->width();
    double height = ui->image->height();
    QPoint pos = ui->centralwidget->mapToParent(ui->image->pos());
    path.addEllipse(pos.x(), pos.y(), width, height);
    painter.setClipPath(path);

    int x = ui->image->pos().x() + (width - picSize.width()) / 2;
    int y = ui->image->pos().y() + (height - picSize.height()) / 2;

    painter.drawPixmap(x, y, picSize.width(), picSize.height(), pixmap);
  }

  painter.end();
}

void MainWindow::wheelEvent(QWheelEvent *event) {
  QPoint numDegrees = event->angleDelta() / 8;
  QPoint numSteps = numDegrees / 15;
  int step = numSteps.y();

  double width = step * ui->image->width() / 100;
  double height = step * ui->image->width() / 100;

  picSize = QSize(picSize.width() + width, picSize.height() + height);
  update();
  event->accept();
}

void MainWindow::on_actionSave_triggered() {}

void MainWindow::on_actionOpen_triggered() {
  QString fileName =
      QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::currentPath(),
                                   tr("Image Files (*.jpg *.jpeg)"));

  if (fileName != "") {
    QPixmap newPix(fileName);

    if (!newPix.isNull()) {
      if (newPix.width() < 200 || newPix.height() < 200) {
        QMessageBox::warning(
            this, tr("Invalid Size"),
            tr("Size of the image must be bigger than 200x200."));
        return;
      }

      pixmap = newPix;
      update();
    }

    else
      QMessageBox::warning(this, tr("Invalid Image"),
                           tr("You tried loading an invalid file."));
  }
}
