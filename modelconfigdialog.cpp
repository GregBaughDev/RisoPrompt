#include "modelconfigdialog.h"

ModelConfigDialog::ModelConfigDialog(QWidget *parent, const ModelConfig &modelConfig, QStringList availableModels) :
    QDialog{parent},
    mModelLabel{this},
    mSaveButton{this},
    mApiKeyLabel{this},
    mApiKeyEditorText{this},
    mComboBox{this},
    mModelConfig{modelConfig},
    mAvailableModels{availableModels}
{
    // next time - sometimes the models aren't appearing in the list

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

    mComboBox.move(50, 30);
    mComboBox.setFixedWidth(300);
    mComboBox.addItems(mAvailableModels);
    if (mModelConfig.model != nullptr)
    {
        mComboBox.setCurrentIndex(mAvailableModels.indexOf(mModelConfig.model));
    }

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
    bool hasModelChanged = mComboBox.currentText() != mModelConfig.model;
    bool hasApiKeyChanged = !mApiKeyEditorText.text().isEmpty() && mApiKeyEditorText.text() != mModelConfig.apiKey;

    if (hasModelChanged || hasApiKeyChanged)
    {
        if (hasModelChanged) emit modelChanged(mComboBox.currentText());
        if (hasApiKeyChanged) emit apiKeyChanged(mApiKeyEditorText.text());

        close();
    }
}
