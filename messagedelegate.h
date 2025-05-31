#ifndef MESSAGEDELEGATE_H
#define MESSAGEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

class MessageDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    const int mMessageSpacing = 5;
    const int mFontSize = 16;
    const QColor mUserMessageColour = QColor(255, 232, 0, 210);
    const QColor mPromptMessageColour = QColor(35, 91, 168, 210);

public:
    MessageDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // MESSAGEDELEGATE_H
