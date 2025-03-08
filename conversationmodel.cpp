#include "conversationmodel.h"

ConversationModel::ConversationModel(QObject *parent) : QAbstractListModel{parent} {};

int ConversationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_messages.size();
}

QVariant ConversationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_messages.size())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        return QVariant::fromValue(m_messages.at(index.row()));
    }

    return QVariant();
}

void ConversationModel::addMessage(const QString &text, const MessageAuthor &author)
{
    beginInsertRows(QModelIndex(), m_messages.size(), m_messages.size());
    m_messages.emplaceBack(text, author);
    endInsertRows();
}

void ConversationModel::resetMessages()
{
    this->beginResetModel();
    m_messages.clear();
    this->endResetModel();
}
