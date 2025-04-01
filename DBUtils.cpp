#include <QFile>
#include <QString>
#include <QDebug>
#include <QSqlDatabase>
#include <QtSql/qsqlerror.h>
#include <QtSql/QSqlQuery>
#include "./conversationmessage.h"

#include <QDateTime>

namespace DBUtils {
    void initiateDBConnection()
    {
        QString dbName = "risoprompt.db";
        bool dbFileExists = QFile::exists(dbName);

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbName);
        bool opened = db.open();

        if (!opened)
        {
            qDebug() << "error opening DB:" << db.lastError();
        }

        if (!dbFileExists)
        {
            QSqlQuery query{db};

            bool tableCreated = query.exec(""
                "CREATE TABLE risoprompt("
                    "conversation_name TEXT NOT NULL, "
                    "author TEXT NOT NULL, "
                    "message_body TEXT NOT NULL, "
                    "created_at TEXT NOT NULL"
                ");");

            if (!tableCreated)
            {
                qDebug() << "Table creation failed:" << query.lastError();
            }
        }

        qDebug() << "db" << dbName << "open!";
    }

    void insertConversationMessage(
        const QString &conversationName,
        const MessageAuthor &author,
        const QString &messageBody
        )
    {
        QSqlQuery insertQuery{QSqlDatabase::database()};

        insertQuery.prepare("INSERT INTO risoprompt"
                            "(conversation_name, author, message_body, created_at) "
                            "VALUES (:conversationName, :author, :messageBody, :createdAt)");
        insertQuery.bindValue(":conversationName", conversationName);
        insertQuery.bindValue(":author", author == MessageAuthor::MODEL ? "Model" : "User");
        insertQuery.bindValue(":messageBody", messageBody);
        insertQuery.bindValue(":createdAt", QDateTime::currentDateTime().toString());
        bool inserted = insertQuery.exec();

        if (!inserted)
        {
            qDebug() << "Error inserting:" << insertQuery.lastError();
        }

    }

    // query use the QSqlDatabase::database()

    //     //query.exec("SELECT * FROM risoprompt;");
    // while (query.next())
    // {
    //     qDebug() << "name" << query.value(0).toString();
    // }

    // connect buttons
}
