#include "main_window.h"
#include "insert_element_dialog.h"
#include "./ui_main_window.h"
#include <QStringListModel>
#include <QModelIndex>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  auto model = new QStringListModel(this);
  model->setStringList(QStringList() << "Item 1" << "Item 2" << "Item 3");
    ui->listView->setModel(model);

    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->listView->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->listView->setDragEnabled(true);
    ui->listView->setAcceptDrops(true);
    ui->listView->setDropIndicatorShown(true);
    ui->listView->setDragDropMode(QAbstractItemView::InternalMove);

    connect(ui->insertButton, &QPushButton::clicked, this, [=]() {
        auto dialog = new InsertElementDialog(this);
        dialog->setMaxIndex(model->rowCount());
        connect(dialog, &InsertElementDialog::elementSelected, this, [=](InsertElementData data) {
            model->insertRows(data.index, 1);
            model->setData(model->index(data.index), data.text);
        });
        dialog->show();
    });

    connect(ui->removeButton, &QPushButton::clicked, this, [=]() {
        auto indexes = ui->listView->selectionModel()->selectedIndexes();
        for (auto index : indexes) {
            model->removeRow(index.row());
        }
    });

}

MainWindow::~MainWindow() { delete ui; }
