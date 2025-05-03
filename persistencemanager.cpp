#include "persistencemanager.h"
#include <QtSql/QSqlQuery>
#include <QDateTime>
#include <QtSql/qsqlerror.h>
#include <QSqlRecord>
#include <QFile>
#include <QtLogging>

PersistenceManager::PersistenceManager(QObject *parent) : QObject{parent} {}

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
        qCritical() << "Error inserting:" << insertQuery.lastError();
    }
}

void PersistenceManager::setActiveConversation(const QString &conversationName)
{
    m_activeConversation = conversationName;
}

void PersistenceManager::deleteConversation(const QString &conversationName)
{
    QSqlQuery deleteQuery{QSqlDatabase::database()};

    deleteQuery.prepare("DELETE FROM risoprompt WHERE conversation_name = :conversationName");
    deleteQuery.bindValue(":conversationName", conversationName);

    bool deleted = deleteQuery.exec();

    if (!deleted)
    {
        qCritical() << "Error deleting conversation:" << deleteQuery.lastError();
    }
}

void PersistenceManager::populateConversationMetadata(QList<ConversationMetadata> *list)
{
    QSqlQueryModel metadataQuery;
    metadataQuery.setQuery("SELECT conversation_name, created_at FROM risoprompt GROUP BY conversation_name");

    for (int i = 0; i < metadataQuery.rowCount(); i++)
    {
        ConversationMetadata meta;
        meta.name = metadataQuery.record(i).value("conversation_name").toString();
        meta.dateTime = metadataQuery.record(i).value("created_at").toString();

        list->append(meta);
    }
}

QList<StoredConversationMessage> PersistenceManager::loadConversation(const QString &conversationName)
{
    QList<StoredConversationMessage> messageList;
    QSqlQuery conversationQuery;
    conversationQuery.prepare("SELECT message_body, author FROM risoprompt WHERE conversation_name = :conversationName ORDER BY sequence ASC");
    conversationQuery.bindValue(":conversationName", conversationName);

    bool queried = conversationQuery.exec();

    if (!queried)
    {
        qCritical() << "Error retrieving conversations:" << conversationQuery.lastError();
    }

    while (conversationQuery.next())
    {
        StoredConversationMessage message;
        message.message = conversationQuery.value(0).toString();
        message.author = conversationQuery.value(1).toString() == "User" ? MessageAuthor::USER : MessageAuthor::MODEL;
        messageList.append(message);
    }

    return messageList;
}

QString PersistenceManager::getActiveConversationName()
{
    return m_activeConversation;
}

void PersistenceManager::initiateDBConnection()
{
    QString dbName = "risoprompt.db";
    bool dbFileExists = QFile::exists(dbName);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    bool opened = db.open();

    if (!opened)
    {
        qCritical() << "error opening DB:" << db.lastError();
    }

    if (!dbFileExists)
    {
        QSqlQuery query{db};

        bool tableCreated = query.exec(""
                                       "CREATE TABLE risoprompt("
                                       "conversation_name TEXT NOT NULL, "
                                       "author TEXT NOT NULL, "
                                       "message_body TEXT NOT NULL, "
                                       "created_at TEXT NOT NULL, "
                                       "sequence INTEGER NOT NULL"
                                       ");");

        if (!tableCreated)
        {
            qCritical() << "Table creation failed:" << query.lastError();
        }
    }

    qInfo() << "db" << dbName << "open!";
}
