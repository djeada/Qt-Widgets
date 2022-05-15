#include "main_window.h"
#include "./ui_main_window.h"
#include "tree_model.h"
#include <QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  auto model = new ReordableTreeModel(QStringList() << "Col A" << "Col B" << "Col C");

  /*
├─Elements
│  ├─Element "elem1"
│  │  └─Properties
│  │     ├─Field field1 = value1
│  │     └─Field field2 = value2
│  └─Element "elem2"
│     └─Properties
│        └─Field field1 = abc
└─Metas
    ├─Meta 1, ...
    ├─Meta 2, ...
    └─Meta 3, ...
    */

  model->appendRow(QStringList() << "Elements");
  model->appendRow(QStringList() << "Metas");

  model->item(0, 0)->appendChild(new TreeItem(QStringList() << "Element"
                                                            << "elem1"
                                                            << "...",
                                              model->item(0, 0)));
  model->item(0, 0)->appendChild(new TreeItem(QStringList() << "Element"
                                                            << "elem2",
                                              model->item(0, 0)));
  model->item(1, 0)->appendChild(new TreeItem(QStringList() << "Meta"
                                                            << "1",
                                              model->item(1, 0)));
  model->item(1, 0)->appendChild(new TreeItem(QStringList() << "Meta"
                                                            << "2",
                                              model->item(1, 0)));
  model->item(1, 0)->appendChild(new TreeItem(QStringList() << "Meta"
                                                            << "3",
                                              model->item(1, 0)));

  model->item(0, 0)->child(0)->appendChild(
      new TreeItem(QStringList() << "Field"
                                 << "field1"
                                 << "value *",
                   model->item(0, 0)->child(0)));
  model->item(0, 0)->child(1)->appendChild(
      new TreeItem(QStringList() << "Field"
                                 << "field2"
                                 << "value **",
                   model->item(0, 0)->child(1)));
  model->item(0, 0)->child(0)->child(0)->appendChild(
      new TreeItem(QStringList() << "Field"
                                 << "field A"
                                 << "value1",
                   model->item(0, 0)->child(0)->child(0)));
  model->item(0, 0)->child(0)->child(0)->appendChild(
      new TreeItem(QStringList() << "Field"
                                 << "field B"
                                 << "value2",
                   model->item(0, 0)->child(0)->child(0)));
  model->item(0, 0)->child(1)->child(0)->appendChild(
      new TreeItem(QStringList() << "Field"
                                 << "field A"
                                 << "abc",
                   model->item(0, 0)->child(1)->child(0)));

  model->setHorizontalHeaderLabels(QStringList() << "Type"
                                                 << "Name"
                                                 << "Value");

  ui->treeView->setModel(model);
}

MainWindow::~MainWindow() { delete ui; }
