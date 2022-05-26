#include "main_window.h"
#include "./ui_main_window.h"
#include "file_dir_model.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // set model
  auto model = new FileDirModel(this);
  model->setRootPath(QDir::currentPath());
  ui->treeView->setModel(model);
}

MainWindow::~MainWindow() { delete ui; }
