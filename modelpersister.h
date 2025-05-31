#ifndef MODELPERSISTER_H
#define MODELPERSISTER_H

#include <QGrpcChannelOptions>
#include <QtGrpc/QGrpcHttp2Channel>
#include <QStringList>
#include "persistencemanager.h"
#include "./proto/generated/google/ai/generativelanguage/v1/model_service_client.grpc.qpb.h"

using namespace google::ai::generativelanguage::v1;

class ModelPersister
{
    ModelService::Client mClient;
    std::shared_ptr<QAbstractGrpcChannel> mChannel;
    ModelConfig mModelConfig;
    QStringList mModels;

public:
    ModelPersister();
    void persistModels();
    QStringList getModels();
    void setModelConfig(const ModelConfig &config);
};

#endif // MODELPERSISTER_H
