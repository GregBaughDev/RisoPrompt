#ifndef PERSISTENCEMANAGER_H
#define PERSISTENCEMANAGER_H

#include <QObject>
#include <QVariant>
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QTreeWidgetItem>

#include "conversationmessage.h"

struct ConversationMetadata
{
    QString name;
    QString dateTime;
};

struct StoredConversationMessage
{
    MessageAuthor author;
    QString message;
};

struct ModelConfig
{
    QString model = nullptr;
    QString apiKey = nullptr;
};

class PersistenceManager : public QObject
{
    Q_OBJECT
    QString mActiveConversation = "";

public:
    PersistenceManager(QObject *parent);
    static void populateConversationMetadata(QList<ConversationMetadata> *list);
    static void initiateDBConnection();
    static void insertConversationMessage(const QString &conversationName, const QString &author, const QString &messageBody, const int &sequence);
    static QList<StoredConversationMessage> loadConversation(const QString &conversationName);
    static ModelConfig loadModelConfig();
    QString getActiveConversationName();

public slots:
    void setActiveConversation(const QString &conversationName);
    void deleteConversation(const QString &conversationName);
    void persistModel(const QString &model);
    void persistApiKey(const QString &apiKey);
};

#endif // PERSISTENCEMANAGER_H
