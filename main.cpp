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

// output debugs to a file
// consolidate styling into one place
// allow updating the api key w/out rebuilding
// code review -> make sure "m" appended (and camel cased OR snake cased), check const correctness, check pass by reference on methods etc
