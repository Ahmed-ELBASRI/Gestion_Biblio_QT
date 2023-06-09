#ifndef EMPRUNTES_H
#define EMPRUNTES_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDateTime>
namespace Ui {
class enmpruntes;
}

class enmpruntes : public QDialog
{
    Q_OBJECT

public:
    explicit enmpruntes(QWidget *parent = nullptr);
    ~enmpruntes();

private slots:
    void on_bt_reload_clicked();

    void on_bt_recherche_clicked();

private:
    Ui::enmpruntes *ui;
    void showEvent(QShowEvent *event);
    QSqlDatabase db;
    void populateEmprunteTable();
};

#endif // EMPRUNTES_H
