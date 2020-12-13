#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql/QtSql>
#include <QDebug>




class connection
{
private:
    // The very object database, which will be work
    QSqlDatabase    db;

public:
    connection();
    void connectToDataBase();
//    bool inserIntoTable(const QVariantList &data);
    void closeDb();
    void seedOnce();
};

#endif // CONNECTION_H
