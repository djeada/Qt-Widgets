
#include <QCoreApplication>
#include <QDebug>
#include <QVector>
#include <QtConcurrent>

void foo() {
  qDebug() << "Starting worker function with id: "
           << QThread::currentThreadId();
  QThread::sleep(1);
  qDebug() << "Worker function finished with id: "
           << QThread::currentThreadId();
}

int main(int argc, char *argv[]) {

  // spawn 3 threads with QConcurrent::run and put them in QList
  QVector<QFuture<void>> futures;
  for (int i = 0; i < 3; ++i) {
    futures.append(QtConcurrent::run(foo));
  }

  // wait for all threads to finish
  for (auto &future : futures) {
    future.waitForFinished();
  }

  return 0;
}
