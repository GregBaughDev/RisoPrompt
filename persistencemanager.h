#ifndef PERSISTENCEMANAGER_H
#define PERSISTENCEMANAGER_H

#include <QObject>
#include <QVariant>
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QTreeWidgetItem>

#include "conversationmessage.h"

struct ConversationMetadata {
    QString name;
    QString dateTime;
};

struct StoredConversationMessage {
    MessageAuthor author;
    QString message;
};

class PersistenceManager : public QObject
{
    Q_OBJECT
    // TO DO - Sort out the mix of camel and snake case!
    QString m_activeConversation = "";
    int conversationCheckpoint; // this will be set on load and will be used to know which messages need to be persisted

public:
    PersistenceManager(QObject *parent);
    static void populateConversationMetadata(QList<ConversationMetadata> *list);
    static void initiateDBConnection();
    static void insertConversationMessage(const QString &conversationName, const QString &author, const QString &messageBody, const int &sequence);
    static QList<StoredConversationMessage> loadConversation(const QString &conversationName);
    QString getActiveConversationName();

public slots:
    void setActiveConversation(const QString &conversationName);
    void deleteConversation(const QString &conversationName);
};

#endif // PERSISTENCEMANAGER_H
