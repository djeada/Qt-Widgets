#ifndef _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_IMAGE_CROPPER_MAIN_WINDOW_H
#define _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_IMAGE_CROPPER_MAIN_WINDOW_H

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
  void on_actionSave_triggered();
  void on_actionOpen_triggered();

private:
  Ui::MainWindow *ui;
};
#endif // _HOME_ADAM_QT_WIDGETS_SRC_GRAPHICS_IMAGE_CROPPER_MAIN_WINDOW_H
