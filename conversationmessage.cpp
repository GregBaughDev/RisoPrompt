#include "conversationmessage.h"

// ConversationMessage::ConversationMessage(const QString message, const MessageAuthor author)
// {
//     m_message = message;
//     m_author = author;
// }

ConversationMessage::ConversationMessage(const QString message)
{
    m_message = message;
    m_author = MessageAuthor::USER;
}

QString ConversationMessage::message() const
{
    return m_message;
}

MessageAuthor ConversationMessage::author() const
{
    return m_author;
}
