#ifndef METHODES_H
#define METHODES_H

#include <QMessageBox>
#include <QtSql/QtSql>
#include <QDebug>



QSqlDatabase initBdWithMySql(void)
{
   QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
   db.setHostName("localhost");
   db.setDatabaseName("test");
   db.setUserName("root");
   db.setPassword("root");
   if(!db.open())
   {
       QMessageBox::critical(0, QObject::tr("Database Error"), db.lastError().text());
   }
   return db;
}

QSqlDatabase initBd(void){
     QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
     db.setDatabaseName("publications");
     if(!db.open())
     {
         QMessageBox::critical(0, QObject::tr("Database Error"), db.lastError().text());
     }
     return db;
}

void closeDB(QSqlDatabase db)
{
    db.close();
}


void showInfoToUser(QWidget *parent, const char *messagee)
{
    QMessageBox::information(parent,QObject::tr("Information"),QObject::tr(messagee));
}


int showWarningToUser(QString message)
{
    QMessageBox msgBox;
    msgBox.setText("Attention !!!");
    msgBox.setInformativeText(message);
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    return msgBox.exec();
}


#endif // METHODES_H
