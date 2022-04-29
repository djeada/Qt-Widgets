#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QTimer>
#include "bordered_scene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_addButton_released();
  void on_removeButton_released();

private:
  Ui::MainWindow *ui;
  BorderedScene *scene;
      QTimer *timer;
};
#endif // MAINWINDOW_H
