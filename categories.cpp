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
void categories::showEvent(QShowEvent *event){
    QDialog::showEvent(event);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("gestion_biblio");
    db.open();
    populateCategorieTable();
    ui->bt_ajouter->setEnabled(false);

}
void categories::populateCategorieTable(){
    QSqlQuery query("SELECT * FROM categorie");

    int row = 0;
    if(db.open()){
        if(query.exec()){
            ui->table_categorie->setRowCount(query.size());
            ui->table_categorie->setColumnCount(5);
            while (query.next()) {
                QString idCategorie = query.value("ID_CATEGORIE").toString();
                QString libCategorie = query.value("LIBELLE_CATEGORIE").toString();
                QString photoCategorie = query.value("photoCategorie").toString();


                QTableWidgetItem *idCat = new QTableWidgetItem(idCategorie);
                QTableWidgetItem *libCat = new QTableWidgetItem(libCategorie);
                QTableWidgetItem *photoCat = new QTableWidgetItem(photoCategorie);



                ui->table_categorie->setItem(row, 0, idCat);
                ui->table_categorie->setItem(row, 1, libCat);
                ui->table_categorie->setItem(row, 2, photoCat);



                QPushButton *refuseButton = new QPushButton("Supprimer");
                QPushButton *modifierButton = new QPushButton("Modifier");
                ui->table_categorie->setCellWidget(row, 3, refuseButton);
                ui->table_categorie->setCellWidget(row, 4, modifierButton);

                connect(refuseButton, &QPushButton::clicked, this, &categories::refuseCategorie);
                connect(modifierButton, &QPushButton::clicked, this, &categories::modifierCategorie);

                ++row;
            }
        }else{
            QMessageBox::information(this,"failed","query is false");
        }
    }else{
        QMessageBox::information(this, "Connection",db.lastError().text());
    }
}
void categories::refuseCategorie(){
    QPushButton* deleteButton = qobject_cast<QPushButton*>(sender());
    int row = ui->table_categorie->indexAt(deleteButton->pos()).row();
    QTableWidgetItem* idItem = ui->table_categorie->item(row, 0);
    QString idCategorie = idItem->text();

    QSqlQuery deleteLivreQuery;
    deleteLivreQuery.prepare("update livre set ID_CATEGORIE = NULL WHERE ID_CATEGORIE = :categorieID");
    deleteLivreQuery.bindValue(":categorieID", idCategorie);
    if (!deleteLivreQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to delete associated rows in the 'rayon' table.");
    }

    // Delete the 'etager' from the database
    QSqlQuery deleteCategorieQuery;
    deleteCategorieQuery.prepare("DELETE FROM categorie WHERE ID_CATEGORIE = :categorieID");
    deleteCategorieQuery.bindValue(":categorieID", idCategorie);
    if (!deleteCategorieQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to delete the 'etager' from the database.");
    }
    QMessageBox::information(this, "Success", " categorie removed successfully.");
    populateCategorieTable();
}
void categories::modifierCategorie(){
    int row = ui->table_categorie->currentRow();
    if (row >= 0) {
        QTableWidgetItem* idItem = ui->table_categorie->item(row, 0);
        QString idCategorie = idItem->text();

        QTableWidgetItem* nameItem = ui->table_categorie->item(row, 1);
        QString categoryName = nameItem->text();

        QTableWidgetItem* photoItem = ui->table_categorie->item(row, 2);
        QString photoPath = photoItem->text();

        ui->tb_categorie->setText(categoryName);
        ui->tb_pathphoto->setText(photoPath);

        selectedCategoryId = idCategorie.toInt();
    }
}

void categories::on_bt_upload_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select Categorie Image", "", "Image Files (*.png *.jpg *.jpeg)");
    if (!filePath.isEmpty()) {
        ui->tb_pathphoto->setText(filePath);
    }
}


void categories::on_bt_ajouter_clicked()
{
    QString categorie = ui->tb_categorie->text();
    QString categoriePath = ui->tb_pathphoto->text();
    QString destinationDirectory = "C:/xampp/htdocs/GestionBiblio/images";
    QString fileName = QFileInfo(categoriePath).fileName();
    QString destinationPath = QDir(destinationDirectory).filePath(fileName);
    QFile::copy(categoriePath, destinationPath);
    QString subPath = destinationPath.mid(destinationPath.indexOf("images"));

    QSqlQuery maxID("select MAX(ID_CATEGORIE) as 'ID' from categorie");
    maxID.exec();
    maxID.next();
    QString ID = maxID.value("ID").toString();
    int IDValue = ID.toInt() + 1;
    QSqlQuery query;
    query.prepare("insert into categorie values(:id,:libcategorie,:photopath)");
    query.bindValue(":id",IDValue);
    query.bindValue(":libcategorie",categorie);
    query.bindValue(":photopath",subPath);
    if(query.exec()){
        QMessageBox::information(this, "Success", "Categorie est ajoute.");

    }else{
        QMessageBox::information(this, "Error", query.lastError().text());
    }
    ui->tb_categorie->clear();
    ui->tb_pathphoto->clear();
    populateCategorieTable();
}


void categories::on_table_categorie_cellClicked(int row, int column)
{
    QTableWidgetItem* idItem = ui->table_categorie->item(row, 0);
    QTableWidgetItem* libelleItem = ui->table_categorie->item(row, 1);
    QTableWidgetItem* photoItem = ui->table_categorie->item(row, 2);

    if (idItem && libelleItem && photoItem) {
        QString categoryId = idItem->text();
        QString libelle = libelleItem->text();
        QString photoPath = photoItem->text();

        ui->tb_categorie->setText(libelle);
        ui->tb_pathphoto->setText(photoPath);

        selectedCategoryId = categoryId.toInt();
    }
}


void categories::on_ck_modifer_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked){
        ui->bt_ajouter->setEnabled(true);
        ui->bt_modifier->setEnabled(false);
        ui->table_categorie->setColumnHidden(4,true);
        ui->tb_categorie->clear();
        ui->tb_pathphoto->clear();
    }else{
        ui->bt_ajouter->setEnabled(false);
        ui->bt_modifier->setEnabled(true);
        ui->table_categorie->setColumnHidden(4,false);

    }
}


void categories::on_bt_modifier_clicked()
{
    QString categorie = ui->tb_categorie->text();
    QString categoriePath = ui->tb_pathphoto->text();
    QString destinationDirectory = "C:/xampp/htdocs/GestionBiblio/images";
    QString fileName = QFileInfo(categoriePath).fileName();
    QString destinationPath = QDir(destinationDirectory).filePath(fileName);
    QFile::copy(categoriePath, destinationPath);
    QString subPath = destinationPath.mid(destinationPath.indexOf("images"));


    QSqlQuery query;
    query.prepare("update categorie set LIBELLE_CATEGORIE =:libcategorie,photoCategorie=:photopath where ID_CATEGORIE=:id");
    query.bindValue(":id",selectedCategoryId);
    query.bindValue(":libcategorie",categorie);
    query.bindValue(":photopath",subPath);
    if(query.exec()){
        QMessageBox::information(this, "Success", "Categorie est modifier.");

    }else{
        QMessageBox::information(this, "Error", query.lastError().text());
    }
    ui->tb_categorie->clear();
    ui->tb_pathphoto->clear();
    populateCategorieTable();
}

