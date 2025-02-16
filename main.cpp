#include "risoprompt.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RisoPrompt w;
    w.show();
    return a.exec();
}

// to do

// sort the type for QVariant
// sort the type issue when the length spans multiple lines

// network call to prompt
// loading state
// block input until response received

// save, copy & new button functionality

// consolidate styling into one place
