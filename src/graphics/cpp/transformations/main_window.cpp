#include "main_window.h"
#include "./ui_main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->xSpinBox->setValue(ui->transformationDisplay->getTranslate().x());
  ui->ySpinBox->setValue(ui->transformationDisplay->getTranslate().y());
  ui->scaleSpinBox->setValue(ui->transformationDisplay->getScale() * 100);
  ui->rotateSpinBox->setValue(ui->transformationDisplay->getRotate());

  // conect ui->transformationDisplay setTranslate() to xSpinBox and ySpinBox
  connect(ui->xSpinBox, &QSpinBox::valueChanged, ui->transformationDisplay,
          [&](int x) {
            ui->transformationDisplay->setTranslate(
                x, ui->transformationDisplay->getTranslate().y());
          });

  connect(ui->ySpinBox, &QSpinBox::valueChanged, ui->transformationDisplay,
          [&](int y) {
            ui->transformationDisplay->setTranslate(
                ui->transformationDisplay->getTranslate().x(), y);
          });

  // conect ui->transformationDisplay setScale() to scaleSpinBox
  connect(ui->scaleSpinBox, &QDoubleSpinBox::valueChanged,
          ui->transformationDisplay, [&](double scale) {
            ui->transformationDisplay->setScale(scale / 100);
          });

  // conect ui->transformationDisplay setRotate() to rotateSpinBox
  connect(ui->rotateSpinBox, &QSpinBox::valueChanged, ui->transformationDisplay,
          [&](int angle) { ui->transformationDisplay->setRotate(angle); });
}

MainWindow::~MainWindow() { delete ui; }
