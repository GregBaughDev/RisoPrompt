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
    else
    {
        qInfo() << "db" << dbName << "open!";
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
            qCritical() << "Table creation failed - risoprompt:" << query.lastError();
        }
        else
        {
            qInfo() << "Risoprompt table created";
        }

        tableCreated = query.exec(""
                                  "CREATE TABLE modelconfig("
                                  "model TEXT, "
                                  "api_key TEXT, "
                                  "user TEXT"
                                  ");");

        if (!tableCreated)
        {
            qCritical() << "Table creation failed - modelconfig:" << query.lastError();
        }
        else
        {
            qInfo() << "Modelconfig table created";
        }

        bool createRootUser = query.exec("INSERT INTO modelconfig (user) VALUES ('root')");

        if (!createRootUser)
        {
            qCritical() << "Unable to create root user";
        }
        else
        {
            qInfo() << "Root user created";
        }
    }
}

ModelConfig PersistenceManager::loadModelConfig()
{
    QSqlQuery query{QSqlDatabase::database()};
    ModelConfig config;

    query.prepare("SELECT * FROM modelconfig");

    bool queried = query.exec();

    if (!queried)
    {
        qCritical() << "Error querying model config:" << query.lastError();
    }

    while (query.next())
    {
        config.model = query.value(0).toString();
        config.apiKey = query.value(1).toString();
    }

    return config;
}

void PersistenceManager::persistModel(const QString &model)
{
    QSqlQuery query{QSqlDatabase::database()};
    query.prepare("UPDATE modelconfig SET model = :model WHERE user = 'root'");
    query.bindValue(":model", model);

    bool updated = query.exec();

    if (!updated)
    {
        qCritical() << "Error updating model:" << query.lastError();
    }
    else
    {
        qInfo() << "Model persisted to db";
    }
}

void PersistenceManager::persistApiKey(const QString &apiKey)
{
    QSqlQuery query{QSqlDatabase::database()};
    query.prepare("UPDATE modelconfig SET api_key = :apiKey WHERE user = 'root'");
    query.bindValue(":apiKey", apiKey);

    bool updated = query.exec();

    if (!updated)
    {
        qCritical() << "Error updating api key:" << query.lastError();
    }
    else
    {
        qInfo() << "Api key persisted to db";
    }
}
