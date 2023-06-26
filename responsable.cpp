#include "responsable.h"
#include "ui_responsable.h"

responsable::responsable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::responsable)
{
    ui->setupUi(this);
}

responsable::~responsable()
{
    delete ui;
}
void responsable::showEvent(QShowEvent *event){
    QDialog::showEvent(event);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("gestion_biblio");
    db.open();
    populateResponsalbesTable();
    ui->bt_ajouter->setEnabled(false);
}
void responsable::populateResponsalbesTable(){
    QSqlQuery query("select * from personne where ID_statue=2 AND archive=0");

    int row = 0;
    if(db.open()){
        if(query.exec()){
            ui->table_responsable->setRowCount(query.size());
            ui->table_responsable->setColumnCount(10);
            while (query.next()) {
                QString idResponsable = query.value("ID_PERSONNE").toString();
                QString nomResponsable = query.value("NOM").toString();
                QString prenomResponsable = query.value("PRENOM").toString();
                QString emailResponsable = query.value("EMAIL").toString();
                QString telResponsable = query.value("NUMEROTEL").toString();
                QString cinResponsable = query.value("CIN").toString();
                QString naissanceResponsable = query.value("DATENAISSANCE").toString();
                QString ageResponsable = query.value("AGE").toString();


                QTableWidgetItem *idRes = new QTableWidgetItem(idResponsable);
                QTableWidgetItem *nomRes = new QTableWidgetItem(nomResponsable);
                QTableWidgetItem *prenomRes = new QTableWidgetItem(prenomResponsable);
                QTableWidgetItem *emailRes = new QTableWidgetItem(emailResponsable);
                QTableWidgetItem *telRes = new QTableWidgetItem(telResponsable);
                QTableWidgetItem *cinRes = new QTableWidgetItem(cinResponsable);
                QTableWidgetItem *naissanceRes = new QTableWidgetItem(naissanceResponsable);
                QTableWidgetItem *ageRes = new QTableWidgetItem(ageResponsable);



                ui->table_responsable->setItem(row, 0, idRes);
                ui->table_responsable->setItem(row, 1, nomRes);
                ui->table_responsable->setItem(row, 2, prenomRes);
                ui->table_responsable->setItem(row, 3, emailRes);
                ui->table_responsable->setItem(row, 4, telRes);
                ui->table_responsable->setItem(row, 5, cinRes);
                ui->table_responsable->setItem(row, 6, naissanceRes);
                ui->table_responsable->setItem(row, 7, ageRes);

                QPushButton *refuseButton = new QPushButton("Supprimer");
                QPushButton *modifierButton = new QPushButton("Modifier");
                ui->table_responsable->setCellWidget(row, 8, refuseButton);
                ui->table_responsable->setCellWidget(row, 9, modifierButton);

                connect(refuseButton, &QPushButton::clicked, this, &responsable::refuseResponsable);
                connect(modifierButton, &QPushButton::clicked, this, &responsable::modifierResponsable);

                ++row;
            }
        }else{
            QMessageBox::information(this,"failed","query is false");
        }
    }else{
        QMessageBox::information(this, "Connection",db.lastError().text());
    }
}
void responsable::refuseResponsable(){
    QPushButton* deleteButton = qobject_cast<QPushButton*>(sender());
    int row = ui->table_responsable->indexAt(deleteButton->pos()).row();
    QTableWidgetItem* idItem = ui->table_responsable->item(row, 0);
    QString idRes = idItem->text();

    QSqlQuery deleteEtudierQuery;
    deleteEtudierQuery.prepare("update personne set archive=1 where ID_PERSONNE=:personId");
    deleteEtudierQuery.bindValue(":personId", idRes);
    if (!deleteEtudierQuery.exec()) {
        QMessageBox::critical(this, "Error", deleteEtudierQuery.lastError().text());
    }
    QMessageBox::information(this, "Success", "Responsable removed successfully");
    populateResponsalbesTable();
}
void responsable::modifierResponsable(){
    int row = ui->table_responsable->currentRow();
    if (row >= 0) {
        QTableWidgetItem* idResponsable = ui->table_responsable->item(row, 0);
        QString idRes = idResponsable->text();

        QTableWidgetItem* nomResponsable = ui->table_responsable->item(row, 1);
        QString nomRes = nomResponsable->text();

        QTableWidgetItem* prenomResponsable = ui->table_responsable->item(row, 2);
        QString prenomRes = prenomResponsable->text();

        QTableWidgetItem* emailResponsable = ui->table_responsable->item(row, 3);
        QString emailRes = emailResponsable->text();

        QTableWidgetItem* telResponsable = ui->table_responsable->item(row, 4);
        QString telRes = telResponsable->text();

        QTableWidgetItem* cinResponsable = ui->table_responsable->item(row, 5);
        QString cinRes = cinResponsable->text();

        QTableWidgetItem* naissanceResponsable = ui->table_responsable->item(row, 6);
        QString naissanceRes = naissanceResponsable->text();
        QDate birthdayDate = QDate::fromString(naissanceRes, "yyyy-MM-dd");

        ui->tb_nom->setText(nomRes);
        ui->tb_prenom->setText(prenomRes);
        ui->tb_email->setText(emailRes);
        ui->tb_telephone->setText(telRes);
        ui->tb_cin->setText(cinRes);
        ui->dt_naissance->setDate(birthdayDate);

        selectedResponsableId = idRes.toInt();
    }
}

void responsable::on_bt_ajouter_clicked()
{
    QString nomResponsable = ui->tb_nom->text();
    QString prenomResponsable = ui->tb_prenom->text();
    QString emailResponsable = ui->tb_email->text();
    QString telResponsable = ui->tb_telephone->text();

    QString cinResponsable = ui->tb_cin->text();
    QString passwordResponsable = ui->tb_password->text();
    QByteArray passwordData = passwordResponsable.toUtf8();
    QByteArray passwordHash = QCryptographicHash::hash(passwordData, QCryptographicHash::Md5);
    QString pwd = QString(passwordHash.toHex());

    QDate selectedDate = ui->dt_naissance->date();
    QString formattedDate = selectedDate.toString("yyyy-MM-dd");
    QDate currentDate = QDate::currentDate();
    int age = currentDate.year() - selectedDate.year();

    QSqlQuery maxID("select MAX(ID_PERSONNE) as 'ID' from personne");
    maxID.exec();
    maxID.next();
    QString ID = maxID.value("ID").toString();
    int IDValue = ID.toInt() + 1;

    QSqlQuery query;
    query.prepare("insert into personne values(:id,2,:nom,:prenom,:email,:password,:numerotel,:cin,:datenaissance,:age,0,0)");
    query.bindValue(":id",IDValue);
    query.bindValue(":prenom",prenomResponsable);
    query.bindValue(":nom",nomResponsable);
    query.bindValue(":email",emailResponsable);
    query.bindValue(":password",pwd);
    query.bindValue(":numerotel",telResponsable);
    query.bindValue(":cin",cinResponsable);
    query.bindValue(":datenaissance",formattedDate);
    query.bindValue(":age",age);
    if(query.exec()){
        QMessageBox::information(this, "Success", "Responsable est ajoute.");

    }else{
        QMessageBox::information(this, "Error", query.lastError().text());
    }
    ui->tb_cin->clear();
    ui->tb_email->clear();
    ui->tb_nom->clear();
    ui->tb_prenom->clear();
    ui->tb_password->clear();
    ui->tb_telephone->clear();
    populateResponsalbesTable();
}


void responsable::on_ck_modifer_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked){
        ui->bt_ajouter->setEnabled(true);
        ui->bt_modifier->setEnabled(false);
        ui->table_responsable->setColumnHidden(8,true);
        ui->tb_cin->clear();
        ui->tb_email->clear();
        ui->tb_nom->clear();
        ui->tb_prenom->clear();
        ui->tb_password->clear();
        ui->tb_telephone->clear();
    }else{
        ui->bt_ajouter->setEnabled(false);
        ui->bt_modifier->setEnabled(true);
        ui->table_responsable->setColumnHidden(8,false);
    }
}


void responsable::on_bt_modifier_clicked()
{
    QString nomResponsable = ui->tb_nom->text();
    QString prenomResponsable = ui->tb_prenom->text();
    QString emailResponsable = ui->tb_email->text();
    QString telResponsable = ui->tb_telephone->text();

    QString cinResponsable = ui->tb_cin->text();
    QString passwordResponsable = ui->tb_password->text();
    QByteArray passwordData = passwordResponsable.toUtf8();
    QByteArray passwordHash = QCryptographicHash::hash(passwordData, QCryptographicHash::Md5);
    QString pwd = QString(passwordHash.toHex());

    QDate selectedDate = ui->dt_naissance->date();
    QString dateNaissance = ui->dt_naissance->date().toString("yyyy-MM-dd");
    QDate currentDate = QDate::currentDate();
    int age = currentDate.year() - selectedDate.year();


    QSqlQuery query;
    query.prepare("update personne set NOM=:nom,PRENOM=:prenom,EMAIL=:email,PASSWORD=:password,NUMEROTEL=:numerotel,CIN=:cin,DATENAISSANCE=:datenaissance,AGE=:age WHERE ID_PERSONNE=:id");
    query.bindValue(":id",selectedResponsableId);
    query.bindValue(":nom",nomResponsable);
    query.bindValue(":prenom",prenomResponsable);
    query.bindValue(":email",emailResponsable);
    query.bindValue(":password",pwd);
    query.bindValue(":numerotel",telResponsable);
    query.bindValue(":cin",cinResponsable);
    query.bindValue(":datenaissance",dateNaissance);
    query.bindValue(":age",age);
    if(query.exec()){
        QMessageBox::information(this, "Success", "Responsable est modifier.");

    }else{
        QMessageBox::information(this, "Error", query.lastError().text());
    }
    ui->tb_cin->clear();
    ui->tb_email->clear();
    ui->tb_nom->clear();
    ui->tb_prenom->clear();
    ui->tb_password->clear();
    ui->tb_telephone->clear();
    populateResponsalbesTable();
}

