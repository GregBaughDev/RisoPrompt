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
    QLabel m_label;
    QTreeWidget m_tree;
public:
    LoadConversationDialog(QWidget *parent);
    void onLoadClicked();

signals:
    void conversationLoaded(const QString selectedItem); // todo - what's the arg type
};

#endif // LOADCONVERSATIONDIALOG_H
