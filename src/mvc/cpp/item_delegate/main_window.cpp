#include "main_window.h"
#include "./ui_main_window.h"
#include "custom_delegate.h"
#include <QModelIndex>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  auto model = new QStringListModel(this);
  model->setStringList(QStringList() << "Item 1"
                                     << "73"
                                     << "Item 3"
                                     << "Item 4"
                                     << "Item 5"
                                     << "Item 6"
                                     << "Item 7"
                                     << "Item 8"
                                     << "Item 9");
  ui->listView->setModel(model);
  ui->listView->setItemDelegate(new CustomDelegate(this));
}

MainWindow::~MainWindow() { delete ui; }
