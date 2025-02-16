#ifndef CONVERSATIONMESSAGE_H
#define CONVERSATIONMESSAGE_H

#include <QString>
#include <QtCore/qvariant.h>

enum MessageAuthor { USER, PROMPT };

class ConversationMessage
{
public:
    ConversationMessage() = default;
    ~ConversationMessage() = default;
    ConversationMessage(const ConversationMessage &) = default;
    ConversationMessage &operator=(const ConversationMessage &) = default;

    //ConversationMessage(const QString message, const MessageAuthor author);
    ConversationMessage(const QString message);

    QString message() const;
    MessageAuthor author() const;

private:
    QString m_message;
    MessageAuthor m_author;
};

// Q_DECLARE_METATYPE(ConversationMessage);

#endif // CONVERSATIONMESSAGE_H
