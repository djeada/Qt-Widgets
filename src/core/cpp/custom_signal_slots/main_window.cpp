#include "main_window.h"
#include "./ui_main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton, &QPushButton::clicked, this,
          [=]() { emit sendString(ui->lineEdit->text()); });

  connect(this, &MainWindow::sendString, this, &MainWindow::display);
}

void MainWindow::display(QString str) { ui->label->setText(str); }

MainWindow::~MainWindow() { delete ui; }
