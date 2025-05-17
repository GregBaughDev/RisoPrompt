#ifndef SAVECONVERSATIONDIALOG_H
#define SAVECONVERSATIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class SaveConversationDialog : public QDialog
{
    Q_OBJECT
    QLineEdit mConversationNameText;
    QLabel mLabel;
    QPushButton mSaveButton;

public:
    SaveConversationDialog(QWidget *parent, QString conversationName);
    void onSaveClicked();

signals:
    void conversationSaved(const QString &conversationName);
};

#endif // SAVECONVERSATIONDIALOG_H
