#include "status_bar.h"

StatusBar::StatusBar(QWidget *parent)
    : QProgressBar(parent), timer(new QTimer(this)), timer_interval(300) {
  connect(timer, &QTimer::timeout, this, [&]() {
    setValue(value() + 1);
    start();
  });
  start();
}

StatusBar::~StatusBar() { delete timer; }

void StatusBar::start() { timer->start(timer_interval); }

void StatusBar::stop() { timer->stop(); }
