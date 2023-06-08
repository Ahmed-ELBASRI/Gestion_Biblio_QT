#include "categories.h"
#include "ui_categories.h"

categories::categories(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::categories)
{
    ui->setupUi(this);
}

categories::~categories()
{
    delete ui;
}
