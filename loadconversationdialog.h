#ifndef LOADCONVERSATIONDIALOG_H
#define LOADCONVERSATIONDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>

class LoadConversationDialog : public QDialog
{
    Q_OBJECT
    QPushButton m_loadButton;
    QLabel m_label;
public:
    LoadConversationDialog(QWidget *parent);
    void onLoadClicked();

signals:
    void conversationLoaded(); // todo - what's the arg type
};

#endif // LOADCONVERSATIONDIALOG_H
