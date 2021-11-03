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

#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>

#include "managerdb.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QScopedPointer<ManagerDb> managerDb(new ManagerDb());
    managerDb->loadDatabase();
    managerDb->generateTestDB();

    qDebug() << "Result1:" << Qt::endl << qPrintable(managerDb->getQueryResult("SELECT Card.ID, Card.Qt, Nom.Nm FROM Card INNER JOIN Nom on Nom.ID = Card.Nom_ID ;")) << Qt::endl;
    qDebug() << "Result2:" << Qt::endl << qPrintable(managerDb->getQueryResult("SELECT Card.ID, Card.Qt, Party.Nm FROM Card INNER JOIN Party ON Party.ID = Card.Party_ID ;")) << Qt::endl;
    qDebug() << "Result3:" << Qt::endl << qPrintable(managerDb->getQueryResult("SELECT ca.ID, cr1.Nm, cr2.Nm FROM Card ca "
                                                                                                "INNER JOIN Contractor cr1 ON cr1.ID = ca.Owner_ID "
                                                                                                "INNER JOIN Contractor cr2 ON cr2.ID = ca.Customer_ID ;")) << Qt::endl;
    qDebug() << "Result4:" << Qt::endl << qPrintable(managerDb->getQueryResult("SELECT Contractor.Nm FROM Contractor UNION ALL SELECT Store.Nm FROM Store ;")) << Qt::endl;
    qDebug() << "Result5:" << Qt::endl << qPrintable(managerDb->getQueryResult("SELECT Card.Store_ID, SUM(Qt) FROM Card GROUP BY Card.Store_ID ;")) << Qt::endl;
    qDebug() << "Result6:" << Qt::endl << qPrintable(managerDb->getQueryResult("SELECT Nom.Nm FROM Nom WHERE Nom.ID NOT IN (SELECT Card.Nom_ID FROM Card) ;")) << Qt::endl;

    return a.exec();
}
