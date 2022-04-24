#include "cmd_interface.h"
#include <QDebug>

CmdInterface::CmdInterface(QObject *parent) : QObject(parent) {
#ifdef __linux__
  const QString executable_path = "/bin/bash";
#elif _WIN32
  const QString executable_path = "C:/windows/system32/cmd.exe";
#else
  throw std::runtime_error("Unsupported OS");
#endif

  proc.setProgram(executable_path);
  proc.start();
  connect(&proc, &QProcess::readyRead, this, &CmdInterface::readyRead);
  connect(&proc, &QProcess::readyReadStandardOutput, this,
          &CmdInterface::readyRead);
  connect(&proc, &QProcess::readyReadStandardError, this,
          &CmdInterface::readyRead);
}

CmdInterface::~CmdInterface() {
  if (proc.isOpen())
    proc.terminate();
}

void CmdInterface::readyRead() {
  qint64 value = 0;
  do {
    QByteArray line = proc.readAll();
    qDebug() << line.trimmed();
    value = line.length();
  } while (value > 0);
}

void CmdInterface::action(QByteArray data) {
  if (!data.endsWith(endl.toLatin1())) {
    for (auto ch : endl)
      data.append(ch.toLatin1());
  }
  proc.write(data);
  proc.waitForBytesWritten(1000);
}
