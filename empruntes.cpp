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
void enmpruntes::populateEmprunteTable(){
    QSqlQuery query("SELECT e.ID_EMPRUNTE,p.ID_PERSONNE,p.NOM,p.PRENOM,r.ID_LIVRE,l.TITRE,DATE(e.DATEEMPRUNTE) as 'DATE EMPRUNTE',DATE(e.DATE_RETURN_EMPRUNTE) as 'DATE END EMPRUNTE' FROM empruntlivre e INNER JOIN reserverlivre r on e.ID_RESERVATION = r.ID_RESERVATION inner join personne p on r.ID_PERSONNE = p.ID_PERSONNE INNER join livre l on r.ID_LIVRE = l.ID_LIVRE");

    int row = 0;
    if(db.open()){
        if(query.exec()){
            ui->table_empruntes->setRowCount(query.size());
            ui->table_empruntes->setColumnCount(8);
            while (query.next()) {
                QString idEmrpunte = query.value("ID_EMPRUNTE").toString();
                QString idPersonne = query.value("ID_PERSONNE").toString();
                QString nomPersonne = query.value("NOM").toString();
                QString prenomPersonne = query.value("PRENOM").toString();
                QString idLivre = query.value("ID_LIVRE").toString();
                QString titreLivre = query.value("TITRE").toString();
                QString dateEmp = query.value("DATE EMPRUNTE").toString();
                QString dateEndEmp = query.value("DATE END EMPRUNTE").toString();



                QTableWidgetItem *idemp = new QTableWidgetItem(idEmrpunte);
                QTableWidgetItem *idperso = new QTableWidgetItem(idPersonne);
                QTableWidgetItem *nomperso = new QTableWidgetItem(nomPersonne);
                QTableWidgetItem *prenomperso = new QTableWidgetItem(prenomPersonne);
                QTableWidgetItem *idlivre = new QTableWidgetItem(idLivre);
                QTableWidgetItem *titrelivre = new QTableWidgetItem(titreLivre);
                QTableWidgetItem *dateemp = new QTableWidgetItem(dateEmp);
                QTableWidgetItem *dateendemp = new QTableWidgetItem(dateEndEmp);

                // Create other QTableWidgetItem objects for other reservation details

                ui->table_empruntes->setItem(row, 0, idemp);
                ui->table_empruntes->setItem(row, 1, idperso);
                ui->table_empruntes->setItem(row, 2, nomperso);
                ui->table_empruntes->setItem(row, 3, prenomperso);
                ui->table_empruntes->setItem(row, 4, idlivre);
                ui->table_empruntes->setItem(row, 5, titrelivre);
                ui->table_empruntes->setItem(row, 6, dateemp);
                ui->table_empruntes->setItem(row, 7, dateendemp);

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
    populateEmprunteTable();
}


void enmpruntes::on_bt_recherche_clicked()
{
//    QString searchOption = ui->comboBox->currentText();
    QString keyword = ui->tb_search->text();


    for (int row = 0; row < ui->table_empruntes->rowCount(); ++row)
    {
        QTableWidgetItem *item = ui->table_empruntes->item(row, ui->comboBox->currentIndex());
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

