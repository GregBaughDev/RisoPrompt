#ifndef PERSISTENCEMANAGER_H
#define PERSISTENCEMANAGER_H

#include <QObject>
#include <QVariant>
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>

class PersistenceManager : public QObject
{
    Q_OBJECT
    QVariant m_activeConversation;
    void loadConversation(const QString &conversationName);
    int conversationCheckpoint; // this will be set on load and will be used to know which messages need to be persisted

public:
    PersistenceManager(QObject *parent);
    static void initiateDBConnection();
    static void insertConversationMessage(const QString &conversationName, const QString &author, const QString &messageBody, const int &sequence);

public slots:
    void setActiveConversation(const QString &conversationName);
    void deleteConversation(const QString &conversationName);
};

#endif // PERSISTENCEMANAGER_H
