#include "messagedelegate.h"

#include "conversationmessage.h"

MessageDelegate::MessageDelegate(QObject *parent) : QStyledItemDelegate{parent} {};

void MessageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    QFont font = painter->font();
    font.setPixelSize(25);
    painter->setFont(font);

    ConversationMessage message = index.data().value<ConversationMessage>();

    switch (message.author())
    {
        case MessageAuthor::USER:
            painter->setPen(QColor(255, 232, 0)); // change the colour into a var
            painter->drawText(option.rect.adjusted(0, 0, 10, 10), Qt::AlignLeft | Qt::TextWordWrap, message.message());
            break;
        case MessageAuthor::PROMPT:
            painter->setPen(QColor(35, 91, 168));
            painter->drawText(option.rect.adjusted(0, 0, 10, 10), Qt::AlignRight | Qt::TextWordWrap, message.message());
            break;
    }
}

QSize MessageDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    QFontMetrics fm(option.font);
    int height = fm.height() * 2;
    return QSize(option.rect.height(), height);
}
