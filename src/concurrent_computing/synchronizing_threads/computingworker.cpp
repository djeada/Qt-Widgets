#include "computingworker.h"

ComputingWorker::ComputingWorker(QObject *parent) : QObject(parent) {}
void ComputingWorker::process(int n) {
  int result = 0;
  for (int i = 0; i < n; ++i)
    result++;

  emit showResults(result);
  emit doneProcess();
}
