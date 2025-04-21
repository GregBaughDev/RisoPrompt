#ifndef LOADCONVERSATIONDIALOG_H
#define LOADCONVERSATIONDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class LoadConversationDialog : public QDialog
{
    Q_OBJECT
    QPushButton m_loadButton;
    QPushButton m_deleteButton;
    QLabel m_label;
    QTreeWidget m_tree;
    void onLoadClicked();
    void onDeleteClicked();

public:
    LoadConversationDialog(QWidget *parent);

signals:
    void conversationLoaded(const QString selectedItem); // todo - what's the arg type
    void conversationDeleted(const QString selectedItem);
};

#endif // LOADCONVERSATIONDIALOG_H
