#ifndef PROMPTREQUEST_H
#define PROMPTREQUEST_H

#include <QObject>
#include <QtGrpc/QGrpcHttp2Channel>
#include <memory.h>
#include "./proto/generated/google/ai/generativelanguage/v1/generative_service_client.grpc.qpb.h"
#include "./conversationmessage.h"

using namespace google::ai::generativelanguage::v1;

class PromptRequest : public QObject
{
    Q_OBJECT
    GenerativeService::Client mClient;
    std::shared_ptr<QAbstractGrpcChannel> mChannel;
    QList<Content> mContents;
    QString mModel;
    QString mApiKey;
    void addContentToCurrentContext(const QString &prompt, const MessageAuthor &author);
    void initialiseGRPCChannelAndClient();

public:
    PromptRequest(QObject *parent = nullptr);

public slots:
    void sendPromptRequest(const QString &prompt);
    void resetContents();
    void setNewModel(const QString &model);
    void setNewApiKey(const QString &apiKey);
    void copyMessagesToClipboard();
    void saveMessagesToDB(const QString &conversationName);
    void loadConversation(const QString &conversationName);

signals:
    void promptResponseReceived(const QString &contents, const MessageAuthor &author);
    void isLoading();
};

#endif // PROMPTREQUEST_H
