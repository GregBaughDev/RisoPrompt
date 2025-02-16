#include "messagedelegate.h"

#include <QDebug>

MessageDelegate::MessageDelegate(QObject *parent) : QStyledItemDelegate{parent} {};

void MessageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    painter->setPen(QColor(255, 232, 0)); // change the colour
    QFont font = painter->font();
    font.setPixelSize(25);
    painter->setFont(font);
    painter->drawText(option.rect.adjusted(0, 0, 10, 10), Qt::AlignLeft | Qt::TextWordWrap, index.data().toString());
}

QSize MessageDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    QFontMetrics fm(option.font);
    int height = fm.height() * 2;
    return QSize(option.rect.height(), height);
}
