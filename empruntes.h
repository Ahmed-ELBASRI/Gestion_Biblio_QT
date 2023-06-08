#ifndef EMPRUNTES_H
#define EMPRUNTES_H

#include <QDialog>

namespace Ui {
class enmpruntes;
}

class enmpruntes : public QDialog
{
    Q_OBJECT

public:
    explicit enmpruntes(QWidget *parent = nullptr);
    ~enmpruntes();

private:
    Ui::enmpruntes *ui;
};

#endif // EMPRUNTES_H
