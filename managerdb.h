/**************************************************************************
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/.
**
**************************************************************************/

#pragma once

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlResult>

class ManagerDb : public QObject
{
public:
    explicit ManagerDb(QObject *parent = nullptr);
    ~ManagerDb();

    bool loadDatabase();
    void generateTestDB();

    QString getQueryResult(const QString &strQuery);

private:
    bool createCardTable();
    bool createNmTable(const QString &nameTable);
    bool insertValuesToCardTable();
    bool insertValuesToNmTable(const QString &nameTable, const QStringList &listValues);

private:
    const QString table_Card;
    const QString table_Nom;
    const QString table_Party;
    const QString table_Contractor;
    const QString table_Store;
    QString _pathDatabase;
    QSqlDatabase db;
};

