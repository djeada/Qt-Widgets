#ifndef COMPUTINGWORKER_H
#define COMPUTINGWORKER_H

#include <QDebug>
#include <QObject>

class ComputingWorker : public QObject {
  Q_OBJECT
public:
  explicit ComputingWorker(QObject *parent = nullptr);

signals:
  void showResults(int n);
  void doneProcess();

public slots:
  void process(int n = INT_MAX);
};

#endif // COMPUTINGWORKER_H
