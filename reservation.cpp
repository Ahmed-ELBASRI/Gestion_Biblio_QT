#include "reservation.h"
#include "ui_reservation.h"

reservation::reservation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reservation)
{
    ui->setupUi(this);


}
void reservation::showEvent(QShowEvent *event){
    QDialog::showEvent(event);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("gestion_biblio");
    db.open();
    populateReservationTable();
}
void reservation::populateReservationTable(){
        QSqlQuery query("SELECT r.ID_RESERVATION,p.ID_PERSONNE,p.NOM,p.PRENOM,r.ID_LIVRE,l.TITRE,DATE(r.DATERESERVATION) as 'DATE RESERVATION' FROM reserverlivre r inner join personne p on r.ID_PERSONNE = p.ID_PERSONNE INNER join livre l on r.ID_LIVRE = l.ID_LIVRE where r.archive = 0 and r.ETAT like 'pending'");

    int row = 0;
    if(db.open()){
        if(query.exec()){
            ui->table_reservation->setRowCount(query.size());
            ui->table_reservation->setColumnCount(9);
            while (query.next()) {
                QString idReservation = query.value("ID_RESERVATION").toString();
                QString idPersonne = query.value("ID_PERSONNE").toString();
                QString nomPersonne = query.value("NOM").toString();
                QString prenomPersonne = query.value("PRENOM").toString();
                QString idLivre = query.value("ID_LIVRE").toString();
                QString titreLivre = query.value("TITRE").toString();
                QString dateRes = query.value("DATE RESERVATION").toString();


                QTableWidgetItem *idres = new QTableWidgetItem(idReservation);
                QTableWidgetItem *idperso = new QTableWidgetItem(idPersonne);
                QTableWidgetItem *nomperso = new QTableWidgetItem(nomPersonne);
                QTableWidgetItem *prenomperso = new QTableWidgetItem(prenomPersonne);
                QTableWidgetItem *idlivre = new QTableWidgetItem(idLivre);
                QTableWidgetItem *titrelivre = new QTableWidgetItem(titreLivre);
                QTableWidgetItem *dateres = new QTableWidgetItem(dateRes);


                ui->table_reservation->setItem(row, 0, idres);
                ui->table_reservation->setItem(row, 1, idperso);
                ui->table_reservation->setItem(row, 2, nomperso);
                ui->table_reservation->setItem(row, 3, prenomperso);
                ui->table_reservation->setItem(row, 4, idlivre);
                ui->table_reservation->setItem(row, 5, titrelivre);
                ui->table_reservation->setItem(row, 6, dateres);



                QPushButton *confirmButton = new QPushButton("Confirmer");
                QPushButton *refuseButton = new QPushButton("Refuser");
                ui->table_reservation->setCellWidget(row, 7, confirmButton);
                ui->table_reservation->setCellWidget(row, 8, refuseButton);

                connect(confirmButton, &QPushButton::clicked, this, &reservation::confirmReservation);
                connect(refuseButton, &QPushButton::clicked, this, &reservation::refuseReservation);

                ++row;
            }
        }else{
            QMessageBox::information(this,"failed","query is false");
        }
    }else{
        QMessageBox::information(this, "Connection",db.lastError().text());
    }
}
void reservation::confirmReservation()
{


    QPushButton *confirmButton = qobject_cast<QPushButton*>(sender());
    int row = ui->table_reservation->indexAt(confirmButton->pos()).row();
    QTableWidgetItem *idItem = ui->table_reservation->item(row, 0);
    if (idItem) {


            QString reservationId = idItem->text();
            QSqlQuery query;
            QSqlQuery query_;
            query.prepare("update reserverlivre set archive=1, ETAT = 'approved' where ID_RESERVATION =:reservationId");
            query.bindValue(":reservationId", reservationId);
            query_.prepare("INSERT INTO empruntlivre(ID_RESERVATION, DATEEMPRUNTE) VALUES (:reservationId, CURRENT_TIMESTAMP)");
            query_.bindValue(":reservationId", reservationId);
            bool q = query.exec();
            bool q2 = query_.exec();
            if (db.open()) {
                if(q == true){
                    QMessageBox::information(this, "Confirmation", "Reservation confirmed successfully.");
                if(q2 == true){
                        QMessageBox::information(this, "Confirmation", "Emprunte confirmed successfully.");
                        ui->table_reservation->clearContents();
                        ui->table_reservation->setRowCount(0);
                        populateReservationTable();


                    }
                }

            } else {
            QMessageBox::warning(this, "Error", "Database connection failed.");
            }
    }
}

void reservation::refuseReservation()
{
    QPushButton *refuseButton = qobject_cast<QPushButton*>(sender());
    int row = ui->table_reservation->indexAt(refuseButton->pos()).row();
    QTableWidgetItem *idItem = ui->table_reservation->item(row, 0);

    if (idItem) {
            QString reservationId = idItem->text();

            QSqlQuery query;
            query.prepare("update reserverlivre set archive=1, ETAT = 'refused' where ID_RESERVATION =:reservationId");
            query.bindValue(":reservationId", reservationId);
            bool q = query.exec();
            if(db.open()){
                if (q == true) {
                    QMessageBox::information(this, "Confirmation", "Reservation refused successfully.");
                    ui->table_reservation->clearContents();
                    ui->table_reservation->setRowCount(0);
                    populateReservationTable();

                } else {
                        QMessageBox::information(this, "Error", query.lastError().text());

                }
            } else {
                QMessageBox::warning(this, "Error", "Database connection failed.");
            }


    }
}

reservation::~reservation()
{
    delete ui;
}





void reservation::on_bt_recherche_clicked()
{
    int searchOption = ui->comboBox->currentIndex();
    QString keyword = ui->tb_search->text();


            for (int row = 0; row < ui->table_reservation->rowCount(); ++row)
            {
                QTableWidgetItem *item = ui->table_reservation->item(row, searchOption);
                if (item && item->text().contains(keyword, Qt::CaseInsensitive))
                {
                    ui->table_reservation->setRowHidden(row, false);
                }
                else
                {
                    ui->table_reservation->setRowHidden(row, true);
                }
            }
}



void reservation::on_bt_reload_clicked()
{
    ui->table_reservation->clearContents();
    ui->table_reservation->setRowCount(0);
    ui->tb_search->clear();
    populateReservationTable();

}

