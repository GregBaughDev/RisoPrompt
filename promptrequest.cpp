#include "promptrequest.h"

#include <QProcessEnvironment>
#include <QGrpcChannelOptions>
#include <QClipboard>
#include <QGuiApplication>

PromptRequest::PromptRequest(QObject *parent, const QString &model) : QObject(parent), m_model{model}
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

    this->resetContents();
}

void PromptRequest::sendPromptRequest(const QString &prompt)
{
    this->addContentToCurrentContext(prompt, MessageAuthor::USER);

    GenerateContentRequest req;
    req.setContents(m_contents);
    req.setModel(m_model);

    emit isLoading();
    std::unique_ptr<QGrpcCallReply> reply = m_client.GenerateContent(req);
    const auto *replyPtr = reply.get();
    QObject::connect(
        replyPtr, &QGrpcCallReply::finished, replyPtr,
        [reply = std::move(reply), this](const QGrpcStatus &status) {
            if (status.isOk()) {
                if (const auto response = reply->read<GenerateContentResponse>())
                {
                    this->addContentToCurrentContext(response.value().candidates().at(0).content().parts().at(0).text(), MessageAuthor::MODEL);
                    emit promptResponseReceived(response.value().candidates().at(0).content().parts().at(0).text(), MessageAuthor::MODEL);
                }
                else
                {
                    qDebug() << "Client deserialization failed!";
                }
            } else {
                qDebug() << "Client failed" << status;
            }
            emit isLoading();
        }
    );
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
    m_contents.append(content);
}

void PromptRequest::resetContents()
{
    m_contents.clear();
    this->addContentToCurrentContext("Do not include markdown in any of your responses", MessageAuthor::USER);
    qDebug() << "Messages cleared";

}

void PromptRequest::setNewModel(const QString &model)
{
    this->m_model = model;
    qDebug() << "Model changed:" << model;
    emit this->currentModel(m_model);
}

void PromptRequest::copyMessagesToClipboard()
{
    QString text;

    for (int i = 1; i < m_contents.count(); i++)
    {
        text += "Role: ";
        text += m_contents.at(i).role();
        text += " : ";
        text += m_contents.at(i).parts().at(0).text();
        text += "\n";
    }

    QGuiApplication::clipboard()->setText(text);
}



