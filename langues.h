#ifndef LANGUES_H
#define LANGUES_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QFileDialog>
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
    void showEvent(QShowEvent *event);
    QSqlDatabase db;
    void populateLanguesTable();
    int selectedLangueId;
private slots:
    void refuseLangues();
    void modifierLangue();
    void on_bt_ajouter_clicked();
    void on_ck_modifer_stateChanged(int arg1);
    void on_bt_modifier_clicked();
};

#endif // LANGUES_H
