#ifndef CUSTOMPLAINTEXT_H
#define CUSTOMPLAINTEXT_H

#include <QPlainTextEdit>
#include "./conversationmessage.h"

class CustomPlainText : public QPlainTextEdit
{
    Q_OBJECT
public:
    CustomPlainText(QWidget *parent);
    void keyPressEvent(QKeyEvent *event);

signals:
    void textSubmit(const QString &newValue, const MessageAuthor &author);
};

#endif // CUSTOMPLAINTEXT_H
