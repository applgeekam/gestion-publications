#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "test.h"
#include "methodes.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = initBd();
    load();
    ui->datePub->calendarPopup();
    connect(ui->importBtn, SIGNAL(clicked()), this, SLOT(openFile()));
}

MainWindow::~MainWindow()
{
    onClose();
    delete ui;
}

void MainWindow::on_btConsulter_clicked()
{
    OnConsulter();
}

void MainWindow::on_pushButton_4_clicked()
{
    onClose();
}

void MainWindow::on_actionConsultation_triggered()
{
    OnConsulter();
}

void MainWindow::on_actionQuitter_triggered()
{
    onClose();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->numPub->text() == "" || ui->filePath->text() == "")
    {
        showInfoToUser(this, "Veuillez donner une valeur a chaque champs s'il vous plait.");

    }
    else
    {
        numPub = ui->numPub->text();
        datePub = ui->datePub->date();
        typePub = ui->typeList->currentIndex();
        save();
    }
}

void MainWindow::openFile()
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
        QDateTime currentDate = QDateTime::currentDateTime();
        if(!QDir(dir + "/Publications").exists())
        {
            QDir().mkdir(dir + "/Publications");
        }

        QString newFilePath = dir + "/Publications/" + filename + "_" + currentDate.toString("d-M-yyyy") + "." + ext;

        if(!QFile::exists(newFilePath))
        {
            QString fullFileName = filename + "." + ext;
            namePub = fullFileName;
            pathOfOriginalSelectedFile = pathOfOriginal;
            pubPath = newFilePath;
            ui->filePath->setText(fullFileName);
        }
        else
        {
            showInfoToUser(this, "Le fichier que vous essayer de charger existe déja. Essayer plutot de la modifier.");
        }
    }

}

void MainWindow::save()
{
    bool cp = QFile::copy(pathOfOriginalSelectedFile, pubPath);
    if(cp == false)
    {
        showInfoToUser(this, "Le chargement du fichier a echoue. Veuillez reessayer s'il vous plait.");
        return;
    }

    QFile(pubPath).setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);

    QSqlTableModel model;
    model.setTable("publications");
    int count = model.rowCount();
    model.insertRows(count, 1);
    model.setData(model.index(count, 5), numPub);
    model.setData(model.index(count, 6), namePub);
    model.setData(model.index(count, 1), pubPath);
    model.setData(model.index(count, 2), datePub);
    model.setData(model.index(count, 4), typePub + 1);
    model.setData(model.index(count, 3), QDateTime::currentDateTime());
    bool isSend = model.submitAll();

    if(isSend)
    {
        showInfoToUser(this, "Enregistrement effectue avec succes");
        ui->numPub->setText("");
        ui->filePath->setText("");
        ui->typeList->setCurrentIndex(0);
        if(modelCount <= 0)
            ui->btConsulter->setEnabled(true);
        modelCount++;
    }
    else
    {
        showInfoToUser(this, "L'enregistrement a echoué. Veuillez verifier les donnees et reessaye");
    }
}

void MainWindow::load()
{
    QSqlQuery requeteur;
    requeteur.exec("SELECT * FROM types");
    while(requeteur.next())
    {
        ui->typeList->addItem(requeteur.value(1).toString());
    }
    ui->typeList->setCurrentIndex(0);


    QSqlTableModel model;
    model.setTable("publications");
    model.select();
    modelCount = model.rowCount();
    if(modelCount <= 0)
        ui->btConsulter->setEnabled(false);
}

void MainWindow::OnConsulter()
{
    test *Test = new test(this);
    connect(Test, SIGNAL(reloadParent()), this, SLOT(load()));
    Test->show();
    hide();
}

void MainWindow::onClose()
{
    closeDB(db);
    this->close();
}

void MainWindow::on_actionNouveau_triggered()
{
    this->show();
}
