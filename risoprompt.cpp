#include "risoprompt.h"
#include "ui_risoprompt.h"

#include <QDebug>
#include "./customplaintext.h"
#include "./conversationwidget.h"
#include "./modelconfigdialog.h"
#include "./saveconversationdialog.h"
#include "./loadconversationdialog.h"
#include "./DBUtils.cpp"

RisoPrompt::RisoPrompt(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::RisoPrompt), promptRequest(parent, "models/gemini-1.5-pro")
{
    ui->setupUi(this);
    ui->progressBar->setVisible(false);
    this->m_promptModel = "models/gemini-1.5-pro";

    DBUtils::initiateDBConnection();

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
    connect(&this->promptRequest, &PromptRequest::currentModel, this, &RisoPrompt::setPromptModel);

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
    ModelConfigDialog dialog{this, this->m_promptModel};

    connect(&dialog, &ModelConfigDialog::modelChanged, &this->promptRequest, &PromptRequest::setNewModel);
    connect(&dialog, &ModelConfigDialog::modelChanged, &this->promptRequest, &PromptRequest::resetContents);
    connect(&dialog, &ModelConfigDialog::modelChanged, ui->conversationWidget, &ConversationWidget::clearMessages);
    dialog.exec();
}

void RisoPrompt::onCopyButtonClicked()
{
    emit copyButtonClicked();
}

void RisoPrompt::onNewButtonClicked()
{
    emit newButtonClicked();
}

void RisoPrompt::onSaveButtonClicked()
{
    SaveConversationDialog dialog{this};
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
    }
    else
    {
        ui->promptInput->setReadOnly(true);
    }
}

void RisoPrompt::setPromptModel(const QString &promptModel)
{
    this->m_promptModel = promptModel;
}

void RisoPrompt::onLoadButtonClicked()
{
    LoadConversationDialog dialog{this};
    dialog.exec();
}
