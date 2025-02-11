#include "risoprompt.h"

#include <QApplication>
#include "./conversation.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RisoPrompt w;
    std::unique_ptr<Conversation> conversation = std::make_unique<Conversation>();

    w.installEventFilter(conversation.get());
    w.show();
    return a.exec();
}
