#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCamera>
#include <QMainWindow>
#include <QMediaRecorder>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QMainWindow *parent = nullptr);
  ~MainWindow();

private slots:
  void on_devices_currentIndexChanged(const QString &arg1);
  void on_connectButton_released();
  void on_recordButton_released();

private:
  Ui::MainWindow *ui;
  bool connected;
  bool recording;
  QCamera *camera;
  QMediaRecorder *recorder;
  void toggleConnected();
  void toggleRecording();
};
#endif // MAINWINDOW_H
