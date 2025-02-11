#ifndef CUSTOMPLAINTEXT_H
#define CUSTOMPLAINTEXT_H

#include <QPlainTextEdit>

class CustomPlainText : public QPlainTextEdit
{
    Q_OBJECT
public:
    CustomPlainText(QWidget *parent);
    void keyPressEvent(QKeyEvent *event);

signals:
    void textSubmit(QString newValue);
};

#endif // CUSTOMPLAINTEXT_H
