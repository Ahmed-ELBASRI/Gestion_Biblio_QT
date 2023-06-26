#ifndef CATEGORIES_H
#define CATEGORIES_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QFileDialog>

namespace Ui {
class categories;
}

class categories : public QDialog
{
    Q_OBJECT

public:
    explicit categories(QWidget *parent = nullptr);
    ~categories();

private:
    Ui::categories *ui;
    void showEvent(QShowEvent *event);
    QSqlDatabase db;
    void populateCategorieTable();
    int selectedCategoryId ;
private slots:
    void refuseCategorie();
    void modifierCategorie();
    void on_bt_upload_clicked();
    void on_bt_ajouter_clicked();
    void on_table_categorie_cellClicked(int row, int column);
    void on_ck_modifer_stateChanged(int arg1);
    void on_bt_modifier_clicked();
};

#endif // CATEGORIES_H
