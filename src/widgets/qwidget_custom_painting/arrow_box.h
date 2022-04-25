#ifndef ARROWBOX_H
#define ARROWBOX_H

#include <QWidget>

class ArrowBox : public QWidget
{
    Q_OBJECT
public:
    explicit ArrowBox(QWidget *parent = nullptr);

protected:
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent *e);

};

#endif // ARROWBOX_H
