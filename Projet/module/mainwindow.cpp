#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "metodes.h"
#include <QtSql>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDesktopServices>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initBd();

    QSqlQuery requeteur;
    requeteur.exec("SELECT * FROM test");
    while(requeteur.next())
    {
        QString libelle_rubrique = requeteur.value(0).toString();
        ui->comboBox->addItem(libelle_rubrique);
    }

    requeteur.exec("SELECT * FROM pub");
    model = new QSqlTableModel(this);
    model->setTable("pub");
    model->setSort(1, Qt::AscendingOrder); // Définition du critère de tri
    model->setHeaderData(1, Qt::Horizontal, "Libelle"); // Définition de l'entête
    model->select();

    ui->pubList->setModel(model); // Liaison entre le modèle et le tableau
    ui->pubList->setColumnHidden(0, true); // On masque la colonne des identifiants
    ui->pubList->resizeColumnsToContents();
    ui->pubList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(open()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pubList_activated(const QModelIndex &index)
{
    int idr = index.row();
    int idc = index.column();
    QModelIndex id = model->index(idr, idc, index);
    QString val = ui->pubList->model()->data(id, 0).toString();
    qDebug() << val;
}

void MainWindow::on_pushButton_3_clicked()
{

}

void MainWindow::open()
{

    QString storagePath = QStandardPaths::displayName(QStandardPaths::DataLocation);
    QString dir =  QDir::homePath();
    QString file;
    const char *types = "Documents (*.pdf *.doc *.docx);;Images (*.png *.xpm *.jpg);;Text Files (*.txt)";

    file = QFileDialog::getOpenFileName(this, tr("Open a File"), dir, tr(types));

    if (file != "")
    {

        QString pathOfOriginal = QFileInfo(file).absoluteFilePath();
        QString filename = QFileInfo(file).baseName();
        QString ext = QFileInfo(file).completeSuffix();
        ui->label->setText(pathOfOriginal);
        QString newFilePath = dir + "/" + filename + "." + ext;
        if(!QFile::exists(newFilePath))
        {
            qDebug() << "step 1";
            bool cp = QFile::copy(pathOfOriginal, newFilePath);
            if(cp)
            {
                qDebug() << "step 2";
                filePath = newFilePath;
                qDebug() << newFilePath;

            }
            else
            {
                qDebug() << cp;
            }
        }
        qDebug() << storagePath;
        qDebug() << dir;
    }
}

void MainWindow::on_pushButton_4_clicked()
{
        QDesktopServices::openUrl(QUrl("file:///" + filePath, QUrl::TolerantMode));
        qDebug() << "exec";
}
