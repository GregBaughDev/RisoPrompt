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

// wip -> save button w/ sqlite
    // save -> show dialog and allow the user to store it with a name
    // load -> show dialog and allow the user to select chat
        // overwrite flows etc
    // probs have a class that handles interacting with the db
    // connect to sqllite
    // how should we store the data -> each row individually?
    // conversation_name, author, message, datetime, conversation_id, sequence
    // serialize/deserialize to required types from DB

// allow to highlight the responses
// consolidate styling into one place
// output debugs to a file
// some sort of error handling/modal
// allow updating the api key w/out rebuilding
// sort styling on scrollbar
// maybe call the list models function and display them in a dropdown instead of having to type in the model name
// code review -> make sure m_ appended, check const correctness, check pass by reference on methods etc
