#include <QFile>
#include <QString>
#include <QDebug>
#include <QSqlDatabase>
#include <QtSql/qsqlerror.h>
#include <QtSql/QSqlQuery>
#include "./conversationmessage.h"

#include <QDateTime>

namespace DBUtils {
    // maybe this should be static in persistencemanager
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
                    "created_at TEXT NOT NULL, "
                    "sequence INTEGER NOT NULL"
                ");");

            if (!tableCreated)
            {
                qDebug() << "Table creation failed:" << query.lastError();
            }
        }

        qDebug() << "db" << dbName << "open!";
    }
}
