#include <QObject>
#include <QProcess>
#include <QString>

#ifdef __linux__
const QString endl("\n");
#elif _WIN32
const QString endl("\r\n");
#else
const QString endl("\r");
#endif

class CmdInterface : public QObject {
  Q_OBJECT
public:
  CmdInterface(QObject *parent = nullptr);
  ~CmdInterface();
signals:

public slots:
  void readyRead();
  void action(QByteArray data);

private:
  QProcess proc;
};
