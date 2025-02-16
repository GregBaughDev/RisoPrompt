#include "conversationmodel.h"

ConversationModel::ConversationModel(QObject *parent) : QAbstractListModel{parent} {};

int ConversationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return messages.size();
}

QVariant ConversationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= messages.size())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        return messages.at(index.row()).message(); // this should return the obj not msg
    }

    return QVariant();
}

void ConversationModel::addMessage(const QString &text)
{
    beginInsertRows(QModelIndex(), messages.size(), messages.size());
    messages.emplaceBack(text);
    endInsertRows();
}
