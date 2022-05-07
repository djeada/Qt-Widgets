#include <QCoreApplication>
#include <QDebug>
#include <QSysInfo>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

#ifdef Q_OS_LINUX
  qDebug() << "We are on Linux system!";
#elif defined(Q_OS_WIN32)
  qDebug() << "We are on Windows system!";
#elif defined(Q_OS_MACX)
  qDebug() << "We are on Mac system!";
#else
  qDebug() << "Unsupported OS!";
#endif

  QSysInfo systemInfo;

  qDebug() << "Cpu: " << systemInfo.buildCpuArchitecture();
  qDebug() << "Build: " << systemInfo.buildAbi();
  qDebug() << "Kernel: " << systemInfo.kernelType();
  qDebug() << "Version: " << systemInfo.kernelVersion();
  qDebug() << "Host name: " << systemInfo.machineHostName();
  qDebug() << "Type: " << systemInfo.productType();
  qDebug() << "Version: " << systemInfo.productVersion();
  qDebug() << "Product name: " << systemInfo.prettyProductName();

  return a.exec();
}
