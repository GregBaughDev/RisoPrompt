#include "risoprompt.h"

#include <QApplication>
#include "conversationmessage.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<ConversationMessage>("ConversationMessage");

    QApplication a(argc, argv);
    RisoPrompt w;
    w.show();
    return a.exec();
}

// to do

// sort the type for QVariant
    // We have the type sorted, the styling looks bad now

// sort the type issue when the length spans multiple lines

// network call to prompt
// loading state
// block input until response received

// save, copy & new button functionality

// consolidate styling into one place
// remove all debugs
