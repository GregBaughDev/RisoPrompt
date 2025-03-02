#ifndef PROMPTREQUEST_H
#define PROMPTREQUEST_H

#include <QObject>
#include <QtGrpc/QGrpcHttp2Channel>
#include <memory.h>
#include "./proto/generated/google/ai/generativelanguage/v1/generative_service_client.grpc.qpb.h"

class PromptRequest : public QObject
{
    Q_OBJECT
    QUrl m_url;
    QString m_apiKey;
    google::ai::generativelanguage::v1::GenerativeService::Client m_client;
    std::shared_ptr<QAbstractGrpcChannel> m_channel;

public:
    PromptRequest(QObject *parent = nullptr);
    void sendPromptRequest(QString prompt);

private slots:

};

#endif // PROMPTREQUEST_H
