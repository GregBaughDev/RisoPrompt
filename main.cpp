#include "risoprompt.h"

#include <QApplication>
#include <QFile>
#include "conversationmessage.h"

QtMessageHandler originalHandler = nullptr;

void logToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    qSetMessagePattern("%{time yyyyMMdd h:mm:ss.zzz ttt} %{type} %{file}:%{line} - %{message}\n");
    QString message = qFormatLogMessage(type, context, msg);
    QFile *f = new QFile("risopromptlog.txt");
    f->open(QIODevice::WriteOnly | QIODevice::Append);
    f->write(message.toStdString().c_str(), message.length());
    f->flush();

    if (originalHandler)
        originalHandler(type, context, msg);
}

int main(int argc, char *argv[])
{
    qRegisterMetaType<ConversationMessage>("ConversationMessage");
    originalHandler = qInstallMessageHandler(logToFile);
    QApplication a(argc, argv);
    RisoPrompt w;
    w.show();
    return a.exec();
}

// to do
// follow up: get the list of available models and display as drop down
