#include "cmd_interface.h"
#include <QCoreApplication>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  CmdInterface cmd;
  cmd.action(QByteArray("dir"));
  cmd.action(QByteArray("echo \"Hello World\""));

  return a.exec();
}
