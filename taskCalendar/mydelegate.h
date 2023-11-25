#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

class MyDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    MyDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // MYDELEGATE_H
