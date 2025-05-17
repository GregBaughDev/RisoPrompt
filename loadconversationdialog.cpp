#include "loadconversationdialog.h"

#include "persistencemanager.h"

LoadConversationDialog::LoadConversationDialog(QWidget *parent) : QDialog{parent}, mLoadButton{this}, mDeleteButton{this}, mLabel{this}, mTree{this}
{
    setWindowTitle("Load conversation");
    setFixedSize(600, 200);

    mLabel.move(50, 10);
    mLabel.setText("Choose conversation to load:");

    mTree.setColumnCount(2);
    mTree.move(50, 30);
    mTree.setFixedHeight(110);
    mTree.setFixedWidth(500);
    mTree.setColumnWidth(0, 250);
    mTree.setColumnWidth(1, 245);
    mTree.setHeaderHidden(true);

    mLoadButton.move(50, 160);
    mLoadButton.setText("load");
    mLoadButton.setFixedSize(240, 30);

    mDeleteButton.move(310, 160);
    mDeleteButton.setText("delete");
    mDeleteButton.setFixedSize(240, 30);

    QList<ConversationMetadata> metadata;
    PersistenceManager::populateConversationMetadata(&metadata);

    QList<QTreeWidgetItem *> items;

    for (int i = 0; i < metadata.length(); i++)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(&mTree);
        item->setText(0, metadata.at(i).name);
        item->setText(1, metadata.at(i).dateTime);
        items.append(item);
    }

    mTree.insertTopLevelItems(0, items);

    connect(&this->mLoadButton, &QPushButton::clicked, this, &LoadConversationDialog::onLoadClicked);
    connect(&this->mDeleteButton, &QPushButton::clicked, this, &LoadConversationDialog::onDeleteClicked);
}

void LoadConversationDialog::onLoadClicked()
{
    if (!mTree.selectedItems().isEmpty())
    {
        emit conversationLoaded(mTree.selectedItems().first()->text(0));
        close();
    }
}

void LoadConversationDialog::onDeleteClicked()
{
    if (!mTree.selectedItems().isEmpty())
    {
        emit conversationDeleted(mTree.selectedItems().first()->text(0));
        close();
    }
}
