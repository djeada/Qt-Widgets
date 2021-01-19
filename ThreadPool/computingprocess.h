#ifndef COMPUTINGPROCESS_H
#define COMPUTINGPROCESS_H

#include <QRunnable>

class ComputingProcess : public QRunnable
{
public:
    ComputingProcess();
    void run();
};

#endif // COMPUTINGPROCESS_H
