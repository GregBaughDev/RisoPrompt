#include "risoprompt.h"
#include "ui_risoprompt.h"

#include <QDebug>
#include "./customplaintext.h"
#include "./conversationwidget.h"

RisoPrompt::RisoPrompt(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::RisoPrompt)
{
    ui->setupUi(this);
    ui->progressBar->setVisible(false);

    // connect buttons
    connect(ui->newButton, &QPushButton::clicked, this, &RisoPrompt::onNewButtonClicked);
    connect(ui->copyButton, &QPushButton::clicked, this, &RisoPrompt::onCopyButtonClicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &RisoPrompt::onSaveButtonClicked);

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
}

RisoPrompt::~RisoPrompt()
{
    delete ui;
}

void RisoPrompt::onSaveButtonClicked()
{
    // todo
}

void RisoPrompt::onCopyButtonClicked()
{
    // todo
}

void RisoPrompt::onNewButtonClicked()
{
    emit newButtonClicked();
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
