#include "managerdb.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

ManagerDb::ManagerDb(QObject *parent) : QObject(parent)
  , table_Card("Card")
  , table_Nom("Nom")
  , table_Party("Party")
  , table_Contractor("Contractor")
  , table_Store("Store")
  , db(QSqlDatabase::addDatabase("QSQLITE"))
{

}

ManagerDb::~ManagerDb()
{
    if (db.isOpen()){
        db.close();
    }
}

bool ManagerDb::loadDatabase()
{
#ifdef QT_DEBUG
    _pathDatabase = QFileInfo(__FILE__).dir().absolutePath() + "/sqlCardDatabase.db";
#else
    _pathDatabase = "sqlCardDatabase.db";
#endif
    db.setDatabaseName(_pathDatabase);
    if(!db.open()){
        qCritical() << "Database not open" << _pathDatabase << Qt::endl;
        return false;
    }
    return true;
}

void ManagerDb::generateTestDB()
{
    if(QFile(_pathDatabase).size() > 0){
        qDebug() << "Can not generateTestDB, because db is not empty" << Qt::endl;
        return;
    }
    createCardTable();
    createNmTable(table_Nom);
    createNmTable(table_Party);
    createNmTable(table_Contractor);
    createNmTable(table_Store);

    insertValuesToCardTable();
    insertValuesToNmTable(table_Nom, QStringList() << "Стол" << "Стул" << "Шкаф" << QString() << "Тумбочка" << "Кресло" << "Ваза" << "Люстра");
    insertValuesToNmTable(table_Party, QStringList() << "Первая" << "Вторая" << "Третья");
    insertValuesToNmTable(table_Contractor, QStringList() << "ООО \"Веллатрест\"" << "ООО \"Оникс\"" << "ООО \"ПРОГРЕСС\"" << "ООО \"Интеллект Сервис\"" << "\"УКРСПЕЦЭКСПОРТ\"");
    insertValuesToNmTable(table_Store, QStringList() << "Готовая продукция" << "Товары на складе" << "Сырье и материалы");
}

QString ManagerDb::getQueryResult(const QString &strQuery)
{
    qDebug() << "Query:" << strQuery;
    QSqlQuery query(strQuery);
    if(!query.exec()){
        qWarning() << __FUNCTION__ << "failed: " << query.lastError() << Qt::endl;
        return {};
    }
    const int count = query.record().count();
    QList<QString> list;
    while (query.next()) {
        QString str;
        for (int var = 0; var < count; ++var) {
            str.append(query.value(var).toString() + "|");
        }
        str.chop(1);
        list.append(str);
    }
    return list.join("\n");
}

bool ManagerDb::createCardTable()
{
    QSqlQuery query;
    query.prepare(QString("CREATE TABLE IF NOT EXISTS %1 ("
            "ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
            "Qt INTEGER NOT NULL,"
            "Nom_ID INTEGER NOT NULL ,"
            "Store_ID INTEGER NOT NULL,"
            "Party_ID INTEGER DEFAULT NULL,"
            "Owner_ID INTEGER DEFAULT NULL,"
            "Customer_ID INTEGER DEFAULT NULL,"
            "FOREIGN KEY(Nom_ID) REFERENCES Nom(ID),"
            "FOREIGN KEY(Store_ID) REFERENCES Store(ID),"
            "FOREIGN KEY(Party_ID) REFERENCES Party(ID),"
            "FOREIGN KEY(Owner_ID) REFERENCES Contractor(ID),"
            "FOREIGN KEY(Customer_ID) REFERENCES Contractor(ID)"
            ");").arg(table_Card));

    if (query.exec()){
        return true;
    }
    qWarning() << __FUNCTION__ << "Couldn't create the table:" << query.lastError() << Qt::endl;
    return false;
}

bool ManagerDb::createNmTable(const QString &nameTable)
{
    QSqlQuery query;
    query.prepare(QString("CREATE TABLE IF NOT EXISTS %1 ("
            "ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
            "Nm TEXT NOT NULL"
            ");").arg(nameTable));

    if (query.exec()){
        return true;
    }
    qWarning() << __FUNCTION__ << "Couldn't create the table:" << query.lastError() << Qt::endl;
    return false;
}

bool ManagerDb::insertValuesToCardTable()
{
    QString strQuery = QString("INSERT INTO %1 (Qt, Nom_ID, Store_ID, Party_ID, Owner_ID, Customer_ID) VALUES ").arg(table_Card);
    strQuery.append("(10,    1,  1, NULL,    1,      NULL    ), ");
    strQuery.append("(20,    2,  1, 1,       NULL,   1       ), ");
    strQuery.append("(25,    3,  1, NULL,    2,      NULL    ), ");
    strQuery.append("(45,    6,  2, 2,       NULL,   2       ), ");
    strQuery.append("(7,     2,  2, NULL,    1,      3       ), ");
    strQuery.append("(17,    1,  2, 3,       1,      NULL    ), ");
    strQuery.append("(45,    7,  2, 3,       NULL,   4       ), ");
    strQuery.append("(34,    3,  3, 3,       3,      5       ), ");
    strQuery.append("(6,     2,  3, 1,       3,      NULL    ), ");
    strQuery.replace(strQuery.size() - 2, 2, ";");
    QSqlQuery query;
    query.prepare(strQuery);
    if(query.exec()){
        return true;
    }
    qWarning() << __FUNCTION__ << "failed: " << query.lastError() << Qt::endl;
    return false;
}

bool ManagerDb::insertValuesToNmTable(const QString &nameTable, const QStringList &listValues)
{
    if (listValues.isEmpty()){
        qWarning() << __FUNCTION__ << "failed: value cannot be empty" << Qt::endl;
        return false;
    }
    QString strQuery = QString("INSERT INTO %1 (Nm) VALUES ").arg(nameTable);
    for (const QString &str: listValues) {
        strQuery.append(QString("('%1'), ").arg(str));
    }
    strQuery.replace(strQuery.size() - 2, 2, ";");
    QSqlQuery query;
    query.prepare(strQuery);
    if(query.exec()){
        return true;
    }
    qWarning() << __FUNCTION__ << "failed: " << query.lastError() << Qt::endl;
    return false;
}
