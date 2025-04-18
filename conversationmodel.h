#ifndef CONVERSATIONMODEL_H
#define CONVERSATIONMODEL_H

#include <QAbstractListModel>
#include "conversationmessage.h"

class ConversationModel : public QAbstractListModel
{
    Q_OBJECT
    QVector<ConversationMessage> m_messages;

public:
    ConversationModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void addMessage(const QString &text, const MessageAuthor &author);
    void resetMessages();
};

#endif // CONVERSATIONMODEL_H
