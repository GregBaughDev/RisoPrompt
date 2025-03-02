#include "promptrequest.h"

#include <QProcessEnvironment>
#include <QGrpcChannelOptions>

PromptRequest::PromptRequest(QObject *parent) : QObject(parent)
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    m_url = QUrl(env.value("PROMPT_URL", ""));
    m_apiKey = env.value("API_KEY", "");

    QHash<QByteArray, QByteArray> optionsMetadata {};
    optionsMetadata["content-type"] = "application/x-protobuf";
    optionsMetadata["X-Goog-Api-Key"] = m_apiKey.toUtf8();

    m_channel = std::make_shared<QGrpcHttp2Channel>(
        QUrl("todo"),
        QGrpcChannelOptions().setMetadata(optionsMetadata)
    );
    m_client.attachChannel(std::move(m_channel));
    
}
