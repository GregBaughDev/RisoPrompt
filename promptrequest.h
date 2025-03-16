#ifndef PROMPTREQUEST_H
#define PROMPTREQUEST_H

#include <QObject>
#include <QtGrpc/QGrpcHttp2Channel>
#include <memory.h>
#include "./proto/generated/google/ai/generativelanguage/v1/generative_service_client.grpc.qpb.h"
#include "./conversationmessage.h"

using namespace google::ai::generativelanguage::v1;

// todo rename this class to something else
class PromptRequest : public QObject
{
    Q_OBJECT
    GenerativeService::Client m_client;
    std::shared_ptr<QAbstractGrpcChannel> m_channel;
    QList<Content> m_contents;
    QString m_model;
    void addContentToCurrentContext(const QString &prompt, const MessageAuthor &author);

public:
    PromptRequest(QObject *parent = nullptr, const QString &model = nullptr);

public slots:
    void sendPromptRequest(const QString &prompt);
    void resetContents();
    void setNewModel(const QString &model);
    void copyMessagesToClipboard();

signals:
    void promptResponseReceived(const QString &contents, const MessageAuthor &author);
    void isLoading();
    void currentModel(const QString &currentModel);
};

#endif // PROMPTREQUEST_H
