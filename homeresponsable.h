#ifndef HOMERESPONSABLE_H
#define HOMERESPONSABLE_H

#include <QDialog>
#include <QMessageBox>
#include "reservation.h"
#include "auteurs.h"
#include "categories.h"
#include "empruntes.h"
#include "etagers_rayons.h"
#include "langues.h"
#include "livres.h"
#include <QtSql>
#include <QSqlDatabase>
namespace Ui {
class HomeResponsable;
}

class HomeResponsable : public QDialog
{
    Q_OBJECT

public:
    explicit HomeResponsable(QWidget *parent = nullptr);
    ~HomeResponsable();

private:
    Ui::HomeResponsable *ui;
    reservation *res;
    Auteurs *auteur;
    categories *categorie;
    Langues *langue;
    livres *livre;
    enmpruntes *emprunte;
    etages_rayons *etager_rayon;
    QSqlDatabase db;
private slots:
    void on_bt_reservation_clicked();

    void on_bt_emprunte_clicked();

    void on_bt_livre_clicked();

    void on_bt_etager_rayon_clicked();

    void on_bt_categorie_clicked();

    void on_bt_auteur_clicked();

    void on_bt_langue_clicked();

};

#endif // HOMERESPONSABLE_H
