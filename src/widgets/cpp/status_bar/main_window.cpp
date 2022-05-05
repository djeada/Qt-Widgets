#include "main_window.h"
#include "./ui_main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // connect start button released with progressBar
  connect(ui->startButton, &QPushButton::released, this, [&]() {
    if (ui->startButton->isChecked()) {
      ui->progressBar->start();
    } else {
      ui->progressBar->stop();
    }
  });

  // connect stop button released with progressBar
  connect(ui->stopButton, &QPushButton::released, this, [&]() {
    if (ui->stopButton->isChecked()) {
      ui->progressBar->stop();
    } else {
      ui->progressBar->start();
    }
  });

  // connect reset button released with progressBar
  connect(ui->resetButton, &QPushButton::released, this,
          [&]() { ui->progressBar->setValue(0); });

  // when stop button is checked, start button is unchecked
  // and vice versa
  connect(ui->stopButton, &QPushButton::toggled, this,
          [&]() { ui->startButton->setChecked(!ui->stopButton->isChecked()); });

  connect(ui->startButton, &QPushButton::toggled, this,
          [&]() { ui->stopButton->setChecked(!ui->startButton->isChecked()); });
}

MainWindow::~MainWindow() { delete ui; }
