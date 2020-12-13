#include "dialog.h"
#include "ui_dialog.h"
#include "metodes.h"
#include <QtSql>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

Dialog::Dialog(QWidget *parent, QString id) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
//    initBd();

//    QSqlQuery requeteur;
//    requeteur.exec("SELECT * FROM pub");
//    model->setTable("pub");
//    model->setFilter("id ='" + id + "'");
//    model->select();
//    QSqlRecord record = model->record(0);
//    ui->label->setText(record.value(1).toString());
}

Dialog::~Dialog()
{
    delete ui;
}
