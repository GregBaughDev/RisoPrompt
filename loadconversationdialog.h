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
    QPushButton mLoadButton;
    QPushButton mDeleteButton;
    QLabel mLabel;
    QTreeWidget mTree;
    void onLoadClicked();
    void onDeleteClicked();

public:
    LoadConversationDialog(QWidget *parent);

signals:
    void conversationLoaded(const QString selectedItem);
    void conversationDeleted(const QString selectedItem);
};

#endif // LOADCONVERSATIONDIALOG_H
