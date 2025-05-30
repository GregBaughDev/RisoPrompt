#ifndef CONVERSATIONWIDGET_H
#define CONVERSATIONWIDGET_H

#include <QWidget>
#include <QListView>
#include <QVBoxLayout>
#include "conversationmodel.h"
#include "conversationmessage.h"

class ConversationWidget : public QWidget
{
    Q_OBJECT

public:
    ConversationWidget(QWidget *parent = nullptr);

public slots:
    void addMessage(const QString &message, const MessageAuthor &author);
    void clearMessages();

private:
    QListView *mListView;
    ConversationModel *mModel;
};

#endif // CONVERSATIONWIDGET_H
