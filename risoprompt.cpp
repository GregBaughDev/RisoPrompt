#include "risoprompt.h"
#include "ui_risoprompt.h"

#include <QDebug>
#include <QProcessEnvironment>
#include <QSqlError>
#include "./customplaintext.h"
#include "./conversationwidget.h"
#include "./modelconfigdialog.h"
#include "./saveconversationdialog.h"
#include "./loadconversationdialog.h"

QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

RisoPrompt::RisoPrompt(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::RisoPrompt),
    mPersistenceManager{parent}
{
    ui->setupUi(this);
    ui->progressBar->setVisible(false);

    try
    {
        PersistenceManager::initiateDBConnection();
    }
    catch (const QSqlError &e)
    {
        qCritical() << "Exception caught:" << e;
        qCritical() << "Closing application";
        throw;
    }

    mModelConfig = PersistenceManager::loadModelConfig();

    if (mModelConfig.model == nullptr || mModelConfig.apiKey == nullptr)
    {
        qWarning() << "Model configuration has missing values";
        this->onModelButtonClicked();
    }

    promptRequest.setNewApiKey(mModelConfig.apiKey);
    promptRequest.setNewModel(mModelConfig.model);

    mModelPersister.setModelConfig(mModelConfig);
    mModelPersister.persistModels();

    connect(ui->newButton, &QPushButton::clicked, this, &RisoPrompt::onNewButtonClicked);
    connect(ui->copyButton, &QPushButton::clicked, this, &RisoPrompt::onCopyButtonClicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &RisoPrompt::onSaveButtonClicked);
    connect(ui->modelButton, &QPushButton::clicked, this, &RisoPrompt::onModelButtonClicked);
    connect(ui->loadButton, &QPushButton::clicked, this, &RisoPrompt::onLoadButtonClicked);

    // handle user input
    connect(ui->promptInput, &CustomPlainText::textSubmit, ui->conversationWidget, &ConversationWidget::addMessage);
    connect(ui->promptInput, &CustomPlainText::textSubmit, &this->promptRequest, &PromptRequest::sendPromptRequest);

    // handle prompt response
    connect(&this->promptRequest, &PromptRequest::promptResponseReceived, ui->conversationWidget, &ConversationWidget::addMessage);

    // handle new button clicked
    connect(this, &RisoPrompt::newButtonClicked, &this->promptRequest, &PromptRequest::resetContents);
    connect(this, &RisoPrompt::newButtonClicked, ui->conversationWidget, &ConversationWidget::clearMessages);

    // toggle loading
    connect(&this->promptRequest, &PromptRequest::isLoading, this, &RisoPrompt::toggleLoading);
    connect(&this->promptRequest, &PromptRequest::isLoading, this, &RisoPrompt::toggleTextEntry);

    // handle copy button clicked
    connect(this, &RisoPrompt::copyButtonClicked, &this->promptRequest, &PromptRequest::copyMessagesToClipboard);
}

RisoPrompt::~RisoPrompt()
{
    delete ui;
}

void RisoPrompt::onModelButtonClicked()
{
    ModelConfigDialog dialog{this, this->mModelConfig, this->mModelPersister.getModels()};

    connect(&dialog, &ModelConfigDialog::modelChanged, &this->promptRequest, &PromptRequest::setNewModel);
    connect(&dialog, &ModelConfigDialog::modelChanged, &this->mPersistenceManager, &PersistenceManager::persistModel);
    connect(&dialog, &ModelConfigDialog::modelChanged, this, &RisoPrompt::setNewModel);
    connect(&dialog, &ModelConfigDialog::apiKeyChanged, &this->promptRequest, &PromptRequest::setNewApiKey);
    connect(&dialog, &ModelConfigDialog::apiKeyChanged, &this->mPersistenceManager, &PersistenceManager::persistApiKey);
    connect(&dialog, &ModelConfigDialog::apiKeyChanged, this, &RisoPrompt::setNewApiKey);

    dialog.exec();
}

void RisoPrompt::onCopyButtonClicked()
{
    emit copyButtonClicked();
}

void RisoPrompt::onNewButtonClicked()
{
    mPersistenceManager.setActiveConversation("");
    emit newButtonClicked();
}

void RisoPrompt::onSaveButtonClicked()
{
    SaveConversationDialog dialog{this, mPersistenceManager.getActiveConversationName()};

    // the below is a bit hacky, but the below deletes the current conversation (if it exists) in the DB before storing the updated version
    connect(&dialog, &SaveConversationDialog::conversationSaved, &this->mPersistenceManager, &PersistenceManager::deleteConversation);
    connect(&dialog, &SaveConversationDialog::conversationSaved, &this->promptRequest, &PromptRequest::saveMessagesToDB);
    connect(&dialog, &SaveConversationDialog::conversationSaved, &this->mPersistenceManager, &PersistenceManager::setActiveConversation);
    dialog.exec();
}

void RisoPrompt::toggleLoading()
{
    if (ui->progressBar->isVisible())
    {
        ui->progressBar->setVisible(false);
    }
    else
    {
        ui->progressBar->setVisible(true);
    }
}

void RisoPrompt::toggleTextEntry()
{
    if (ui->promptInput->isReadOnly())
    {
        ui->promptInput->setReadOnly(false);
        ui->promptInput->setVisible(true);
    }
    else
    {
        ui->promptInput->setReadOnly(true);
        ui->promptInput->setVisible(false);
    }
}

void RisoPrompt::onLoadButtonClicked()
{
    LoadConversationDialog dialog{this};

    connect(&dialog, &LoadConversationDialog::conversationDeleted, &this->mPersistenceManager, &PersistenceManager::deleteConversation);
    connect(&dialog, &LoadConversationDialog::conversationLoaded, ui->conversationWidget, &ConversationWidget::clearMessages);
    connect(&dialog, &LoadConversationDialog::conversationLoaded, &this->promptRequest, &PromptRequest::loadConversation);
    connect(&dialog, &LoadConversationDialog::conversationLoaded, &this->mPersistenceManager, &PersistenceManager::setActiveConversation);

    dialog.exec();
}

void RisoPrompt::setNewModel(const QString &model)
{
    mModelConfig.model = model;
}

void RisoPrompt::setNewApiKey(const QString &key)
{
    mModelConfig.apiKey = key;
}
