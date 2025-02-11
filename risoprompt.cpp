#include "risoprompt.h"
#include "ui_risoprompt.h"

#include <QDebug>
#include "./customplaintext.h"

RisoPrompt::RisoPrompt(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RisoPrompt)
{
    ui->setupUi(this);

    connect(ui->promptInput, &CustomPlainText::textSubmit, this, &RisoPrompt::handleTextSubmit);
}

RisoPrompt::~RisoPrompt()
{
    delete ui;
}

void RisoPrompt::handleTextSubmit(const QString &newValue)
{
    ui->testTextDisplay->setPlainText(newValue);
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
    // todo
}


