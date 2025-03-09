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

// new button isn't working now
// allow to highlight the responses
// save and copy button functionality
// make and set an icon
// consolidate styling into one place
// remove all debugs
// some sort of error handling/modal
// find a way to set/change the model and api key without having to rebuild
// code review -> make sure m_ appended, check const correctness, check pass by reference on methods etc
