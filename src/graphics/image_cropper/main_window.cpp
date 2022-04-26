#include "main_window.h"
#include "ui_main_window.h"

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
}

MainWindow::~MainWindow() { delete ui; }



void MainWindow::on_actionSave_triggered() {}

void MainWindow::on_actionOpen_triggered() {
  auto fileName =
      QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::currentPath(),
                                   tr("Image Files (*.jpg *.JPG *.png *.PNG, *.bmp, *.BMP)"));

  ui->image_cropper->setPixmapFromFile(fileName);
}


