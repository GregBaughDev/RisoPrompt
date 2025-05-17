#ifndef CONVERSATIONMESSAGE_H
#define CONVERSATIONMESSAGE_H

#include <QString>
#include <QtCore/qvariant.h>

enum MessageAuthor { USER, MODEL };

class ConversationMessage
{
public:
    ConversationMessage() = default;
    ~ConversationMessage() = default;
    ConversationMessage(const ConversationMessage &) = default;
    ConversationMessage &operator=(const ConversationMessage &) = default;

    ConversationMessage(const QString message, const MessageAuthor author);
    QString message() const;
    MessageAuthor author() const;

private:
    QString mMessage;
    MessageAuthor mAuthor;
};

Q_DECLARE_METATYPE(ConversationMessage);

#endif // CONVERSATIONMESSAGE_H
