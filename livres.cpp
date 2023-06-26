#include "livres.h"
#include "ui_livres.h"

livres::livres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::livres)
{

    ui->setupUi(this);
    touslivre = new tousLivres(ui->groupBox);
    touslivre->hide();
}

livres::~livres()
{
    delete ui;
}
void livres::showEvent(QShowEvent *event){
    QDialog::showEvent(event);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("gestion_biblio");
    db.open();
    ui->cb_auteur->clear();
    ui->cb_categorie->clear();
    ui->cb_etagers->clear();
    ui->cb_rayon->clear();
    ui->cb_livre->clear();
    ui->cb_langue->clear();
    populateCombosLivre();
    ui->bt_ajouter->setEnabled(false);
}
void livres::clearFields(){
    ui->tb_description->clear();
    ui->tb_isbn->clear();
    ui->tb_pages->clear();
    ui->tb_prix->clear();
    ui->tb_titre->clear();
    ui->img_couv->clear();
    ui->img_couv_min->clear();
}
void livres::populateCombosLivre()
{
    QSqlQuery rayonQuery("select ID_ETAGERE from etagere");
    if(rayonQuery.exec()){
        while (rayonQuery.next()) {
            QString rayon = rayonQuery.value("ID_ETAGERE").toString();
            ui->cb_etagers->addItem(rayon);
        }
    }
    QSqlQuery livreQuery("select l.ID_LIVRE, l.TITRE from livre l ");
    if(livreQuery.exec()){
        while (livreQuery.next()) {
            QString livre = livreQuery.value("TITRE").toString();
            ui->cb_livre->addItem(livre);
            int idLivre = livreQuery.value("ID_LIVRE").toInt();
            ui->cb_livre->setItemData(ui->cb_livre->count() - 1, idLivre);
        }
    }
    QSqlQuery auteurQuery("select ID_AUTEUR ,NOM_AUTEUR from auteur");
    if(auteurQuery.exec()){
        while (auteurQuery.next()) {
            QString auteur = auteurQuery.value("NOM_AUTEUR").toString();
            ui->cb_auteur->addItem(auteur);
            int idAuteur = auteurQuery.value("ID_AUTEUR").toInt();
            ui->cb_auteur->setItemData(ui->cb_auteur->count() - 1, idAuteur);
        }
    }
    QSqlQuery categorieQuery("SELECT ID_CATEGORIE ,LIBELLE_CATEGORIE FROM categorie ");

    if(categorieQuery.exec()){
        while (categorieQuery.next()) {
            QString categorie = categorieQuery.value("LIBELLE_CATEGORIE").toString();
            ui->cb_categorie->addItem(categorie);
            int idCategorie = categorieQuery.value("ID_CATEGORIE").toInt();
            ui->cb_categorie->setItemData(ui->cb_categorie->count() - 1, idCategorie);
        }
    }
    QSqlQuery langueQuery("SELECT ID_LANGUE,LIBELLE_LANGUE FROM lange ");

    if(langueQuery.exec()){
        while (langueQuery.next()) {
            QString langue = langueQuery.value("LIBELLE_LANGUE").toString();
            ui->cb_langue->addItem(langue);
            int idLangue = langueQuery.value("ID_LANGUE").toInt();
            ui->cb_langue->setItemData(ui->cb_langue->count() - 1, idLangue);
        }
    }

}

void livres::on_bt_upload_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select Cover Image", "", "Image Files (*.png *.jpg *.jpeg)");
    if (!filePath.isEmpty()) {
        ui->img_couv->setText(filePath);
    }
}


void livres::on_bt_upload_min_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select Cover Image", "", "Image Files (*.png *.jpg *.jpeg)");
    if (!filePath.isEmpty()) {
        ui->img_couv_min->setText(filePath);
    }
}


void livres::on_cb_etagers_currentIndexChanged()
{
    QString selectedEtager = ui->cb_etagers->currentText();
    QSqlQuery query;
    query.prepare("SELECT ID_RAYON FROM rayon WHERE ID_ETAGER = :idetager");
    query.bindValue(":idetager", selectedEtager);
    if (query.exec()) {
        ui->cb_rayon->clear();
        while (query.next()) {
            QString rayon = query.value("ID_RAYON").toString();
            ui->cb_rayon->addItem(rayon);
        }
    } else {
        QMessageBox::information(this, "Error", "Failed to retrieve rayon data.");
    }
}


void livres::on_bt_ajouter_clicked()
{
    QString titre = ui->tb_titre->text();
    QString pages = ui->tb_pages->text();
    QString prix = ui->tb_prix->text();
    QString isbn = ui->tb_isbn->text();
    QString description = ui->tb_description->toPlainText();
    QString rayon = ui->cb_rayon->currentText();
    QString couverturePath = ui->img_couv->text();
    QString destinationDirectory = "C:/xampp/htdocs/GestionBiblio/images/book_cover";
    QString fileName = QFileInfo(couverturePath).fileName();
    QString destinationPath = QDir(destinationDirectory).filePath(fileName);
    QFile::copy(couverturePath, destinationPath);
    QString subPath = destinationPath.mid(destinationPath.indexOf("images"));
    QString couvertureMinPath = ui->img_couv_min->text();
    QString destinationDirectoryMin = "C:/xampp/htdocs/GestionBiblio/images/book_cover/wishlist_image";
    QString fileNameMin = QFileInfo(couvertureMinPath).fileName();
    QString destinationPathMin = QDir(destinationDirectoryMin).filePath(fileNameMin);
    QFile::copy(couvertureMinPath, destinationPathMin);
    QString subPathMin = destinationPathMin.mid(destinationPathMin.indexOf("images"));
    int selectedLangueIndex = ui->cb_langue->currentIndex();
    int idLangue = ui->cb_langue->itemData(selectedLangueIndex).toInt();
    int selectedCategorieIndex = ui->cb_categorie->currentIndex();
    int idCategorie = ui->cb_categorie->itemData(selectedCategorieIndex).toInt();
    QDate selectedDate = ui->dt_annepub->date();
    QString formattedDate = selectedDate.toString("yyyy-MM-dd");
    QSqlQuery maxID("select MAX(ID_LIVRE) as 'ID' from livre");
    maxID.exec();
    maxID.next();
    QString ID = maxID.value("ID").toString();
    int IDValue = ID.toInt() + 1;
    QSqlQuery query;
    query.prepare("insert into livre values(:id,:rayon,:langue,:categorie,:titre,:isbn,:description,:annepub,:pages,:prix,:couv,:couv_min,0,0)");
    query.bindValue(":id",IDValue);
    query.bindValue(":rayon",rayon);
    query.bindValue(":langue",idLangue);
    query.bindValue(":categorie",idCategorie);
    query.bindValue(":titre",titre);
    query.bindValue(":isbn",isbn);
    query.bindValue(":description",description);
    query.bindValue(":annepub",formattedDate);
    query.bindValue(":pages",pages);
    query.bindValue(":prix",prix);
    query.bindValue(":couv",subPath);
    query.bindValue(":couv_min",subPathMin);
    if(query.exec()){
        QMessageBox::information(this, "Success", "Livre est ajoute.");

    }else{
        QMessageBox::information(this, "Error", query.lastError().text());
    }
    QSqlQuery rediger;
    int selectedAuthorIndex = ui->cb_auteur->currentIndex();
    int idAuteur = ui->cb_auteur->itemData(selectedAuthorIndex).toInt();
    rediger.prepare("insert into rediger values(:idlivre,:id_auteur)");

    rediger.bindValue(":idlivre",IDValue);
    rediger.bindValue(":id_auteur",idAuteur);
    if(rediger.exec()){
        QMessageBox::information(this, "Success", "rediger est ajoute.");
    }else{
        QMessageBox::information(this, "Error",rediger.lastError().text());
    }
}


void livres::on_check_modifer_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked){
        ui->bt_ajouter->setEnabled(true);
        ui->bt_supprimer->setEnabled(false);
        ui->cb_livre->setEnabled(false);
        ui->bt_modifier->setEnabled(false);
        clearFields();
        ui->lb_modifier->setText("disabled");
        ui->lb_ajouter->setText("");
        ui->lb_supprimver->setText("disabled");

    }else{
        ui->cb_livre->setEnabled(true);
        ui->bt_modifier->setEnabled(true);
        ui->bt_ajouter->setEnabled(false);
        ui->bt_supprimer->setEnabled(true);
        ui->lb_modifier->setText("");
        ui->lb_ajouter->setText("disabled");
        ui->lb_supprimver->setText("");
        initialize();
    }


}
void livres::initialize()
{
    bool isEnabled = ui->check_modifer->isChecked();
    ui->cb_livre->setEnabled(isEnabled);
    ui->bt_modifier->setEnabled(isEnabled);
}


void livres::on_cb_livre_currentIndexChanged()
{
    int selectedIndex = ui->cb_livre->currentIndex();
    int idLivre = ui->cb_livre->itemData(selectedIndex).toInt();
    QSqlQuery query;
    query.prepare("SELECT l.*, a.*, e.ID_ETAGERE, c.LIBELLE_CATEGORIE, la.LIBELLE_LANGUE FROM livre l  INNER JOIN rediger r ON l.ID_LIVRE = r.ID_LIVRE  INNER JOIN auteur a ON r.ID_AUTEUR = a.ID_AUTEUR  LEFT JOIN rayon ra ON l.ID_RAYON = ra.ID_RAYON  LEFT JOIN etagere e ON ra.ID_ETAGER = e.ID_ETAGERE  INNER JOIN categorie c ON l.ID_CATEGORIE = c.ID_CATEGORIE  INNER JOIN lange la ON l.ID_LANGUE = la.ID_LANGUE WHERE l.ID_LIVRE = :idlivre GROUP BY l.ID_LIVRE");
    query.bindValue(":idlivre", idLivre);
    if (query.exec()) {
        if (query.next()) {
            clearFields();

            ui->tb_titre->setText(query.value("TITRE").toString());
            QString rayon = query.value("ID_ETAGERE").toString();
            for (int i = 0; i < ui->cb_etagers->count(); i++) {
                if (ui->cb_etagers->itemText(i) == rayon) {
                    ui->cb_etagers->setCurrentIndex(i);
                    break;
                }
            }

            int idLangue = query.value("ID_LANGUE").toInt();
            for (int i = 0; i < ui->cb_langue->count(); i++) {
                if (ui->cb_langue->itemData(i).toInt() == idLangue) {
                    ui->cb_langue->setCurrentIndex(i);
                    break;
                }
            }

            int idCategorie = query.value("ID_CATEGORIE").toInt();
            for (int i = 0; i < ui->cb_categorie->count(); i++) {
                if (ui->cb_categorie->itemData(i).toInt() == idCategorie) {
                    ui->cb_categorie->setCurrentIndex(i);
                    break;
                }
            }

            int idAuteur = query.value("ID_AUTEUR").toInt();
            for (int i = 0; i < ui->cb_auteur->count(); i++) {
                if (ui->cb_auteur->itemData(i).toInt() == idAuteur) {
                    ui->cb_auteur->setCurrentIndex(i);
                    break;
                }
            }

            ui->tb_isbn->setText(query.value("ISBN").toString());
            ui->tb_description->setText(query.value("DESCRIPTION").toString());
            ui->tb_titre->setText(query.value("TITRE").toString());
            QString dateString = query.value("DATEPUBLICATION").toString();
            QDate datePub = QDate::fromString(dateString, "yyyy-MM-dd");
            ui->dt_annepub->setDate(datePub);
            ui->tb_pages->setText(query.value("NOMBREPAGE").toString());
            ui->img_couv->setText(query.value("COUVERTURE").toString());
            ui->img_couv_min->setText(query.value("COUVERTURE_MIN").toString());
            ui->tb_prix->setText(query.value("PRIX").toString());
        }
    }
    else {
        QMessageBox::information(this, "Error", query.lastError().text());
    }
}


void livres::on_bt_modifier_clicked()
{
    QString titre = ui->tb_titre->text();
    QString pages = ui->tb_pages->text();
    QString prix = ui->tb_prix->text();
    QString isbn = ui->tb_isbn->text();
    QString description = ui->tb_description->toPlainText();
    QString rayon = ui->cb_rayon->currentText();
    QString couverturePath = ui->img_couv->text();
    QString destinationDirectory = "C:/xampp/htdocs/GestionBiblio/images/book_cover";
    QString fileName = QFileInfo(couverturePath).fileName();
    QString destinationPath = QDir(destinationDirectory).filePath(fileName);
    QFile::copy(couverturePath, destinationPath);
    QString subPath = destinationPath.mid(destinationPath.indexOf("images"));
    QString couvertureMinPath = ui->img_couv_min->text();
    QString destinationDirectoryMin = "C:/xampp/htdocs/GestionBiblio/images/book_cover/wishlist_image";
    QString fileNameMin = QFileInfo(couvertureMinPath).fileName();
    QString destinationPathMin = QDir(destinationDirectoryMin).filePath(fileNameMin);
    QFile::copy(couvertureMinPath, destinationPathMin);
    QString subPathMin = destinationPathMin.mid(destinationPathMin.indexOf("images"));
    int selectedLangueIndex = ui->cb_langue->currentIndex();
    int idLangue = ui->cb_langue->itemData(selectedLangueIndex).toInt();
    int selectedCategorieIndex = ui->cb_categorie->currentIndex();
    int idCategorie = ui->cb_categorie->itemData(selectedCategorieIndex).toInt();
    int selectedLivreIndex = ui->cb_livre->currentIndex();
    int idLivre = ui->cb_livre->itemData(selectedLivreIndex).toInt();
    QDate selectedDate = ui->dt_annepub->date();
    QString formattedDate = selectedDate.toString("yyyy-MM-dd");
//    QSqlQuery maxID("select MAX(ID_LIVRE) as 'ID' from livre");
//    maxID.exec();
//    maxID.next();
//    QString ID = maxID.value("ID").toString();
//    int IDValue = ID.toInt() + 1;
    QSqlQuery query;
    query.prepare("update livre set ID_RAYON=:RAYON, ID_LANGUE =:LANGUE, ID_CATEGORIE=:categorie,TITRE=:TITRE,ISBN=:ISBN,DESCRIPTION=:DESCRIPTION,ANNEEPUBLICATION=:ANNEEPUBLICATION,NOMBREPAGE=:NOMBREPAGE,PRIX=:PRIX,COUVERTURE=:COUVERTURE,COUVERTURE_MIN=:COUVERTURE_MIN,QUANTITEREEL=0,QUANTITESTOCK=0 where ID_LIVRE=:livre;");
//    query.bindValue(":id",IDValue);
    query.bindValue(":RAYON",rayon);
    query.bindValue(":LANGUE",idLangue);
    query.bindValue(":categorie",idCategorie);
    query.bindValue(":TITRE",titre);
    query.bindValue(":ISBN",isbn);
    query.bindValue(":DESCRIPTION",description);
    query.bindValue(":ANNEEPUBLICATION",formattedDate);
    query.bindValue(":NOMBREPAGE",pages);
    query.bindValue(":PRIX",prix);
    query.bindValue(":COUVERTURE",subPath);
    query.bindValue(":COUVERTURE_MIN",subPathMin);
    query.bindValue(":livre",idLivre);
    if(query.exec()){
        QMessageBox::information(this, "Success", "Livre est modifier.");

    }else{
        QMessageBox::information(this, "Error", query.lastError().text());
    }
    QSqlQuery rediger;
    int selectedAuthorIndex = ui->cb_auteur->currentIndex();
    int idAuteur = ui->cb_auteur->itemData(selectedAuthorIndex).toInt();
    rediger.prepare("UPDATE rediger SET ID_AUTEUR=:AUTEUR where ID_LIVRE=:idlivre;");
    rediger.bindValue(":idlivre",idLivre);
    rediger.bindValue(":AUTEUR",idAuteur);
    if(rediger.exec()){
        QMessageBox::information(this, "Success", "rediger est modifier.");
    }else{
        QMessageBox::information(this, "Error",rediger.lastError().text());
    }

}


void livres::on_bt_supprimer_clicked()
{
    int selectedIndex = ui->cb_livre->currentIndex();
    int idLivre = ui->cb_livre->itemData(selectedIndex).toInt();

    ui->cb_livre->removeItem(selectedIndex);

    QSqlQuery deleteRedigerQuery;
    deleteRedigerQuery.prepare("DELETE FROM rediger WHERE ID_LIVRE = :idlivre");
    deleteRedigerQuery.bindValue(":idlivre", idLivre);
    if (deleteRedigerQuery.exec()) {
        QMessageBox::information(this, "Success", "Livre supprimer dans rediger");
    }
    else{
        QMessageBox::information(this, "Error", deleteRedigerQuery.lastError().text());
    }
    QSqlQuery deleteLivreQuery;
    deleteLivreQuery.prepare("DELETE FROM livre WHERE ID_LIVRE = :idlivre");
    deleteLivreQuery.bindValue(":idlivre", idLivre);
    if (deleteLivreQuery.exec()) {
        QMessageBox::information(this, "Success", "Livre supprimé.");
    } else {
        QMessageBox::information(this, "Error", deleteLivreQuery.lastError().text());
    }
}


void livres::on_bt_afficher_clicked()
{
    if (!touslivre) {
        touslivre = new tousLivres(this);
        touslivre->hide();
    }
    touslivre->show();
}

