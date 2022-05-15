#include "main_window.h"
#include "./ui_main_window.h"
#include "tree_model.h"
#include <QList>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  auto model = new TreeModel(QStringList() << "Col A" << "Col B" << "Col C");
  model->appendRow(QStringList() << "Elements");
  model->appendRow(QStringList() << "Items");
  ui->treeView->setModel(model);
}

MainWindow::~MainWindow() { delete ui; }
