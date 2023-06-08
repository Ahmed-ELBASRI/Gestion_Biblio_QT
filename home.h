#ifndef HOME_H
#define HOME_H

#include <QDialog>
#include "reservation.h"
#include "auteurs.h"
#include "categories.h"
#include "empruntes.h"
#include "etagers_rayons.h"
#include "langues.h"
#include "livres.h"

namespace Ui {
class home;
}

class home : public QDialog
{
    Q_OBJECT

public:
    explicit home(QWidget *parent = nullptr);
    ~home();

private slots:
    void on_bt_reservation_clicked();

    void on_bt_emprunte_clicked();

    void on_bt_livre_clicked();

    void on_bt_etager_rayon_clicked();

    void on_bt_categorie_clicked();

    void on_bt_auteur_clicked();

    void on_bt_langue_clicked();

private:
    Ui::home *ui;
    reservation *res;
    Auteurs *auteur;
    categories *categorie;
    Langues *langue;
    livres *livre;
    enmpruntes *emprunte;
    etages_rayons *etager_rayon;

};

#endif // HOME_H
