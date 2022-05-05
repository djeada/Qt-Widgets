
/* status bar is QProgressBar with internal QTimer
every second it will update the progress bar by incrementing it by 1
there are functions that allow you to set the progress bar to a specific value
and to start and stop the timer
*/

#include <QProgressBar>
#include <QTimer>

class StatusBar : public QProgressBar {
  Q_OBJECT

public:
  StatusBar(QWidget *parent = nullptr);
  ~StatusBar();

public slots:
  void start();
  void stop();

private:
  QTimer *timer;
  int timer_interval;
};
