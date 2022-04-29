#include "main_window.h"
#include "movable_image.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  scene = new BorderedScene(QRectF(0, 0, 300, 300), 10,  this);
    ui->graphicsView->setScene(scene);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, scene, &BorderedScene::advance);
    timer->start(100);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_addButton_released() {
  scene->addItem(new MovableImage(scene->sceneRect(), this));
}

void MainWindow::on_removeButton_released() {
  for (auto item : scene->selectedItems()) {
    scene->removeItem(item);
    delete item;
  }
}
