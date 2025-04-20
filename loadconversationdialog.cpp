#include "loadconversationdialog.h"

LoadConversationDialog::LoadConversationDialog(QWidget *parent) :
    QDialog{parent}, m_loadButton{this}, m_label{this}, m_tree{this}
{
    setWindowTitle("Load conversation");
    setFixedSize(400, 200);

    m_label.move(50, 10);
    m_label.setText("Choose conversation to load:");

    m_tree.setColumnCount(2);
    m_tree.move(50, 30);
    m_tree.setFixedHeight(110);
    m_tree.setFixedWidth(300);
    m_tree.setColumnWidth(0, 200);
    m_tree.setColumnWidth(1, 95);
    m_tree.setHeaderHidden(true);

    m_loadButton.move(50, 160);
    m_loadButton.setText("load");
    m_loadButton.setFixedSize(300, 30);

    // hardcode the data for the minute
    QList<QTreeWidgetItem*> items;

    QTreeWidgetItem *item1 = new QTreeWidgetItem(&m_tree);

    item1->setText(0, "Chairlift");
    item1->setText(1, "24/03/25 19:49");

    QTreeWidgetItem *item2 = new QTreeWidgetItem(&m_tree);

    item2->setText(0, "Embedded software");
    item2->setText(1, "20/02/25 11:11");

    items.append(item1);
    items.append(item2);

    m_tree.insertTopLevelItems(0, items);

    connect(&this->m_loadButton, &QPushButton::clicked, this, &LoadConversationDialog::onLoadClicked);
}

void LoadConversationDialog::onLoadClicked()
{
    emit conversationLoaded(m_tree.selectedItems().first()->text(0));
    qDebug() << "conversation loaded is" << m_tree.selectedItems().first()->text(0);
    close();
}

// probs need a delete button too!
// and also pop up the dialog if current conversation isn't saved
