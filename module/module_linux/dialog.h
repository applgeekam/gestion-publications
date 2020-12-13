#ifndef DIALOG_H
#define DIALOG_H
#include <QtSql>

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0, QString id = "");
    ~Dialog();

private:
    Ui::Dialog *ui;
        QSqlTableModel *model ;
};

#endif // DIALOG_H
