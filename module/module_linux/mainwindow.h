#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtSql>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pubList_activated(const QModelIndex &index);
    void open();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
     QSqlTableModel *model ;
     QString filePath;
};

#endif // MAINWINDOW_H
