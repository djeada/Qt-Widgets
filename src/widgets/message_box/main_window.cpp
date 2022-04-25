#include "main_window.h"
#include "./ui_main_window.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect push button release with show message box
    connect(ui->pushButton, &QPushButton::released, this, [&]() {
        auto result = QMessageBox::warning(this, tr("My Application"),
                                  tr("The most recent modifications are not saved.\n"
                                     "Would you like to save them?"),
                                  QMessageBox::Save | 
                                  QMessageBox::Discard |
                                  QMessageBox::Cancel,
                                  QMessageBox::Save);
        
        switch (result) {
            case QMessageBox::Save:
                QMessageBox::information(this, tr("My Application"),
                                         tr("Save clicked."));
                break;
            case QMessageBox::Discard:
                QMessageBox::information(this, tr("My Application"),
                                         tr("Discard clicked."));
                break;
            case QMessageBox::Cancel:
                QMessageBox::information(this, tr("My Application"),
                                         tr("Cancel clicked."));
                break;
            default:
                break;
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

