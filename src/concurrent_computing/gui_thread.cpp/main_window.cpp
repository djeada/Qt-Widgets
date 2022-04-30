#include "main_window.h"
#include "./ui_main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->label_1->setToolTip(
      "<html><head/><body><p><span style=\" font-size:10pt; "
      "font-weight:600;\">Custom tooltip</span></p></body></html>");
  ui->label_2->setToolTip(
      "<html><head/><body><p><span style=\" font-size:10pt; "
      "font-weight:600;\">Custom tooltip</span></p><p><span style=\" "
      "font-size:10pt; font-weight:600;\">with bullet list <ol> <li>item "
      "1</li> <li>item 2</li> <li>item 3</li> </ol></span></p></body></html>");
  ui->label_3->setToolTip(
      "<html><head/><body><p><span style=\" font-size:10pt; "
      "font-weight:600;\">Custom tooltip</span></p><p><span style=\" "
      "font-size:10pt; font-weight:600;\">with image <img "
      "src=\"https://placekitten.com/200/300\"/></span></p></body></html>");
}

MainWindow::~MainWindow() { delete ui; }
