#ifndef SAVECONVERSATIONDIALOG_H
#define SAVECONVERSATIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class SaveConversationDialog : public QDialog
{
    Q_OBJECT
    QLineEdit m_conversationNameText;
    QLabel m_label;
    QPushButton m_saveButton;

public:
    SaveConversationDialog(QWidget *parent, QString conversationName);
    void onSaveClicked();

signals:
    void conversationSaved(const QString &conversationName);
};

#endif // SAVECONVERSATIONDIALOG_H
