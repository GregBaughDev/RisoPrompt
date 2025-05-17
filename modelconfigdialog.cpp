#include "modelconfigdialog.h"

ModelConfigDialog::ModelConfigDialog(QWidget *parent, const ModelConfig &modelConfig) :
    QDialog{parent},
    m_modelEditorText{this},
    m_modelLabel{this},
    m_saveButton{this},
    m_apiKeyLabel{this},
    m_apiKeyEditorText{this},
    m_modelConfig{modelConfig}
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

    m_modelLabel.move(50, 10);
    m_modelLabel.setText("Current model (overwrite to change)");

    m_modelEditorText.move(50, 30);
    m_modelEditorText.setFixedWidth(300);
    m_modelEditorText.setText(m_modelConfig.model);
    m_modelEditorText.displayText();

    m_apiKeyLabel.move(50, 60);
    m_apiKeyLabel.setText("Update the API key (overwrite to change)");

    m_apiKeyEditorText.move(50, 80);
    m_apiKeyEditorText.setFixedWidth(300);
    m_apiKeyEditorText.setEchoMode(QLineEdit::Password);
    m_apiKeyEditorText.setText(m_modelConfig.apiKey);
    m_apiKeyEditorText.displayText();

    m_saveButton.move(50, 110);
    m_saveButton.setText("save");
    m_saveButton.setFixedSize(300, 30);

    connect(&this->m_saveButton, &QPushButton::clicked, this, &ModelConfigDialog::onSaveClicked);
}

void ModelConfigDialog::onSaveClicked()
{
    bool hasModelChanged = !m_modelEditorText.text().isEmpty() && m_modelEditorText.text() != m_modelConfig.model;
    bool hasApiKeyChanged = !m_apiKeyEditorText.text().isEmpty() && m_apiKeyEditorText.text() != m_modelConfig.apiKey;

    if (hasModelChanged || hasApiKeyChanged)
    {
        if (hasModelChanged) emit modelChanged(m_modelEditorText.text());
        if (hasApiKeyChanged) emit apiKeyChanged(m_apiKeyEditorText.text());

        close();
    }
}
