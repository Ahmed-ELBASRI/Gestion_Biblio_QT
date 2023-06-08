#include "home.h"
#include "ui_home.h"

home::home(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::home)
{
    ui->setupUi(this);
    res = new reservation(ui->action);
    res->hide();
    auteur = new Auteurs(ui->action);
    auteur->hide();
    categorie = new categories(ui->action);
    categorie->hide();
    livre = new livres(ui->action);
    livre->hide();
    emprunte = new enmpruntes(ui->action);
    emprunte->hide();
    langue = new Langues(ui->action);
    langue->hide();
    etager_rayon = new etages_rayons(ui->action);
    etager_rayon->hide();
}

home::~home()
{
    delete ui;
}

void home::on_bt_reservation_clicked()
{
    if (!res) {
        res = new reservation(this);
        res->hide();
    }
    res->show();
}


void home::on_bt_emprunte_clicked()
{
    if (!emprunte) {
        emprunte = new enmpruntes(this);
        emprunte->hide();
    }
    emprunte->show();
}


void home::on_bt_livre_clicked()
{
    if (!livre) {
        livre = new livres(this);
        livre->hide();
    }
    livre->show();
}


void home::on_bt_etager_rayon_clicked()
{
    if (!etager_rayon) {
        etager_rayon = new etages_rayons(this);
        etager_rayon->hide();
    }
    etager_rayon->show();
}


void home::on_bt_categorie_clicked()
{
    if (!categorie) {
        categorie = new categories(this);
        categorie->hide();
    }
    categorie->show();
}


void home::on_bt_auteur_clicked()
{
    if (!auteur) {
        auteur = new Auteurs(this);
        auteur->hide();
    }
    auteur->show();
}


void home::on_bt_langue_clicked()
{
    if (!langue) {
        langue = new Langues(this);
        langue->hide();
    }
    langue->show();
}

