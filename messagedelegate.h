#ifndef MESSAGEDELEGATE_H
#define MESSAGEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

class MessageDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    const int messageSpacing = 20;
    const int fontSize = 25;
    const QColor userMessageColour = QColor(255, 232, 0);
    const QColor promptMessageColour = QColor(35, 91, 168);

public:
    MessageDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // MESSAGEDELEGATE_H
