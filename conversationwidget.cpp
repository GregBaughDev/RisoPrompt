#include "conversationwidget.h"
#include "messagedelegate.h"

ConversationWidget::ConversationWidget(QWidget *parent) : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this); // should this be QTPointer?

    listView = new QListView(this);
    model = new ConversationModel(this);
    listView->setModel(model);
    listView->setItemDelegate(new MessageDelegate(this));
    listView->setFrameStyle(QFrame::NoFrame);
    listView->setWordWrap(true);
    layout->addWidget(listView);
    setLayout(layout);
}


void ConversationWidget::addMessage(const QString &message, const MessageAuthor &author)
{
    model->addMessage(message, author);
    listView->scrollToBottom();
}
