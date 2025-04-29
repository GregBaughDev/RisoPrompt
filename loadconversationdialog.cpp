#include "loadconversationdialog.h"

#include "persistencemanager.h"

LoadConversationDialog::LoadConversationDialog(QWidget *parent) : QDialog{parent}, m_loadButton{this}, m_deleteButton{this}, m_label{this}, m_tree{this}
{
    setWindowTitle("Load conversation");
    setFixedSize(600, 200);

    m_label.move(50, 10);
    m_label.setText("Choose conversation to load:");

    m_tree.setColumnCount(2);
    m_tree.move(50, 30);
    m_tree.setFixedHeight(110);
    m_tree.setFixedWidth(500);
    m_tree.setColumnWidth(0, 250);
    m_tree.setColumnWidth(1, 245);
    m_tree.setHeaderHidden(true);

    m_loadButton.move(50, 160);
    m_loadButton.setText("load");
    m_loadButton.setFixedSize(240, 30);

    m_deleteButton.move(310, 160);
    m_deleteButton.setText("delete");
    m_deleteButton.setFixedSize(240, 30);

    QList<ConversationMetadata> metadata;
    PersistenceManager::populateConversationMetadata(&metadata);

    QList<QTreeWidgetItem *> items;

    for (int i = 0; i < metadata.length(); i++)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(&m_tree);
        item->setText(0, metadata.at(i).name);
        item->setText(1, metadata.at(i).dateTime);
        items.append(item);
    }

    m_tree.insertTopLevelItems(0, items);

    connect(&this->m_loadButton, &QPushButton::clicked, this, &LoadConversationDialog::onLoadClicked);
    connect(&this->m_deleteButton, &QPushButton::clicked, this, &LoadConversationDialog::onDeleteClicked);
}

void LoadConversationDialog::onLoadClicked()
{
    if (!m_tree.selectedItems().isEmpty())
    {
        emit conversationLoaded(m_tree.selectedItems().first()->text(0));
        close();
    }
}

void LoadConversationDialog::onDeleteClicked()
{
    if (!m_tree.selectedItems().isEmpty())
    {
        emit conversationDeleted(m_tree.selectedItems().first()->text(0));
        // will also need to delete the conversation from the m_tree
    }
}
