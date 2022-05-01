#ifndef _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_MOVING_BALLS_MAIN_WINDOW_H
#define _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_MOVING_BALLS_MAIN_WINDOW_H

#include "bordered_scene.h"
#include <QGraphicsScene>
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
} // namespace Ui
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
#endif // _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_MOVING_BALLS_MAIN_WINDOW_H
