#include "modelconfigdialog.h"

ModelConfigDialog::ModelConfigDialog(QWidget *parent, const QString promptModel, const QString apiKey) :
    QDialog{parent},
    m_modelEditorText{this},
    m_modelLabel{this},
    m_saveButton{this},
    m_promptModel{promptModel},
    m_apiKeyLabel{this},
    m_apiKey{apiKey},
    m_apiKeyEditorText{this}
{
    setWindowTitle("Change Gemini model");
    setFixedSize(400, 150);

    m_modelLabel.move(50, 10);
    m_modelLabel.setText("Current model (overwrite to change)");

    m_modelEditorText.move(50, 30);
    m_modelEditorText.setFixedWidth(300);
    m_modelEditorText.setText(m_promptModel);
    m_modelEditorText.displayText();

    m_apiKeyLabel.move(50, 60);
    m_apiKeyLabel.setText("Update the API key here (if required)");

    m_apiKeyEditorText.move(50, 80);
    m_apiKeyEditorText.setFixedWidth(300);

    m_saveButton.move(50, 110);
    m_saveButton.setText("save");
    m_saveButton.setFixedSize(300, 30);

    connect(&this->m_saveButton, &QPushButton::clicked, this, &ModelConfigDialog::onSaveClicked);
}

void ModelConfigDialog::onSaveClicked()
{
    bool hasModelChanged = !m_modelEditorText.text().isEmpty() && m_modelEditorText.text() != m_promptModel;
    bool hasApiKeyChanged = !m_apiKeyEditorText.text().isEmpty();

    if (hasModelChanged || hasApiKeyChanged)
    {
        if (hasModelChanged) emit modelChanged(m_modelEditorText.text());
        if (hasApiKeyChanged) emit apiKeyChanged(m_apiKeyEditorText.text());

        close();
    }
}
