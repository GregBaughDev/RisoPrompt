#include "saveconversationdialog.h"

SaveConversationDialog::SaveConversationDialog(QWidget *parent, QString conversationName) :
    QDialog{parent}, mConversationNameText{this}, mLabel{this}, mSaveButton{this}
{
    setWindowTitle("Save conversation");
    setFixedSize(400, 100);

    mLabel.move(50, 10);
    mLabel.setText("Enter conversation name");

    mConversationNameText.move(50, 30);
    mConversationNameText.setFixedWidth(300);

    mSaveButton.move(50, 60);
    mSaveButton.setText("save");
    mSaveButton.setFixedSize(300, 30);

    mConversationNameText.setText(conversationName);

    connect(&this->mSaveButton, &QPushButton::clicked, this, &SaveConversationDialog::onSaveClicked);
}

void SaveConversationDialog::onSaveClicked()
{
    if (!mConversationNameText.text().isEmpty())
    {
        emit conversationSaved(mConversationNameText.text());
        close();
    }
}
