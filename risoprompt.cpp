#include "risoprompt.h"
#include "ui_risoprompt.h"

#include <QDebug>
#include "./customplaintext.h"
#include "./conversationwidget.h"

RisoPrompt::RisoPrompt(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::RisoPrompt)
{
    ui->setupUi(this);

    // handle user input
    connect(ui->promptInput, &CustomPlainText::textSubmit, ui->conversationWidget, &ConversationWidget::addMessage);
    connect(ui->promptInput, &CustomPlainText::textSubmit, &this->promptRequest, &PromptRequest::sendPromptRequest);

    // handle prompt response
    connect(&this->promptRequest, &PromptRequest::promptResponseReceived, ui->conversationWidget, &ConversationWidget::addMessage);

    // handle new button clicked
    connect(this, &RisoPrompt::newButtonClicked, &this->promptRequest, &PromptRequest::resetContents);
    connect(this, &RisoPrompt::newButtonClicked, ui->conversationWidget, &ConversationWidget::clearMessages);
}

RisoPrompt::~RisoPrompt()
{
    delete ui;
}

void RisoPrompt::on_saveButton_clicked()
{
    // todo
}

void RisoPrompt::on_copyButton_clicked()
{
    // todo
}

void RisoPrompt::on_newButton_clicked()
{
    emit newButtonClicked();
}
