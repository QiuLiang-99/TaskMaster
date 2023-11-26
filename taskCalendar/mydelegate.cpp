// MyDelegate.cpp
#include "MyDelegate.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QMessageBox>

MyDelegate::MyDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyledItemDelegate::paint(painter, option, index);

    // 创建一个QWidget作为单元格的内容
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);

    // 创建并添加多个QLabel到QWidget
    for (int j = 0; j < 3; ++j) {
        QLabel *label = new QLabel(QString("文本%1").arg(j));
        label->setStyleSheet(QString("background-color: %1").arg(j % 2 == 0 ? "red" : "blue"));
        layout->addWidget(label);
    }

    // 将QWidget添加到QTableWidgetItem
    //QTableWidgetItem *item = new QTableWidgetItem();
    //tableWidget->setItem(i, 0, item);
    //tableWidget->setCellWidget(i, 0, widget);
}
