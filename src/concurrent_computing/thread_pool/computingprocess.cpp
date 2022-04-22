#include "computingprocess.h"
#include <QDebug>

ComputingProcess::ComputingProcess() {}

void ComputingProcess::run() {
  int result = 0;

  for (int i = 0; i < INT_MAX; ++i)
    result += i;

  qDebug() << result;
}
