#include "etagers_rayons.h"
#include "ui_etagers_rayons.h"

etages_rayons::etages_rayons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::etages_rayons)
{
    ui->setupUi(this);
}

etages_rayons::~etages_rayons()
{
    delete ui;
}
void etages_rayons::showEvent(QShowEvent *event){
    QDialog::showEvent(event);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("gestion_biblio");
    db.open();
    populateEtagersRayonsCombos();
    populateEtagersTable();
    populateRayonsTable();
}
void etages_rayons::populateEtagersRayonsCombos(){
    QSqlQuery etagerQuery("select ID_ETAGERE from etagere");
    if(etagerQuery.exec()){
        while (etagerQuery.next()) {
            QString etager = etagerQuery.value("ID_ETAGERE").toString();
            ui->cb_etager->addItem(etager);
            ui->cb_etager->setItemData(ui->cb_etager->count() - 1, etager);
        }
    }
}
void etages_rayons::populateEtagersTable(){
    QSqlQuery query("SELECT * FROM etagere");

    int row = 0;
    if(db.open()){
        if(query.exec()){
            ui->tabe_etagers->setRowCount(query.size());
            ui->tabe_etagers->setColumnCount(3);
            while (query.next()) {
                QString idEtager = query.value("ID_ETAGERE").toString();
                QString nbrRayon = query.value("NBRRAYON").toString();


                QTableWidgetItem *idEtag = new QTableWidgetItem(idEtager);
                QTableWidgetItem *nbrRay = new QTableWidgetItem(nbrRayon);



                ui->tabe_etagers->setItem(row, 0, idEtag);
                ui->tabe_etagers->setItem(row, 1, nbrRay);

                QPushButton *refuseButton = new QPushButton("Supprimer");
                ui->tabe_etagers->setCellWidget(row, 2, refuseButton);

                connect(refuseButton, &QPushButton::clicked, this, &etages_rayons::refuseEtager);

                ++row;
            }
        }else{
            QMessageBox::information(this,"failed","query is false");
        }
    }else{
        QMessageBox::information(this, "Connection",db.lastError().text());
    }
}

void etages_rayons::populateRayonsTable(){
    QSqlQuery query("SELECT * FROM rayon");

    int row = 0;
    if(db.open()){
        if(query.exec()){
            ui->table_rayon->setRowCount(query.size());
            ui->table_rayon->setColumnCount(3);
            while (query.next()) {
                QString idRayon = query.value("ID_RAYON").toString();
                QString idEtager = query.value("ID_ETAGER").toString();
                QString capRayon = query.value("CAPACITERAYON").toString();

                //Retrieve other reservation details as needed

                QTableWidgetItem *idRay = new QTableWidgetItem(idRayon);
                QTableWidgetItem *idEtag = new QTableWidgetItem(idEtager);
                QTableWidgetItem *capRay = new QTableWidgetItem(capRayon);



                ui->table_rayon->setItem(row, 0, idRay);
                ui->table_rayon->setItem(row, 1, idEtag);
                ui->table_rayon->setItem(row, 2, capRay);



//                QPushButton *refuseButton = new QPushButton("Supprimer");
//                ui->table_rayon->setCellWidget(row, 3, refuseButton);

//                connect(refuseButton, &QPushButton::clicked, this, &etages_rayons::refuseEtager);

                ++row;
            }
        }else{
            QMessageBox::information(this,"failed","query is false");
        }
    }else{
        QMessageBox::information(this, "Connection",db.lastError().text());
    }
}

void etages_rayons::refuseEtager()
{
    QPushButton* deleteButton = qobject_cast<QPushButton*>(sender());
    int row = ui->tabe_etagers->indexAt(deleteButton->pos()).row();
    QTableWidgetItem* idItem = ui->tabe_etagers->item(row, 0);
    QString etagerID = idItem->text();

    QSqlQuery updateLivreQuery;
    QSqlQuery selectRayonQuery;
    selectRayonQuery.prepare("select r.ID_RAYON from livre l INNER join rayon r on l.ID_RAYON = r.ID_RAYON where r.ID_ETAGER = :idetager");
    selectRayonQuery.bindValue(":idetager", etagerID);
    if (selectRayonQuery.exec()) {
        while (selectRayonQuery.next()) {
            QString rayonID = selectRayonQuery.value("ID_RAYON").toString();

            updateLivreQuery.prepare("UPDATE livre SET ID_RAYON = NULL WHERE ID_RAYON = :rayonId");
            updateLivreQuery.bindValue(":rayonId", rayonID);
            if (!updateLivreQuery.exec()) {
                QMessageBox::critical(this, "Error", "Failed to update 'livre' table.");
            }
        }
    } else {
    }
    QSqlQuery deleteRayonQuery;
    deleteRayonQuery.prepare("DELETE FROM rayon WHERE ID_ETAGER = :etagerId");
    deleteRayonQuery.bindValue(":etagerId", etagerID);
    if (!deleteRayonQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to delete associated rows in the 'rayon' table.");
    }

    QSqlQuery deleteEtagerQuery;
    deleteEtagerQuery.prepare("DELETE FROM etagere WHERE ID_ETAGERE = :etagerId");
    deleteEtagerQuery.bindValue(":etagerId", etagerID);
    if (!deleteEtagerQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to delete the 'etager' from the database.");
    }

    QMessageBox::information(this, "Success", "etager removed successfully.");
    populateEtagersTable();
    populateRayonsTable();
}

void etages_rayons::on_bt_ajouter_clicked()
{
    QString nbrRayon = ui->tb_nbrRayon->text();
    QString capRayon = ui->tb_capRayon->text();

    QSqlQuery maxIDEtager("select MAX(ID_ETAGERE) as 'ID' from etagere");
    maxIDEtager.exec();
    maxIDEtager.next();
    QString IDEtager = maxIDEtager.value("ID").toString();
    int IDValueEtager = IDEtager.toInt() + 1;

    QSqlQuery query;
    query.prepare("insert into etagere values(:id,:nbrrayon)");
    query.bindValue(":id",IDValueEtager);
    query.bindValue(":nbrrayon",nbrRayon);
    if(query.exec()){
        QMessageBox::information(this, "Success", "etagers est ajoute.");
        populateEtagersTable();
        populateEtagersRayonsCombos();
    }else{
        QMessageBox::information(this, "Error", query.lastError().text());
    }
    QSqlQuery query2;

    QSqlQuery maxIDRayon("select MAX(ID_RAYON) as 'ID' from rayon");
    maxIDRayon.exec();
    maxIDRayon.next();
    QString IDRayon = maxIDRayon.value("ID").toString();
    int IDValueRayon = IDRayon.toInt() + 1;
    query2.prepare("insert into rayon values(:idray,:ideta,:caprayon)");
    for(int i =0; i<nbrRayon.toInt();i++){
        query2.bindValue(":idray",IDValueRayon);
        query2.bindValue(":ideta",IDValueEtager);
        query2.bindValue(":caprayon",capRayon);
        query2.exec();
        IDValueRayon++;
    }
    populateRayonsTable();
}


void etages_rayons::on_cb_etager_currentIndexChanged(int index)
{
    QVariant selectedOption = ui->cb_etager->itemData(index);
    int selectedIdEtager = selectedOption.toInt();

    for (int row = 0; row < ui->table_rayon->rowCount(); ++row) {
        QTableWidgetItem* item = ui->table_rayon->item(row, 1);

        if (item->text().toInt() == selectedIdEtager) {
            ui->table_rayon->setRowHidden(row, false);
        }else {
            ui->table_rayon->setRowHidden(row, true);
        }
    }
}


void etages_rayons::on_cb_rayon_currentIndexChanged(int index)
{
//    QVariant selectedOption = ui->cb_rayon->itemData(index);
//    int selectedIdEtager = selectedOption.toInt();

//    for (int row = 0; row < ui->table_rayon->rowCount(); ++row) {
//        QTableWidgetItem* item = ui->table_rayon->item(row, 0); // Assuming the idEtager column is at index 1

//        if (item->text().toInt() == selectedIdEtager) {
//            ui->table_rayon->setRowHidden(row, false);
//        } else {
//            ui->table_rayon->setRowHidden(row, true);
//        }
//    }
}


void etages_rayons::on_bt_reload_clicked()
{
    ui->table_rayon->clearContents();
    ui->table_rayon->setRowCount(0);
    populateRayonsTable();
}

