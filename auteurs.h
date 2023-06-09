#ifndef AUTEURS_H
#define AUTEURS_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QFileDialog>

namespace Ui {
class Auteurs;
}

class Auteurs : public QDialog
{
    Q_OBJECT

public:
    explicit Auteurs(QWidget *parent = nullptr);
    ~Auteurs();

private:
    Ui::Auteurs *ui;
    void showEvent(QShowEvent *event);
    QSqlDatabase db;
    void populateAuteursTable();
    int selectedAuteurId ;
private slots:
    void refuseAuteurs();
    void modifierAuteurs();
    void on_bt_ajouter_clicked();
    void on_ck_modifer_stateChanged(int arg1);
    void on_bt_modifier_clicked();
};

#endif // AUTEURS_H
