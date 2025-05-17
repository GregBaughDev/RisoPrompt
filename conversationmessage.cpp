#include "conversationmessage.h"

ConversationMessage::ConversationMessage(const QString message, const MessageAuthor author)
{
    mMessage = message;
    mAuthor = author;
}

QString ConversationMessage::message() const
{
    return mMessage;
}

MessageAuthor ConversationMessage::author() const
{
    return mAuthor;
}
