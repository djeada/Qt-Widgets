#ifndef _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_MOVABLE_IMAGE_MAIN_WINDOW_H
#define _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_MOVABLE_IMAGE_MAIN_WINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>

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
  QGraphicsScene *scene;
};
#endif // _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_MOVABLE_IMAGE_MAIN_WINDOW_H
