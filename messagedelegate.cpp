#include "messagedelegate.h"

#include "conversationmessage.h"

MessageDelegate::MessageDelegate(QObject *parent) : QStyledItemDelegate{parent} {};

void MessageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    QFont font = painter->font();
    font.setPixelSize(mFontSize);
    painter->setFont(font);

    ConversationMessage message = index.data().value<ConversationMessage>();

    switch (message.author())
    {
        case MessageAuthor::USER:
            painter->setPen(mUserMessageColour);
            painter->drawText(option.rect, Qt::AlignLeft | Qt::TextWordWrap, message.message());
            break;
        case MessageAuthor::MODEL:
            painter->setPen(mPromptMessageColour);
            painter->drawText(option.rect, Qt::AlignLeft | Qt::TextWordWrap, message.message());
            break;
    }

    painter->restore();
}

QSize MessageDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString message = index.data().value<ConversationMessage>().message();

    QFont font = option.font;
    font.setPixelSize(mFontSize);
    QFontMetrics fm(font);

    QRect textRect = fm.boundingRect(QRect(0, 0, option.rect.width(), 0), Qt::TextWordWrap | Qt::AlignLeft, message);
    return QSize(option.rect.width(), textRect.height() + mMessageSpacing);
}
