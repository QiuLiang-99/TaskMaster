#include "mydelegate.h"

MyDelegate::MyDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    painter->save();

    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    // Draw item background
    QStyledItemDelegate::paint(painter, opt, index);

    // Get the text from the model
    QString text = index.model()->data(index, Qt::DisplayRole).toString();

    // Split the text into lines
    QStringList lines = text.split("\n");

    // Calculate the height of each line
    int lineHeight = option.rect.height() / lines.size();

    // Define the colors
    QList<QColor> colors = {Qt::transparent, Qt::red, QColorConstants::Svg::orange, Qt::yellow, Qt::green, Qt::blue, QColorConstants::Svg::indigo, QColorConstants::Svg::violet};

    // Draw each line with a different background color
    for (int i = 0; i < lines.size(); ++i) {
        QRect lineRect(option.rect.left(), option.rect.top() + i * lineHeight, option.rect.width(), lineHeight);
        painter->fillRect(lineRect, colors[i % colors.size()]);
        painter->drawText(lineRect, Qt::AlignCenter, lines[i]);
    }

    painter->restore();
}
