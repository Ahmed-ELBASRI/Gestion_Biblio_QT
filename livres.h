#ifndef LIVRES_H
#define LIVRES_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QFileDialog>
namespace Ui {
class livres;
}

class livres : public QDialog
{
    Q_OBJECT

public:
    explicit livres(QWidget *parent = nullptr);
    ~livres();

private slots:
    void on_bt_upload_clicked();

    void on_bt_upload_min_clicked();

    void on_cb_etagers_currentIndexChanged();

    void on_bt_ajouter_clicked();

private:
    Ui::livres *ui;
    void showEvent(QShowEvent *event);
    QSqlDatabase db;
    void populateCombosLivre();
};

#endif // LIVRES_H
