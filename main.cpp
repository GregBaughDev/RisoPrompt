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

// block input until response received
// try displaying in a rich text widget
// save and copy button functionality
// make and set an icon
// consolidate styling into one place
// remove all debugs
// code review -> make sure m_ appended, check const correctness, check pass by reference on methods etc
