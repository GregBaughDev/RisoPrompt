#include "promptrequest.h"

#include <QProcessEnvironment>
#include <QGrpcChannelOptions>

PromptRequest::PromptRequest(QObject *parent) : QObject(parent)
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    QHash<QByteArray, QByteArray> optionsMetadata {};
    optionsMetadata["content-type"] = "application/x-protobuf";
    optionsMetadata["X-Goog-Api-Key"] = env.value("API_KEY", "").toUtf8();

    m_channel = std::make_shared<QGrpcHttp2Channel>(
        QUrl("https://generativelanguage.googleapis.com/google.ai.generativelanguage.v1/GenerateContent"),
        QGrpcChannelOptions().setMetadata(optionsMetadata)
    );
    m_client.attachChannel(m_channel);

    this->addContentToCurrentContext("Do not include markdown in any of your responses", MessageAuthor::USER);
}

void PromptRequest::sendPromptRequest(const QString &prompt)
{
    this->addContentToCurrentContext(prompt, MessageAuthor::USER);

    GenerateContentRequest req;
    req.setContents(m_contents);
    req.setModel("models/gemini-1.5-flash");

    std::unique_ptr<QGrpcCallReply> reply = m_client.GenerateContent(req);
    const auto *replyPtr = reply.get();
    QObject::connect(
        replyPtr, &QGrpcCallReply::finished, replyPtr,
        [reply = std::move(reply), this](const QGrpcStatus &status) {
            if (status.isOk()) {
                if (const auto response = reply->read<GenerateContentResponse>())
                    emit promptResponseReceived(response.value().candidates().at(0).content().parts().at(0).text(), MessageAuthor::MODEL);
                else
                    qDebug() << "Client deserialization failed!";
            } else {
                qDebug() << "Client failed" << status;
            }
        }
    );
}

void PromptRequest::addContentToCurrentContext(const QString &prompt, const MessageAuthor &author)
{
    Part part;
    QList<Part> parts;
    Content content;

    part.setText(prompt);
    parts.append(part);
    content.setParts(parts);
    content.setRole(author == MessageAuthor::MODEL ? "Model" : "User");
    m_contents.append(content);
}



