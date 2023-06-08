#ifndef RESERVATION_H
#define RESERVATION_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDateTime>
namespace Ui {
class reservation;
}

class reservation : public QDialog
{
    Q_OBJECT
public:
    explicit reservation(QWidget *parent = nullptr);
    ~reservation();


private:
    Ui::reservation *ui;
    void showEvent(QShowEvent *event);
    QSqlDatabase db;
    void populateReservationTable();

private slots:
    void refuseReservation();
    void confirmReservation();
    void on_bt_login_clicked();
    void on_bt_recherche_clicked();
    void on_bt_recherche_2_clicked();
    void on_bt_reload_clicked();
};

#endif // RESERVATION_H
