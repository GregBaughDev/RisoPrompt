#ifndef CONVERSATIONMODEL_H
#define CONVERSATIONMODEL_H

#include <QAbstractListModel>
#include "conversationmessage.h"

class ConversationModel : public QAbstractListModel
{
    Q_OBJECT

public:
    ConversationModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void addMessage(const QString &text, const MessageAuthor &author);

private:
    QVector<ConversationMessage> messages;
};

#endif // CONVERSATIONMODEL_H
