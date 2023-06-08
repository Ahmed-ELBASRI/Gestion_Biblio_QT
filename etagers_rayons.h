#ifndef ETAGERS_RAYONS_H
#define ETAGERS_RAYONS_H

#include <QDialog>

namespace Ui {
class etages_rayons;
}

class etages_rayons : public QDialog
{
    Q_OBJECT

public:
    explicit etages_rayons(QWidget *parent = nullptr);
    ~etages_rayons();

private:
    Ui::etages_rayons *ui;
};

#endif // ETAGERS_RAYONS_H
