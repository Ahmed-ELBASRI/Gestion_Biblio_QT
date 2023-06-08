#include "livres.h"
#include "ui_livres.h"

livres::livres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::livres)
{
    ui->setupUi(this);
}

livres::~livres()
{
    delete ui;
}
