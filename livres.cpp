#include "livres.h"
#include "ui_livres.h"

livres::livres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::livres)
{
    ui->setupUi(this);
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
    populateCombosLivre();
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
    QString destinationDirectoryMin = "C:/xampp/htdocs/GestionBiblio/images/book_cover/book_cover_min";
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
        ui->tb_description->clear();
        ui->tb_isbn->clear();
        ui->tb_pages->clear();
        ui->tb_prix->clear();
        ui->tb_titre->clear();
        ui->img_couv->clear();
        ui->img_couv_min->clear();
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

