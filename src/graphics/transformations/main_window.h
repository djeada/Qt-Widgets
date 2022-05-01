#ifndef _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_TRANSFORMATIONS_MAIN_WINDOW_H
#define _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_TRANSFORMATIONS_MAIN_WINDOW_H

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

private:
  Ui::MainWindow *ui;
};
#endif // _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_TRANSFORMATIONS_MAIN_WINDOW_H
