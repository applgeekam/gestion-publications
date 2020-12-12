#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QtSql>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void OnConsulter();
    void onClose();
    ~MainWindow();

private slots:
    void on_btConsulter_clicked();

    void on_pushButton_4_clicked();

    void on_actionConsultation_triggered();

    void on_actionQuitter_triggered();

    void on_pushButton_2_clicked();

    void openFile();

    void save();

    void load();

    void on_actionNouveau_triggered();

private:
    Ui::MainWindow *ui;
    int typePub;
    int modelCount;
    QSqlDatabase db;
    QString numPub;
    QString namePub;
    QString pubPath;
    QString pathOfOriginalSelectedFile;
    QDate datePub;

};

#endif // MAINWINDOW_H
