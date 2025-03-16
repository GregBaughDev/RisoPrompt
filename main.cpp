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

// allow to highlight the responses
// save and copy button functionality
// consolidate styling into one place
// remove all debugs
// some sort of error handling/modal
// save functionality and integrate with sqlite
// sort styling on scrollbar
// maybe call the list models function and display them in a dropdown instead of having to type in the model name
// code review -> make sure m_ appended, check const correctness, check pass by reference on methods etc
