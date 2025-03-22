#include "modelconfigdialog.h"

ModelConfigDialog::ModelConfigDialog(QWidget *parent, const QString promptModel) :
    QDialog{parent}, m_modelEditorText{this}, m_label{this}, m_saveButton{this}, m_promptModel{promptModel}
{
    setWindowTitle("Change Gemini model");
    setFixedSize(400, 100);

    m_label.move(50, 10);
    m_label.setText("Current model (overwrite to change)");

    m_modelEditorText.move(50, 30);
    m_modelEditorText.setFixedWidth(300);
    m_modelEditorText.setText(m_promptModel);
    m_modelEditorText.displayText();

    m_saveButton.move(50, 60);
    m_saveButton.setText("save");
    m_saveButton.setFixedSize(300, 30);

    connect(&this->m_saveButton, &QPushButton::clicked, this, &ModelConfigDialog::onSaveClicked);
}

void ModelConfigDialog::onSaveClicked()
{
    if (m_modelEditorText.text() != "")
    {
        emit modelChanged(m_modelEditorText.text());
        close();
    }
}
