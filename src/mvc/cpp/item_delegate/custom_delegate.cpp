#include "custom_delegate.h"
#include <QLineEdit>
#include <QPainter>
#include <QProgressBar>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>

CustomDelegate::CustomDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}


CustomDelegate::~CustomDelegate()
{

}


void CustomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto row = index.row();

    switch (row) {
    case 1:{ 
        // create QProgressBar
        auto progressBar = new QProgressBar();
        progressBar->setGeometry(option.rect);
        progressBar->setValue(index.data().toInt());
        progressBar->setTextVisible(false);
        progressBar->setStyleSheet("QProgressBar::chunk { background-color: #006400; }");
        QPixmap pixmap(option.rect.size());
        progressBar->render(&pixmap);
        painter->drawPixmap(option.rect, pixmap);
        break;
    }
    case 3:{
        auto oldPen = painter->pen();
        QPen pen(QColor("#FFD700"), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
                    painter->setPen(pen);
                                        painter->setBrush(QColor("#FFD700"));
                                        painter->setRenderHint(QPainter::Antialiasing);

    painter->drawRect(option.rect.center().x() - 30, option.rect.center().y() -10, 20, 20);
    painter->drawRect(option.rect.center().x() + 10, option.rect.center().y() -10, 20, 20);
    painter->setPen(oldPen);

        break;
    }
    default: {
     // draw background blue
        painter->fillRect(option.rect, QColor(176,224,230));
        // ceter text
        auto text = index.data().toString();
        auto rect = option.rect;
        auto textRect = painter->boundingRect(rect, Qt::AlignCenter, text);
        textRect.moveCenter(rect.center());
        painter->drawText(textRect, Qt::AlignCenter, text);
        return;
    }
    }

}


QSize CustomDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // make it twice as long as the default
    auto originalSize = QStyledItemDelegate::sizeHint(option, index);
    return QSize(originalSize.width() , originalSize.height() * 2);
}


QWidget *CustomDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto row = index.row();
    switch (row) {
    case 1: {
        auto dialog = new QDialog(parent);
        dialog->setWindowFlags(Qt::Popup);
        auto slider = new QSlider(Qt::Horizontal);
        slider->setRange(0, 100);
        slider->setValue(index.data().toInt());
        slider->setTickPosition(QSlider::TicksBothSides);
        slider->setTickInterval(10);
        dialog ->setLayout(new QVBoxLayout);
        dialog->layout()->addWidget(slider);
        return dialog;
    }
    case 3: {
        return nullptr;
    }
    default: {
          auto editor = new QLineEdit(parent);
        editor->setText(index.data().toString());
        return editor;
    }
    }
}

void CustomDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

    auto row = index.row();
    switch (row) {
    case 1: {
        auto dialog = qobject_cast<QDialog*>(editor);
        auto slider = qobject_cast<QSlider*>(dialog->findChild<QSlider*>());
        model->setData(index, slider->value());
        return;
    }
    default: {
        auto lineEdit = qobject_cast<QLineEdit*>(editor);
        model->setData(index, lineEdit->text());
        return;
            }
    }

}

