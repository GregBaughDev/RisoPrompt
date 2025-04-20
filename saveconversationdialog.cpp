#include "saveconversationdialog.h"

SaveConversationDialog::SaveConversationDialog(QWidget *parent) :
    QDialog{parent}, m_conversationNameText{this}, m_label{this}, m_saveButton{this}
{
    setWindowTitle("Save conversation");
    setFixedSize(400, 100);

    m_label.move(50, 10);
    m_label.setText("Enter conversation name");

    m_conversationNameText.move(50, 30);
    m_conversationNameText.setFixedWidth(300);

    m_saveButton.move(50, 60);
    m_saveButton.setText("save");
    m_saveButton.setFixedSize(300, 30);

    connect(&this->m_saveButton, &QPushButton::clicked, this, &SaveConversationDialog::onSaveClicked);
}

void SaveConversationDialog::onSaveClicked()
{
    if (m_conversationNameText.text() != "")
    {
        emit conversationSaved(m_conversationNameText.text());
        close();
    }
}
