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
    void textSubmit(QString newValue, MessageAuthor author);
};

#endif // CUSTOMPLAINTEXT_H
