#include "main_window.h"
#include "./ui_main_window.h"

#include <QString>

int foo(int id) {
  qDebug() << "Starting worker function with id: " << QThread::currentThreadId();
  QThread::sleep(1);
  qDebug() << "Worker function finished with id: " << QThread::currentThreadId();

  return id;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), counter(0) {
  ui->setupUi(this);

  // connect push button with QtConcurrent::run and run single foo() function, but use a watcher to wait till it's finished
  connect(ui->pushButton, &QPushButton::clicked, [this]() {
    auto future = QtConcurrent::run(foo, counter++);
    connect(&watcher, &QFutureWatcher<int>::finished, this, [this, future]() {
      // display return result of foo() function
      ui->listWidget->addItem(QString("Thread id: 0x%1").arg(future.result()));
    });
    ui->listWidget->clear();
    watcher.setFuture(future);
  });


}

MainWindow::~MainWindow() { delete ui; }
