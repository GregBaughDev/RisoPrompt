#include "customplaintext.h"
#include <QDebug>

CustomPlainText::CustomPlainText(QWidget *parent)
    : QPlainTextEdit{parent}
{}

void CustomPlainText::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        emit textSubmit(this->toPlainText());
        this->clear();
    }
    else
    {
        QPlainTextEdit::keyPressEvent(event);
    }
}
