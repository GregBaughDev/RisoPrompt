#include "promptrequest.h"

#include <QGrpcChannelOptions>
#include <QClipboard>
#include <QGuiApplication>
#include <persistencemanager.h>

PromptRequest::PromptRequest(QObject *parent) : QObject(parent)
{
    initialiseGRPCChannelAndClient();
    this->resetContents();
}

void PromptRequest::sendPromptRequest(const QString &prompt)
{
    this->addContentToCurrentContext(prompt, MessageAuthor::USER);

    GenerateContentRequest req;
    req.setContents(mContents);
    req.setModel(mModel);

    emit isLoading();
    std::unique_ptr<QGrpcCallReply> reply = mClient.GenerateContent(req);
    const auto *replyPtr = reply.get();
    QObject::connect(
        replyPtr, &QGrpcCallReply::finished, replyPtr,
        [reply = std::move(reply), this](const QGrpcStatus &status)
        {
            if (status.isOk())
            {
                if (const auto response = reply->read<GenerateContentResponse>())
                {
                    this->addContentToCurrentContext(response.value().candidates().at(0).content().parts().at(0).text(), MessageAuthor::MODEL);
                    emit promptResponseReceived(response.value().candidates().at(0).content().parts().at(0).text(), MessageAuthor::MODEL);
                }
                else
                {
                    qCritical() << "Client deserialization failed!";
                }
            }
            else
            {
                qCritical() << "Client failed" << status;
            }
            emit isLoading();
        });
}

void PromptRequest::addContentToCurrentContext(const QString &contents, const MessageAuthor &author)
{
    Part part;
    QList<Part> parts;
    Content content;

    part.setText(contents);
    parts.append(part);
    content.setParts(parts);
    content.setRole(author == MessageAuthor::MODEL ? "Model" : "User");
    mContents.append(content);
}

void PromptRequest::resetContents()
{
    mContents.clear();
    this->addContentToCurrentContext("Do not include markdown in any of your responses", MessageAuthor::USER);
    qInfo() << "Messages cleared";
}

void PromptRequest::setNewModel(const QString &model)
{
    this->mModel = model;
    qInfo() << "Model changed:" << model;
}

void PromptRequest::setNewApiKey(const QString &apiKey)
{
    this->mApiKey = apiKey;
    qInfo() << "Api key updated";
    initialiseGRPCChannelAndClient();
}

void PromptRequest::copyMessagesToClipboard()
{
    QString text;

    for (int i = 1; i < mContents.count(); i++)
    {
        text += "Role: ";
        text += mContents.at(i).role();
        text += " : ";
        text += mContents.at(i).parts().at(0).text();
        text += "\n";
    }

    QGuiApplication::clipboard()->setText(text);
}

void PromptRequest::saveMessagesToDB(const QString &conversationName)
{
    for (int i = 0; i < mContents.count(); i++)
    {
        PersistenceManager::insertConversationMessage(conversationName, mContents.at(i).role(), mContents.at(i).parts().at(0).text(), i);
    }
}

void PromptRequest::loadConversation(const QString &conversationName)
{
    // reset contents
    mContents.clear();

    // load conversation
    QList<StoredConversationMessage> storedMessages = PersistenceManager::loadConversation(conversationName);

    for (int i = 0; i < storedMessages.count(); i++)
    {
        this->addContentToCurrentContext(storedMessages.at(i).message, storedMessages.at(i).author);

        if (i != 0) // first message sets context so we don't want to display it to the user
        {
            emit promptResponseReceived(storedMessages.at(i).message, storedMessages.at(i).author);
        }
    }
}

void PromptRequest::initialiseGRPCChannelAndClient()
{
    qInfo() << "Initialising GRPC channel and client...";

    QHash<QByteArray, QByteArray> optionsMetadata{};
    optionsMetadata["content-type"] = "application/x-protobuf";
    optionsMetadata["X-Goog-Api-Key"] = mApiKey.toUtf8();

    mChannel = std::make_shared<QGrpcHttp2Channel>(
        QUrl("https://generativelanguage.googleapis.com/google.ai.generativelanguage.v1/GenerateContent"),
        QGrpcChannelOptions().setMetadata(optionsMetadata));
    mClient.attachChannel(mChannel);

    qInfo() << "initialisation complete";
}
