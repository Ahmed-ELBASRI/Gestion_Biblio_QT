#ifndef ETAGERS_RAYONS_H
#define ETAGERS_RAYONS_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QFileDialog>

namespace Ui {
class etages_rayons;
}

class etages_rayons : public QDialog
{
    Q_OBJECT

public:
    explicit etages_rayons(QWidget *parent = nullptr);
    ~etages_rayons();

private:
    Ui::etages_rayons *ui;
    void showEvent(QShowEvent *event);
    QSqlDatabase db;
    void populateEtagersTable();
    void populateRayonsTable();
    void populateEtagersRayonsCombos();

private slots:
    void refuseEtager();
    void on_bt_ajouter_clicked();
    void on_cb_etager_currentIndexChanged(int index);
    void on_cb_rayon_currentIndexChanged(int index);
    void on_bt_reload_clicked();
};

#endif // ETAGERS_RAYONS_H
