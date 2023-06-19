#include "empruntes.h"
#include "ui_empruntes.h"

enmpruntes::enmpruntes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::enmpruntes)
{
    ui->setupUi(this);
}

enmpruntes::~enmpruntes()
{
    delete ui;
}
void enmpruntes::showEvent(QShowEvent *event){
    QDialog::showEvent(event);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("gestion_biblio");
    db.open();
    populateEmprunteTable();
}
void enmpruntes::confirmReservation()
{


    QPushButton *confirmButton = qobject_cast<QPushButton*>(sender());
    int row = ui->table_empruntes->indexAt(confirmButton->pos()).row();
    QTableWidgetItem *idItem = ui->table_empruntes->item(row, 0);
    if (idItem) {

        QString emprunteID = idItem->text();
        QSqlQuery query;
        query.prepare("update empruntlivre set DATE_RETURN=CURRENT_TIMESTAMP WHERE ID_EMPRUNTE = :emprundeID");
        query.bindValue(":emprundeID", emprunteID);
        bool q = query.exec();
        if (db.open()) {
            if(q == true){
                QMessageBox::information(this, "Confirmation", "emprunt returned successfully.");
                populateEmprunteTable();
            }

        } else {
            QMessageBox::warning(this, "Error", "Database connection failed.");
        }
    }
}
void enmpruntes::populateEmprunteTable(){
    QSqlQuery query("SELECT e.ID_EMPRUNTE,p.ID_PERSONNE,p.NOM,p.PRENOM,r.ID_LIVRE,l.TITRE,DATE(e.DATEEMPRUNTE) as 'DATE EMPRUNTE',DATE(e.DATE_RETURN) as 'DATE RETURN',DATE(e.DATE_RETURN_EMPRUNTE) as 'DATE END EMPRUNTE' FROM empruntlivre e INNER JOIN reserverlivre r on e.ID_RESERVATION = r.ID_RESERVATION inner join personne p on r.ID_PERSONNE = p.ID_PERSONNE INNER join livre l on r.ID_LIVRE = l.ID_LIVRE");

    int row = 0;
    if(db.open()){
        if(query.exec()){
            ui->table_empruntes->setRowCount(query.size());
            ui->table_empruntes->setColumnCount(10);
            while (query.next()) {
                QString idEmrpunte = query.value("ID_EMPRUNTE").toString();
                QString idPersonne = query.value("ID_PERSONNE").toString();
                QString nomPersonne = query.value("NOM").toString();
                QString prenomPersonne = query.value("PRENOM").toString();
                QString idLivre = query.value("ID_LIVRE").toString();
                QString titreLivre = query.value("TITRE").toString();
                QString dateEmp = query.value("DATE EMPRUNTE").toString();
                QString dateReturn = query.value("DATE RETURN").toString();
                QString dateEndEmp = query.value("DATE END EMPRUNTE").toString();



                QTableWidgetItem *idemp = new QTableWidgetItem(idEmrpunte);
                QTableWidgetItem *idperso = new QTableWidgetItem(idPersonne);
                QTableWidgetItem *nomperso = new QTableWidgetItem(nomPersonne);
                QTableWidgetItem *prenomperso = new QTableWidgetItem(prenomPersonne);
                QTableWidgetItem *idlivre = new QTableWidgetItem(idLivre);
                QTableWidgetItem *titrelivre = new QTableWidgetItem(titreLivre);
                QTableWidgetItem *dateemp = new QTableWidgetItem(dateEmp);
                QTableWidgetItem *dateRet = new QTableWidgetItem(dateReturn);
                QTableWidgetItem *dateendemp = new QTableWidgetItem(dateEndEmp);

                // Create other QTableWidgetItem objects for other reservation details

                ui->table_empruntes->setItem(row, 0, idemp);
                ui->table_empruntes->setItem(row, 1, idperso);
                ui->table_empruntes->setItem(row, 2, nomperso);
                ui->table_empruntes->setItem(row, 3, prenomperso);
                ui->table_empruntes->setItem(row, 4, idlivre);
                ui->table_empruntes->setItem(row, 5, titrelivre);
                ui->table_empruntes->setItem(row, 6, dateemp);
                ui->table_empruntes->setItem(row, 7, dateRet);
                ui->table_empruntes->setItem(row, 8, dateendemp);

                QPushButton *confirmButton = new QPushButton("Confirmer");
                ui->table_empruntes->setCellWidget(row, 9, confirmButton);
                if (!dateReturn.isNull()) {
                    confirmButton->setEnabled(false);
                }
                connect(confirmButton, &QPushButton::clicked, this, &enmpruntes::confirmReservation);
                ++row;
            }
        }else{
            QMessageBox::information(this,"failed","query is false");
        }
    }else{
        QMessageBox::information(this, "Connection", "connection failed");
    }
}
void enmpruntes::on_bt_reload_clicked()
{
    ui->table_empruntes->clearContents();
    ui->table_empruntes->setRowCount(0);
    ui->tb_search->clear();
    populateEmprunteTable();
}


void enmpruntes::on_bt_recherche_clicked()
{
    int searchOption = ui->comboBox->currentIndex();
    QString keyword = ui->tb_search->text();


    for (int row = 0; row < ui->table_empruntes->rowCount(); ++row)
    {
        QTableWidgetItem *item = ui->table_empruntes->item(row,searchOption);
        if (item && item->text().contains(keyword, Qt::CaseInsensitive))
        {
            ui->table_empruntes->setRowHidden(row, false);
        }
        else
        {
            ui->table_empruntes->setRowHidden(row, true);
        }
    }
}

