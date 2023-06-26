
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCryptographicHash>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tb_email->setPlaceholderText("Enter votre email");
    ui->tb_password->setPlaceholderText("Enter votre password");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bt_login_clicked()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("gestion_biblio");
    if(db.open()){
        QString email = ui->tb_email->text();
        QString password = ui->tb_password->text();

        QByteArray passwordData = password.toUtf8();
        QByteArray passwordHash = QCryptographicHash::hash(passwordData, QCryptographicHash::Md5);
        QString pwd = QString(passwordHash.toHex());

        QSqlQuery query;
        query.prepare("select p.*, s.* from personne p inner join statut s on p.ID_statue=s.ID where EMAIL like :email and PASSWORD like :password");
        query.bindValue(":email",email);
        query.bindValue(":password",pwd);
        if(query.exec()){
//            QMessageBox::information(this,"success","query is true");
            while (query.next()) {
                QString email_DB = query.value("EMAIL").toString();
                QString pwd_DB = query.value("PASSWORD").toString();
                QString status = query.value("LIBELLE").toString();

                if(email_DB == email && pwd_DB == pwd){
                    if (status.compare("rsb", Qt::CaseInsensitive) == 0) {
                        this->close();
                        HomeResponsable hr;
                        hr.setModal(true);
                        hr.exec();
                        break;
                    } else if (status.compare("admin", Qt::CaseInsensitive) == 0) {
                        this->close();
                        home h;
                        h.setModal(true);
                        h.exec();
                        break;
                    }

                }else{
                   QMessageBox::information(this,"login failed","email or password is not correct");
                    ui->tb_email->clear();
                    ui->tb_password->clear();
                    break;
                }
            }
        }else{
            QMessageBox::information(this,"failed","query is false");
        }
    }else{
        QMessageBox::information(this, "Connection", "connection failed");

    }

}


