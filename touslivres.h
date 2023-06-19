#ifndef TOUSLIVRES_H
#define TOUSLIVRES_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDateTime>

namespace Ui {
class tousLivres;
}

class tousLivres : public QDialog
{
    Q_OBJECT

public:
    explicit tousLivres(QWidget *parent = nullptr);
    ~tousLivres();

private slots:
    void on_bt_reload_clicked();

    void on_bt_recherche_clicked();

private:
    Ui::tousLivres *ui;
    void showEvent(QShowEvent *event);
    QSqlDatabase db;
    void populateReservationTable();
};

#endif // TOUSLIVRES_H
