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

// wip -> save & load w/ sqlite
    // delete flow
    // flows for discarding unsaved changes
    // prompt to save when there's unsaved changes?

// allow to highlight the responses
// consolidate styling into one place
// output debugs to a file
// some sort of error handling/modal
// allow updating the api key w/out rebuilding
// maybe call the list models function and display them in a dropdown instead of having to type in the model name
// code review -> make sure m_ appended, check const correctness, check pass by reference on methods etc
