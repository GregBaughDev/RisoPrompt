#include "conversationwidget.h"
#include "messagedelegate.h"

ConversationWidget::ConversationWidget(QWidget *parent) : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    mListView = new QListView(this);
    mModel = new ConversationModel(this);
    mListView->setModel(mModel);
    mListView->setItemDelegate(new MessageDelegate(this));
    mListView->setFrameStyle(QFrame::NoFrame);
    mListView->setWordWrap(true);
    layout->addWidget(mListView);
    setLayout(layout);
}

void ConversationWidget::addMessage(const QString &message, const MessageAuthor &author)
{
    mModel->addMessage(message, author);
}

void ConversationWidget::clearMessages()
{
    mModel->resetMessages();
}
