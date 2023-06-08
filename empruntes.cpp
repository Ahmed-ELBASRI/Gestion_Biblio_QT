#include "empruntes.h"
#include "ui_empruntes.h"

enmpruntes::enmpruntes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::enmpruntes)
{
    ui->setupUi(this);
}

enmpruntes::~enmpruntes()
{
    delete ui;
}
