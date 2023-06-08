#ifndef AUTEURS_H
#define AUTEURS_H

#include <QDialog>

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
};

#endif // AUTEURS_H
