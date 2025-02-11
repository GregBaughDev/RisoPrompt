#include "./conversation.h"

#include <QDebug>
#include <QEvent>
#include "./customplaintext.h"

Conversation::Conversation() : QObject() {}

bool Conversation::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return)
        {
            qDebug() << "Ok this should be only key enter event?";
            return true;
        }
    }

    return false;
}
