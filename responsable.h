#ifndef RESPONSABLE_H
#define RESPONSABLE_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QFileDialog>
#include <QDate>

namespace Ui {
class responsable;
}

class responsable : public QDialog
{
    Q_OBJECT

public:
    explicit responsable(QWidget *parent = nullptr);
    ~responsable();

private:
    Ui::responsable *ui;
    void showEvent(QShowEvent *event);
    QSqlDatabase db;
    void populateResponsalbesTable();
    int selectedResponsableId ;
private slots:
    void refuseResponsable();
    void modifierResponsable();
    void on_bt_ajouter_clicked();
    void on_ck_modifer_stateChanged(int arg1);
    void on_bt_modifier_clicked();
};


#endif // RESPONSABLE_H
