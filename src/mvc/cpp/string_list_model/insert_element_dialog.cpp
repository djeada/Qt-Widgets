#include "insert_element_dialog.h"
#include "./ui_insert_element_dialog.h"
#include <QPushButton>

InsertElementDialog::InsertElementDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::InsertElementDialog) {
  ui->setupUi(this);

  connect(this, &QDialog::accepted, this, [=]() {
    auto data = InsertElementData{ui->spinBox->value(), ui->lineEdit->text()};
    emit elementSelected(data);
    close();
  });

}

void InsertElementDialog::setMaxIndex(int maxIndex) {
  ui->spinBox->setMaximum(maxIndex);
}

InsertElementDialog::~InsertElementDialog() { delete ui; }
