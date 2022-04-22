#include "computingworker.h"
#include <QCoreApplication>
#include <QDebug>

class Master : QObject {
public:
  Master() {
    ComputingWorker *workerObject = new ComputingWorker;
    connect(workerObject, &ComputingWorker::doneProcess, workerObject,
            &ComputingWorker::deleteLater);
    connect(workerObject, &ComputingWorker::showResults, this,
            [](int n) { qDebug() << "Final result:" << n; });
    workerObject->process();
  }
};

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  Master master;

  return a.exec();
}
