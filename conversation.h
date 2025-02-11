#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <vector>
#include <QObject>

enum MessageAuthor { USER, PROMPT };

typedef struct ConversationMessage {
    std::string message;
    MessageAuthor author;
} ConversationMessage;

class Conversation : public QObject
{
    // this will the class that contains the active conversation
    // it will communication with the UI and the external prompt service
    Q_OBJECT

    std::vector<ConversationMessage> history;

public:
    Conversation();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // CONVERSATION_H
