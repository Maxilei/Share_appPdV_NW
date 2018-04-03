#include "mainwindow.h"
#include "ui_mainwindow.h"
#define URL2 "http://172.29.56.5/~miori/NewWorld/Share_appPdV_NW/jsons_receptionPR/prodDuJour.php"
#define URL3 "http://172.29.56.5/~miori/NewWorld/Share_appPdV_NW/jsons_receptionPR/listeDesCdes.php"
#include <QUrl>
#include <QUrlQuery>
#include <QJsonArray>
#include<QJsonObject>
#include<QCheckBox>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QTableWidget>

MainWindow::MainWindow(QNetworkAccessManager *pmyNWM, QString theName, QString theSurname, QString theMail, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myNWM=pmyNWM;
    name=theName;
    surname=theSurname;
    mail=theMail;
    QUrl serviceUrl(URL2);
    QUrl donnees;
    QUrlQuery query;

    QNetworkRequest request(serviceUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

   QByteArray postData;
   reply = myNWM->post(request,postData);
   connect(reply,SIGNAL(finished()),this,SLOT(afficheLesProducteurs()));

}
void MainWindow::afficheLesProducteurs()
{
    qDebug()<<"void MainWindow::afficheLesProducteurs()";
    QByteArray response_data = reply->readAll();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
    jsArray=jsonResponse.array();
    int nbLDC=jsArray.count();
    qDebug()<<nbLDC;
    int boucle=0;
    while(boucle < nbLDC)
    {
        QPushButton *nouveauBouton = new QPushButton(jsArray[boucle].toObject()["userNom"].toString()+jsArray[boucle].toObject()["userPrenom"].toString(),this);
        nouveauBouton->setProperty("idProducteur",jsArray[boucle].toObject()["utilisateurID"].toString());
        connect(nouveauBouton,SIGNAL(clicked()),this,SLOT(afficheLaLivraison()));
        ui->maVerticalLayout->addWidget(nouveauBouton);
        boucle++;
    }

}

void MainWindow::afficheLaLivraison()
{
    qDebug()<<"void MainWindow::afficheLaLivraison()";
    QPushButton* boutonClique=(QPushButton*) sender();
    QString sonId=boutonClique->property("idProducteur").toString();
    //la suite
    qDebug()<<sonId;
    QUrl serviceUrl(URL3);
    QUrl donnees;
    QUrlQuery query;
    query.addQueryItem("utilisateurID",sonId);
    donnees.setQuery(query);
    QByteArray postData(donnees.toString(QUrl::RemoveFragment).remove("?").toLatin1());

    QNetworkRequest request(serviceUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QNetworkReply *reply2 = myNWM->post(request,postData);
    while(!reply2->isFinished())
    {
        qApp->processEvents();
    }
    QByteArray response_data = reply2->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
    jsArray=jsonResponse.array();
    int nbLDC=jsArray.count();
    qDebug()<<nbLDC;
    qDebug()<<jsArray[0].toObject()["lotDescription"].toString();

    QTableWidget *nouvelleTable = new QTableWidget(nbLDC,4,this);
    int boucle=0;
    while(boucle < nbLDC)
    {
    //    nouvelleTable->setItem(boucle,0,);
        nouvelleTable->setItem(boucle,1,new QTableWidgetItem(jsArray[boucle].toObject()["lotDescription"].toString()));
        nouvelleTable->setItem(boucle,2,new QTableWidgetItem(jsArray[boucle].toObject()["qte"].toString()));
        nouvelleTable->setItem(boucle,3,new QTableWidgetItem(jsArray[boucle].toObject()["umNom"].toString()));
        boucle++;
    }
    ui->maVerticalLayout->addWidget(nouvelleTable);
}

MainWindow::~MainWindow()
{
    delete ui;
}
