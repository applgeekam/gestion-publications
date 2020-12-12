#ifndef TEST_H
#define TEST_H
#include <QtSql>

#include <QDialog>

namespace Ui {
class test;
}

class test : public QDialog
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = 0);
    ~test();


private slots:

    void on_backBtn_clicked();

    void on_test_rejected();

    void on_seeBtn_clicked();

    void on_deleteBtn_clicked();

    void on_modifyBtn_clicked();

    void loadModal();

    void on_pubList_clicked(const QModelIndex &index);

    void Onclose();

signals:

    void reloadParent();

private:
    Ui::test *ui;
    QWidget *Parent;
    QSqlRelationalTableModel *model ;
    int currentId;
    QString currentPath;

};

#endif // TEST_H
