#include "touslivres.h"
#include "ui_touslivres.h"

tousLivres::tousLivres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tousLivres)
{
    ui->setupUi(this);
}

tousLivres::~tousLivres()
{
    delete ui;
}
void tousLivres::showEvent(QShowEvent *event){
    QDialog::showEvent(event);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("gestion_biblio");
    db.open();
    populateReservationTable();
}
void tousLivres::populateReservationTable(){
    QSqlQuery query("SELECT L.ID_LIVRE,L.ID_RAYON,L.TITRE,L.DESCRIPTION,L.ISBN,L.ANNEEPUBLICATION,L.NOMBREPAGE,L.PRIX,LA.LIBELLE_LANGUE,C.LIBELLE_CATEGORIE,E.ID_ETAGERE ,GROUP_CONCAT(A.NOM_AUTEUR SEPARATOR ',') AS NOM_AUTEUR FROM livre L INNER JOIN rediger R ON L.ID_LIVRE = R.ID_LIVRE INNER JOIN auteur A ON R.ID_AUTEUR = A.ID_AUTEUR INNER JOIN lange LA ON L.ID_LANGUE = LA.ID_LANGUE INNER JOIN categorie C ON L.ID_CATEGORIE = C.ID_CATEGORIE INNER JOIN rayon RR ON L.ID_RAYON = RR.ID_RAYON INNER JOIN etagere E ON RR.ID_ETAGER = E.ID_ETAGERE GROUP BY L.ID_LIVRE;");

    int row = 0;
    if(db.open()){
        if(query.exec()){
            ui->table_livre->setRowCount(query.size());
            ui->table_livre->setColumnCount(12);
            while (query.next()) {
                QString idLivre = query.value("ID_LIVRE").toString();
                QString idRayon = query.value("ID_RAYON").toString();
                QString titre = query.value("TITRE").toString();
                QString description = query.value("DESCRIPTION").toString();
                QString isbn = query.value("ISBN").toString();
                QString annePublication = query.value("ANNEEPUBLICATION").toString();
                QString nombrePage = query.value("NOMBREPAGE").toString();
                QString prix = query.value("PRIX").toString();
                QString libelleLangue = query.value("LIBELLE_LANGUE").toString();
                QString libelleCategorie = query.value("LIBELLE_CATEGORIE").toString();
                QString idEtager = query.value("ID_ETAGERE").toString();
                QString nomAuteur = query.value("NOM_AUTEUR").toString();

                QTableWidgetItem *idLiv = new QTableWidgetItem(idLivre);
                QTableWidgetItem *idRay = new QTableWidgetItem(idRayon);
                QTableWidgetItem *tit = new QTableWidgetItem(titre);
                QTableWidgetItem *descr = new QTableWidgetItem(description);
                QTableWidgetItem *isb = new QTableWidgetItem(isbn);
                QTableWidgetItem *annePub = new QTableWidgetItem(annePublication);
                QTableWidgetItem *nbrPage = new QTableWidgetItem(nombrePage);
                QTableWidgetItem *pri = new QTableWidgetItem(prix);
                QTableWidgetItem *libelleLang = new QTableWidgetItem(libelleLangue);
                QTableWidgetItem *libelleCateg = new QTableWidgetItem(libelleCategorie);
                QTableWidgetItem *idEtag = new QTableWidgetItem(idEtager);
                QTableWidgetItem *nomAut = new QTableWidgetItem(nomAuteur);


                ui->table_livre->setItem(row, 0, idLiv);
                ui->table_livre->setItem(row, 1, tit);
                ui->table_livre->setItem(row, 2, descr);
                ui->table_livre->setItem(row, 3, libelleLang);
                ui->table_livre->setItem(row, 4, annePub);
                ui->table_livre->setItem(row, 5, libelleCateg);
                ui->table_livre->setItem(row, 6, nomAut);
                ui->table_livre->setItem(row, 7, pri);
                ui->table_livre->setItem(row, 8, idRay);
                ui->table_livre->setItem(row, 9, idEtag);
                ui->table_livre->setItem(row, 10, nbrPage);
                ui->table_livre->setItem(row, 11, isb);
                ++row;

            }
        }else{
            QMessageBox::information(this,"failed","query is false");
        }
    }else{
        QMessageBox::information(this, "Connection",db.lastError().text());
    }
}

void tousLivres::on_bt_reload_clicked()
{
    ui->table_livre->clearContents();
    ui->table_livre->setRowCount(0);
    ui->tb_search->clear();
    populateReservationTable();
}


void tousLivres::on_bt_recherche_clicked()
{
    int searchOption = ui->comboBox->currentIndex();
    QString keyword = ui->tb_search->text();


    for (int row = 0; row < ui->table_livre->rowCount(); ++row)
    {
        QTableWidgetItem *item = ui->table_livre->item(row, searchOption);
        if (item && item->text().contains(keyword, Qt::CaseInsensitive))
        {
            ui->table_livre->setRowHidden(row, false);
        }
        else
        {
            ui->table_livre->setRowHidden(row, true);
        }
    }
}

