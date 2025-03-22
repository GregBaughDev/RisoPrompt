#include "loadconversationdialog.h"

LoadConversationDialog::LoadConversationDialog(QWidget *parent) :
    QDialog{parent}, m_loadButton{this}, m_label{this}
{
    setWindowTitle("Load conversation");
    setFixedSize(400, 200);

    m_label.move(50, 10);
    m_label.setText("Choose conversation to load:");

    m_loadButton.move(50, 160);
    m_loadButton.setText("load");
    m_loadButton.setFixedSize(300, 30);

    // next up - display tree widget
}


// do it with a tree widget - will eventually map the db types but for now let's
// hardcode the data
