#include "auteurs.h"
#include "ui_auteurs.h"

Auteurs::Auteurs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Auteurs)
{
    ui->setupUi(this);
}

Auteurs::~Auteurs()
{
    delete ui;
}
