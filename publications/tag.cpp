#include "tag.h"
#include "ui_tag.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>


tag::tag(QWidget *parent,  int id) :
    QDialog(parent),
    ui(new Ui::tag)
{
    ui->setupUi(this);

    Parent = parent;
    currentId = id;
    QString request;
    QSqlQuery requeteur;

    requeteur.exec("SELECT * FROM types");
    typeModel = new QSqlTableModel(this);
    typeModel->setTable("types");
    typeModel->select();
    for(int i = 0; i < typeModel->rowCount(); i++)
    {
        QSqlRecord record = typeModel->record(i);
        ui->typeList->addItem(record.value(1).toString());
    }

    requeteur.exec("SELECT * FROM publications");
    request = QString("pubId=%1").arg(currentId);
    model = new QSqlTableModel(this);
    model->setTable("publications");
    model->setFilter(request);
    model->select();

    if(model->rowCount() > 0)
    {
        QSqlRecord record = model->record(0);
        ui->datePub->setDate(QDate::fromString(record.value(2).toString(), "d/M/yyyy"));
        ui->numPub->setText(record.value(5).toString());
        ui->filePath->setText(record.value(6).toString());

        request = QString("id=%1").arg(record.value(4).toInt());
        typeModel->setFilter(request);
        typeModel->select();
        QSqlRecord recordType = typeModel->record(0);
        ui->typeList->setCurrentText(recordType.value(1).toString());

        namePub = record.value(6).toString();
        pubPath = record.value(1).toString();
        pathOfOriginalSelectedFile = "";
    }
    else
    {
        close();
        showInfoToUser("Verifier les informations relatives a la publications, puis reessayer.");
    }

    connect(ui->importBtn, SIGNAL(clicked()), this, SLOT(open()));

    // qDebug() << currentId;
}

tag::~tag()
{
    delete ui;
}

void tag::on_pushButton_4_clicked()
{
    Onclose();
}

void tag::open()
{

    QString dir =  QDir::homePath();
    QString file;
    const char *types = "Documents (*.pdf *.doc *.docx);;Images (*.png *.xpm *.jpg);;Text Files (*.txt)";

    file = QFileDialog::getOpenFileName(this, tr("Open a File"), dir, tr(types));

    if (file != "")
    {

        QString pathOfOriginal = QFileInfo(file).absoluteFilePath();
        QString filename = QFileInfo(file).baseName();
        QString ext = QFileInfo(file).completeSuffix();


        if(!QDir(dir + "/Publications").exists())
        {
            QDir().mkdir(dir + "/Publications");
        }

        QDateTime currentDate = QDateTime::currentDateTime();
        QString newFilePath = dir + "/Publications/" + filename + "_" + currentDate.toString("d-M-yyyy") + "." + ext;

        QString fullFileName = filename + "." + ext;
        namePub = fullFileName;
        pathOfOriginalSelectedFile = pathOfOriginal;
        updatePubPath = newFilePath;
        ui->filePath->setText(fullFileName);

    }

}

void tag::on_pushButton_3_clicked()
{
    if(ui->numPub->text() == "" || ui->filePath->text() == "")
    {
        showInfoToUser("Veuillez donner une valeur a chaque champs s'il vous plait.");
    }
    else
    {
            QString numPub = ui->numPub->text();
            QDate datePub = ui->datePub->date();
            QString typePub = ui->typeList->currentText();

            if(pathOfOriginalSelectedFile != "")
            {
                 //this app don't has ability to remove file from this directory, if not this code check if this action is done
                 bool valid = QFile::remove(pubPath);
                 if(!valid)
                 {
                     showInfoToUser("La suppression de l'ancien fichier a echoué. Veuillez reessayer s'il vous plait.");
                     return;
                 }

                bool cp = QFile::copy(pathOfOriginalSelectedFile, updatePubPath);
                if(!cp)
                {
                    showInfoToUser("Le chargement du fichier a echoue. Veuillez reessayer s'il vous plait.");
                    return;
                }
            }
            else
            {
                updatePubPath = pubPath;
            }



            QSqlRecord record = model->record(0);

            // Update each field
            record.setValue(1, updatePubPath);
            record.setValue(2, datePub.toString("dd/MM/yyyy"));
            record.setValue(3, QString("%1").arg(QDateTime::currentDateTime().toString("d/M/yyyy hh:mm:ss")));

            QSqlQuery requeteur;
            QString request;
            requeteur.exec("SELECT * FROM types");
            typeModel = new QSqlTableModel(this);
            request = QString("code='%1'").arg(typePub);
            typeModel->setTable("types");
            typeModel->setFilter(request);
            typeModel->select();
            QSqlRecord recordType = typeModel->record(0);
            record.setValue(4, recordType.value(0).toInt());


            record.setValue(5, numPub);
            record.setValue(6, namePub);

            bool isUpdate = model->setRecord(0, record);

            if(isUpdate)
            {
                showInfoToUser("Modification effectue avec succes");
                Onclose();
            }
            else
            {
                showInfoToUser("L'enregistrement a echoué. Veuillez verifier les donnees et reessaye");
            }
    }
}

void tag::showInfoToUser(const char *message)
{
    QMessageBox::information(this,QObject::tr("Information"), tr(message));
}

void tag::on_tag_destroyed()
{
   Onclose();
}

void tag::Onclose(){
    Parent->show();
    reloadParent();
    this->close();
}

