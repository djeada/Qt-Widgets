#include "mainwindow.h"
#include "movableimage.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);

  QGraphicsTextItem *text =
      scene->addText("Drop pictures here", QFont("Ubuntu", 20));
  text->setFlag(QGraphicsItem::ItemIsMovable);
  text->setFlag(QGraphicsItem::ItemIsSelectable);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_addButton_released() {
  scene->addItem(new MovableImage(this));
}

void MainWindow::on_removeButton_released() {
  for (auto item : scene->selectedItems()) {
    scene->removeItem(item);
    delete item;
  }
}
