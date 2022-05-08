#ifndef INSERT_ELEMENT_DIALOG_H
#define INSERT_ELEMENT_DIALOG_H

#include <QDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class InsertElementDialog;
}
QT_END_NAMESPACE

struct InsertElementData {
  int index;
  QString text;
};

class InsertElementDialog : public QDialog {
  Q_OBJECT

public:
  InsertElementDialog(QWidget *parent = nullptr);
  ~InsertElementDialog();
  void setMaxIndex(int maxIndex);

signals:
  void elementSelected(InsertElementData data);

private:
  Ui::InsertElementDialog *ui;
};
#endif // INSERT_ELEMENT_DIALOG_H
