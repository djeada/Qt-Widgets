#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QProcess>
#include <QString>

QByteArray spawnProcess(QString program, QStringList arguments,
                        QString message) {
  QProcess process;
  process.start(program, arguments);

  if (!process.waitForStarted())
    throw std::runtime_error("Process failed to start");

  if (!message.isEmpty()) {
    process.write(message.toUtf8());
    process.closeWriteChannel();
  }

  if (!process.waitForFinished())
    throw std::runtime_error("Process failed to finish");

  auto result = process.readAll();
  qDebug() << process.readAll();
  return result;
}

int main(int argc, char *argv[]) {

  QString program = "ls";
  QStringList arguments = {"-l, -a"};
  QString message;

  try {
    auto result = spawnProcess(program, arguments, message);
    qDebug() << result;
  } catch (std::runtime_error &e) {
    qDebug() << e.what();
  }
}
