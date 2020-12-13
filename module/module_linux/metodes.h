
#ifndef METODES_H
#define METODES_H

#include <QtSql/QtSql>
#include <QDebug>



QSqlDatabase initBd(void)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
       db.setHostName("localhost");
       db.setDatabaseName("test");
       db.setUserName("root");
       db.setPassword("root");
       bool ok = db.open();
         if(ok){
            return db;
         }else {
             qDebug("ECHEC D'OUVERTURE DE LA BASE ");
         }
}


#endif // METODES_H
