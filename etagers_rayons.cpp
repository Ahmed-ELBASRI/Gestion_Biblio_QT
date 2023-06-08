#include "etagers_rayons.h"
#include "ui_etagers_rayons.h"

etages_rayons::etages_rayons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::etages_rayons)
{
    ui->setupUi(this);
}

etages_rayons::~etages_rayons()
{
    delete ui;
}
