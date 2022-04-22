#include "computingprocess.h"
#include <QCoreApplication>
#include <QDebug>
#include <QThreadPool>
#include <QTime>
#include <vector>

void delay(int n) {
  QTime dieTime = QTime::currentTime().addSecs(n);
  while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void startProcesses(int n) {

  std::vector<ComputingProcess *> processes(n, new ComputingProcess());

  for (auto &process : processes)
    QThreadPool::globalInstance()->start(process);

  qDebug() << QThreadPool::globalInstance()->activeThreadCount();
  delay(10);
  qDebug() << QThreadPool::globalInstance()->activeThreadCount();
}

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  startProcesses(10);

  return a.exec();
}
