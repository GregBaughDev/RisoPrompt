#include "modelconfigdialog.h"

ModelConfigDialog::ModelConfigDialog(QWidget *parent, const ModelConfig &modelConfig) :
    QDialog{parent},
    mModelEditorText{this},
    mModelLabel{this},
    mSaveButton{this},
    mApiKeyLabel{this},
    mApiKeyEditorText{this},
    mModelConfig{modelConfig}
{
    if (modelConfig.model == nullptr || modelConfig.apiKey == nullptr)
    {
        setWindowTitle("Configure Gemini model");
    }
    else
    {
        setWindowTitle("Change Gemini model");
    }

    setFixedSize(400, 150);

    mModelLabel.move(50, 10);
    mModelLabel.setText("Current model (overwrite to change)");

    mModelEditorText.move(50, 30);
    mModelEditorText.setFixedWidth(300);
    mModelEditorText.setText(mModelConfig.model);
    mModelEditorText.displayText();

    mApiKeyLabel.move(50, 60);
    mApiKeyLabel.setText("Update the API key (overwrite to change)");

    mApiKeyEditorText.move(50, 80);
    mApiKeyEditorText.setFixedWidth(300);
    mApiKeyEditorText.setEchoMode(QLineEdit::Password);
    mApiKeyEditorText.setText(mModelConfig.apiKey);
    mApiKeyEditorText.displayText();

    mSaveButton.move(50, 110);
    mSaveButton.setText("save");
    mSaveButton.setFixedSize(300, 30);

    connect(&this->mSaveButton, &QPushButton::clicked, this, &ModelConfigDialog::onSaveClicked);
}

void ModelConfigDialog::onSaveClicked()
{
    bool hasModelChanged = !mModelEditorText.text().isEmpty() && mModelEditorText.text() != mModelConfig.model;
    bool hasApiKeyChanged = !mApiKeyEditorText.text().isEmpty() && mApiKeyEditorText.text() != mModelConfig.apiKey;

    if (hasModelChanged || hasApiKeyChanged)
    {
        if (hasModelChanged) emit modelChanged(mModelEditorText.text());
        if (hasApiKeyChanged) emit apiKeyChanged(mApiKeyEditorText.text());

        close();
    }
}
