#ifndef TAG_H
#define TAG_H

#include <QDialog>
#include "test.h"

namespace Ui {
class tag;
}

class tag : public QDialog
{
    Q_OBJECT

public:
    explicit tag(QWidget *parent = 0, int id = 0);
    void showInfoToUser(const char* message);
    ~tag();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void open();

    void on_tag_destroyed();

    void Onclose();

signals:

    void reloadParent();

private:
    Ui::tag *ui;
    QWidget *Parent;
    QSqlTableModel *model ;
    QSqlTableModel *typeModel ;
    int currentId;
    QString namePub;
    QString pubPath;
    QString updatePubPath;
    QString pathOfOriginalSelectedFile;
};

#endif // TAG_H
