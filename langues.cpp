#include "langues.h"
#include "ui_langues.h"

Langues::Langues(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Langues)
{
    ui->setupUi(this);
}

Langues::~Langues()
{
    delete ui;
}
