#include "modelpersister.h"

ModelPersister::ModelPersister() {}

void ModelPersister::persistModels()
{
    qInfo() << "Initialising GRPC channel and client...";

    QHash<QByteArray, QByteArray> optionsMetadata{};
    optionsMetadata["content-type"] = "application/x-protobuf";
    optionsMetadata["X-Goog-Api-Key"] = mModelConfig.apiKey.toUtf8();

    mChannel = std::make_shared<QGrpcHttp2Channel>(
        QUrl("https://generativelanguage.googleapis.com/google.ai.generativelanguage.v1/ListModels"),
        QGrpcChannelOptions().setMetadata(optionsMetadata));
    mClient.attachChannel(mChannel);

    std::unique_ptr<QGrpcCallReply> reply = mClient.ListModels(ListModelsRequest());
    const auto *replyPtr = reply.get();
    QObject::connect(
        replyPtr, &QGrpcCallReply::finished, replyPtr,
        [reply = std::move(reply), this](const QGrpcStatus &status)
        {
            if (status.isOk())
            {
                if (const auto response = reply->read<ListModelsResponse>())
                {
                    for (auto &m : response.value().models())
                    {
                        mModels.append(m.name());
                    }
                }
                else
                {
                    qCritical() << "Client failed" << status;
                }
            }
            else
            {
                qCritical() << "Error querying models:" << status.code();
            }
        });

    qInfo() << "initialisation complete";
}

QStringList ModelPersister::getModels()
{
    return mModels;
}

void ModelPersister::setModelConfig(const ModelConfig &config)
{
    this->mModelConfig = config;
}
