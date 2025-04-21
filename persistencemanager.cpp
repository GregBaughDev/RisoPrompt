#include "persistencemanager.h"
#include <QtSql/QSqlQuery>
#include <QDateTime>
#include <QtSql/qsqlerror.h>

PersistenceManager::PersistenceManager(QObject *parent) : QObject{parent} {}

void PersistenceManager::loadConversation(const QString &conversationName)
{
    // this should return a list of messages and their author
}

void PersistenceManager::insertConversationMessage(const QString &conversationName, const QString &author, const QString &messageBody, const int &sequence)
{
    QSqlQuery insertQuery{QSqlDatabase::database()};

    insertQuery.prepare("INSERT INTO risoprompt"
                        "(conversation_name, author, message_body, created_at, sequence) "
                        "VALUES (:conversationName, :author, :messageBody, :createdAt, :sequence)");
    insertQuery.bindValue(":conversationName", conversationName);
    insertQuery.bindValue(":author", author);
    insertQuery.bindValue(":messageBody", messageBody);
    insertQuery.bindValue(":createdAt", QDateTime::currentDateTime().toString());
    insertQuery.bindValue(":sequence", sequence);
    bool inserted = insertQuery.exec();

    if (!inserted)
    {
        qDebug() << "Error inserting:" << insertQuery.lastError();
    }
}

void PersistenceManager::setActiveConversation(const QString &conversationName)
{
    m_activeConversation = conversationName;
}
