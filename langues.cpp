#include "langues.h"
#include "ui_langues.h"

Langues::Langues(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Langues)
{
    ui->setupUi(this);
}

Langues::~Langues()
{
    delete ui;
}
void Langues::showEvent(QShowEvent *event){
    QDialog::showEvent(event);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("gestion_biblio");
    db.open();
    populateLanguesTable();
    ui->bt_ajouter->setEnabled(false);
}
void Langues::populateLanguesTable(){
    QSqlQuery query("SELECT * FROM lange");

    int row = 0;
    if(db.open()){
        if(query.exec()){
            ui->table_langue->setRowCount(query.size());
            ui->table_langue->setColumnCount(4);
            while (query.next()) {
                QString idLangue = query.value("ID_LANGUE").toString();
                QString libLangue = query.value("LIBELLE_LANGUE").toString();


                QTableWidgetItem *idLang = new QTableWidgetItem(idLangue);
                QTableWidgetItem *libLang = new QTableWidgetItem(libLangue);



                ui->table_langue->setItem(row, 0, idLang);
                ui->table_langue->setItem(row, 1, libLang);

                QPushButton *refuseButton = new QPushButton("Supprimer");
                QPushButton *modifierButton = new QPushButton("Modifier");
                ui->table_langue->setCellWidget(row, 2, refuseButton);
                ui->table_langue->setCellWidget(row, 3, modifierButton);

                connect(refuseButton, &QPushButton::clicked, this, &Langues::refuseLangues);
                connect(modifierButton, &QPushButton::clicked, this, &Langues::modifierLangue);

                ++row;
            }
        }else{
            QMessageBox::information(this,"failed","query is false");
        }
    }else{
        QMessageBox::information(this, "Connection",db.lastError().text());
    }
}
void Langues::refuseLangues(){
    QPushButton* deleteButton = qobject_cast<QPushButton*>(sender());
    int row = ui->table_langue->indexAt(deleteButton->pos()).row();
    QTableWidgetItem* idItem = ui->table_langue->item(row, 0);
    QString idLangue = idItem->text();

    QSqlQuery deleteRedigerQuery;
    deleteRedigerQuery.prepare("DELETE FROM traduite WHERE ID_LANGUE = :idlangue");
    deleteRedigerQuery.bindValue(":idlangue", idLangue);
    if (!deleteRedigerQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to delete associated rows in the 'rediger' table.");
    }

    QSqlQuery deleteLangueQuery;
    deleteLangueQuery.prepare("DELETE FROM lange WHERE ID_LANGUE = :idlangue");
    deleteLangueQuery.bindValue(":idlangue", idLangue);
    if (!deleteLangueQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to delete the 'langue' from the database.");
    }
    QMessageBox::information(this, "Success", "langue removed successfully");
    populateLanguesTable();
}
void Langues::modifierLangue(){
    int row = ui->table_langue->currentRow();
    if (row >= 0) {
        QTableWidgetItem* idItem = ui->table_langue->item(row, 0);
        QString idLangue = idItem->text();

        QTableWidgetItem* nameItem = ui->table_langue->item(row, 1);
        QString libelleLangue = nameItem->text();


        ui->tb_langue->setText(libelleLangue);

        selectedLangueId = idLangue.toInt();
    }
}

void Langues::on_bt_ajouter_clicked()
{
    QString libelleLangue = ui->tb_langue->text();


    QSqlQuery maxID("select MAX(ID_LANGUE) as 'ID' from lange");
    maxID.exec();
    maxID.next();
    QString ID = maxID.value("ID").toString();
    int IDValue = ID.toInt() + 1;
    QSqlQuery query;
    query.prepare("insert into lange values(:id,:libellelangue)");
    query.bindValue(":id",IDValue);
    query.bindValue(":libellelangue",libelleLangue);
    if(query.exec()){
        QMessageBox::information(this, "Success", "Langue est ajoute.");

    }else{
        QMessageBox::information(this, "Error", query.lastError().text());
    }
    ui->tb_langue->clear();
    populateLanguesTable();
}


void Langues::on_ck_modifer_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked){
        ui->bt_ajouter->setEnabled(true);
        ui->bt_modifier->setEnabled(false);
        ui->table_langue->setColumnHidden(3,true);
        ui->tb_langue->clear();
    }else{
        ui->bt_ajouter->setEnabled(false);
        ui->bt_modifier->setEnabled(true);
        ui->table_langue->setColumnHidden(3,false);

    }
}


void Langues::on_bt_modifier_clicked()
{
    QString langue = ui->tb_langue->text();


    QSqlQuery query;
    query.prepare("update lange set LIBELLE_LANGUE =:libellelangue where ID_LANGUE=:id");
    query.bindValue(":id",selectedLangueId);
    query.bindValue(":libellelangue",langue);
    if(query.exec()){
        QMessageBox::information(this, "Success", "Langue est modifier.");

    }else{
        QMessageBox::information(this, "Error", query.lastError().text());
    }
    ui->tb_langue->clear();
    populateLanguesTable();
}

