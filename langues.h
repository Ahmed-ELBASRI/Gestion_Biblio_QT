#ifndef LANGUES_H
#define LANGUES_H

#include <QDialog>

namespace Ui {
class Langues;
}

class Langues : public QDialog
{
    Q_OBJECT

public:
    explicit Langues(QWidget *parent = nullptr);
    ~Langues();

private:
    Ui::Langues *ui;
};

#endif // LANGUES_H
