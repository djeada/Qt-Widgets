#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
  void on_actionSave_triggered();
  void on_actionOpen_triggered();

private:
  Ui::MainWindow *ui;
  QPixmap pixmap;
  QSize picSize;
  void paintEvent(QPaintEvent *event);
  void wheelEvent(QWheelEvent *event);
};
#endif // MAINWINDOW_H
