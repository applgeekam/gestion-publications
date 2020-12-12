//#include "methodes.h"
#include "mainwindow.h"
#include "test.h"
#include "tag.h"
#include "ui_test.h"


#include <QtSql>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDesktopServices>
#include <QFileDialog>


test::test(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);
    Parent = parent;
    loadModal();
}

test::~test()
{
    delete ui;
}


void test::on_backBtn_clicked()
{
    Onclose();
}



void test::on_test_rejected()
{
    Onclose();
}

void test::on_seeBtn_clicked()
{
    //qDebug() << currentPath;
    QDesktopServices::openUrl(QUrl("file:///" + currentPath, QUrl::TolerantMode));
}

void test::on_deleteBtn_clicked()
{
    QString request = QString("pubId=%1").arg(currentId);
    model->setFilter(request);
    model->select();
    if(model->rowCount() > 0)
    {
        QSqlRecord record = model->record(0);
        QString const message = "Vous etes en train de supprimer la publication : " + record.value(6).toString()+ ". Appuyer sur Oui pour confirmer.";
        int rep = QMessageBox::warning(this, tr("Attention !!!"),
                                             message,
                                             QMessageBox::Cancel | QMessageBox::Yes,
                                            QMessageBox::Cancel);

        switch (rep) {
          case QMessageBox::Yes:
                model->removeRows(0, model->rowCount());
                model->submitAll();
              break;
          case QMessageBox::Cancel:
              break;
          default:
                QMessageBox::information(this,QObject::tr("Information"), "Aucune données n'est supprimer");
              break;
        }
        loadModal();
    }
}

void test::loadModal()
{
    QSqlQuery requeteur;
    requeteur.exec("SELECT * FROM publications");
    model = new QSqlRelationalTableModel(this);
    model->setTable("publications");

    model->setRelation(4, QSqlRelation("types", "id", "code"));
    model->setSort(1, Qt::AscendingOrder); // Définition du critère de tri
    model->setHeaderData(5, Qt::Horizontal, "Numero de publication");
    model->setHeaderData(6, Qt::Horizontal, "Nom du fichier");
    model->setHeaderData(2, Qt::Horizontal, "Date de publication");
    model->setHeaderData(3, Qt::Horizontal, "Date d'enregistrement");
    model->setHeaderData(4, Qt::Horizontal, "Type de la publication");
    model->select();

    if(model->rowCount() == 0)
    {
        Onclose();
        QMessageBox::information(this,QObject::tr("Information"), "La liste des publications est vide. Veuillez d'abord faire des enregistrements.");

    }
    ui->pubList->setModel(model); // Liaison entre le modèle et le tableau
    ui->pubList->setItemDelegate(new QSqlRelationalDelegate(this));
    ui->pubList->setColumnHidden(0, true); // On masque la colonne des identifiants
    ui->pubList->setColumnHidden(1, true);
    ui->pubList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pubList->resizeColumnsToContents();
    ui->pubList->horizontalHeader()->setStretchLastSection(true);
    ui->pubList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void test::on_modifyBtn_clicked()
{

    tag *Tag = new tag(this, currentId);
    connect(Tag, SIGNAL(reloadParent()), this, SLOT(loadModal()));
    Tag->show();
    hide();
}


void test::on_pubList_clicked(const QModelIndex &index)
{
    int idr = index.row();
    currentId = model->index(idr, 0).data().toInt();
    currentPath = model->index(idr, 1).data().toString();
    ui->modifyBtn->setEnabled(true);
    ui->seeBtn->setEnabled(true);
    ui->deleteBtn->setEnabled(true);
}

void test::Onclose()
{
    Parent->show();
    reloadParent();
    this->close();
}
