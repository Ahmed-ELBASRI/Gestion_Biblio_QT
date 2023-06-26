#include "auteurs.h"
#include "ui_auteurs.h"

Auteurs::Auteurs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Auteurs)
{
    ui->setupUi(this);
}

Auteurs::~Auteurs()
{
    delete ui;
}
void Auteurs::showEvent(QShowEvent *event){
    QDialog::showEvent(event);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("gestion_biblio");
    db.open();
    populateAuteursTable();
    ui->bt_ajouter->setEnabled(false);

}
void Auteurs::populateAuteursTable(){
    QSqlQuery query("SELECT * FROM auteur");

    int row = 0;
    if(db.open()){
        if(query.exec()){
            ui->table_auteur->setRowCount(query.size());
            ui->table_auteur->setColumnCount(5);
            while (query.next()) {
                QString idAuteur = query.value("ID_AUTEUR").toString();
                QString nomAuteur = query.value("NOM_AUTEUR").toString();
                QString datNaissance = query.value("DATENAISSANCEAUTEUR").toString();


                QTableWidgetItem *idAut = new QTableWidgetItem(idAuteur);
                QTableWidgetItem *nomAut = new QTableWidgetItem(nomAuteur);
                QTableWidgetItem *datNais = new QTableWidgetItem(datNaissance);



                ui->table_auteur->setItem(row, 0, idAut);
                ui->table_auteur->setItem(row, 1, nomAut);
                ui->table_auteur->setItem(row, 2, datNais);

                QPushButton *refuseButton = new QPushButton("Supprimer");
                QPushButton *modifierButton = new QPushButton("Modifier");
                ui->table_auteur->setCellWidget(row, 3, refuseButton);
                ui->table_auteur->setCellWidget(row, 4, modifierButton);

                connect(refuseButton, &QPushButton::clicked, this, &Auteurs::refuseAuteurs);
                connect(modifierButton, &QPushButton::clicked, this, &Auteurs::modifierAuteurs);

                ++row;
            }
        }else{
            QMessageBox::information(this,"failed","query is false");
        }
    }else{
        QMessageBox::information(this, "Connection",db.lastError().text());
    }
}
void Auteurs::refuseAuteurs(){
    QPushButton* deleteButton = qobject_cast<QPushButton*>(sender());
    int row = ui->table_auteur->indexAt(deleteButton->pos()).row();
    QTableWidgetItem* idItem = ui->table_auteur->item(row, 0);
    QString idAuteur = idItem->text();

    QSqlQuery deleteRedigerQuery;
    deleteRedigerQuery.prepare("DELETE FROM rediger WHERE ID_AUTEUR = :idAuteur");
    deleteRedigerQuery.bindValue(":idAuteur", idAuteur);
    if (!deleteRedigerQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to delete associated rows in the 'rediger' table.");
    }

    QSqlQuery deleteAuteurQuery;
    deleteAuteurQuery.prepare("DELETE FROM auteur WHERE ID_AUTEUR = :auteurID");
    deleteAuteurQuery.bindValue(":auteurID", idAuteur);
    if (!deleteAuteurQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to delete the 'auteur' from the database.");
    }
    QMessageBox::information(this, "Success", "auteur removed successfully");
    populateAuteursTable();
}
void Auteurs::modifierAuteurs(){
    int row = ui->table_auteur->currentRow();
    if (row >= 0) {
        QTableWidgetItem* idItem = ui->table_auteur->item(row, 0);
        QString idAuteur = idItem->text();

        QTableWidgetItem* nameItem = ui->table_auteur->item(row, 1);
        QString auteurNom = nameItem->text();

        QTableWidgetItem* dt_Naiss = ui->table_auteur->item(row, 2);
        QString dt_naissance = dt_Naiss->text();
        QDate birthdayDate = QDate::fromString(dt_naissance, "yyyy-MM-dd");

        ui->tb_auteur->setText(auteurNom);
        ui->dt_naissance->setDate(birthdayDate);

        selectedAuteurId = idAuteur.toInt();
    }
}

void Auteurs::on_bt_ajouter_clicked()
{
    QString nomAuteur = ui->tb_auteur->text();
    QDate selectedDate = ui->dt_naissance->date();
    QString formattedDate = selectedDate.toString("yyyy-MM-dd");

    QSqlQuery maxID("select MAX(ID_AUTEUR) as 'ID' from auteur");
    maxID.exec();
    maxID.next();
    QString ID = maxID.value("ID").toString();
    int IDValue = ID.toInt() + 1;
    QSqlQuery query;
    query.prepare("insert into auteur values(:id,::nomAuteur,:dateNaissance)");
    query.bindValue(":id",IDValue);
    query.bindValue(":libcategorie",nomAuteur);
    query.bindValue(":dateNaissance",formattedDate);
    if(query.exec()){
        QMessageBox::information(this, "Success", "Auteur est ajoute.");

    }else{
        QMessageBox::information(this, "Error", query.lastError().text());
    }
    ui->tb_auteur->clear();
    populateAuteursTable();
}


void Auteurs::on_ck_modifer_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked){
        ui->bt_ajouter->setEnabled(true);
        ui->bt_modifier->setEnabled(false);
        ui->table_auteur->setColumnHidden(4,true);
        ui->tb_auteur->clear();
    }else{
        ui->bt_ajouter->setEnabled(false);
        ui->bt_modifier->setEnabled(true);
        ui->table_auteur->setColumnHidden(4,false);

    }
}


void Auteurs::on_bt_modifier_clicked()
{
    QString auteur = ui->tb_auteur->text();
    QString dateNaissance = ui->dt_naissance->date().toString("yyyy-MM-dd");


    QSqlQuery query;
    query.prepare("update auteur set NOM_AUTEUR =:nomauteur,DATENAISSANCEAUTEUR=:dtn where ID_AUTEUR=:id");
    query.bindValue(":id",selectedAuteurId);
    query.bindValue(":nomauteur",auteur);
    query.bindValue(":dtn",dateNaissance);
    if(query.exec()){
        QMessageBox::information(this, "Success", "Auteur est modifier.");

    }else{
        QMessageBox::information(this, "Error", query.lastError().text());
    }
    ui->tb_auteur->clear();
    populateAuteursTable();
}

