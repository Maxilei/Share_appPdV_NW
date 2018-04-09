#include "mainwindow.h"
#include "ui_mainwindow.h"
#define URL2 "http://172.29.56.5/~miori/NewWorld/Share_appPdV_NW/jsons_receptionPR/prodDuJour.php"
#define URL3 "http://172.29.56.5/~miori/NewWorld/Share_appPdV_NW/jsons_receptionPR/listeDesCdes.php"
#define URL4 "http://172.29.56.5/~miori/NewWorld/Share_appPdV_NW/jsons_receptionPR/consommateurDuJour.php"
#include <QUrl>
#include <QUrlQuery>
#include <QJsonArray>
#include<QJsonObject>
#include<QCheckBox>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QTableWidget>
#include "boutonproducteur.h"

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



    QUrl serviceUrlClient(URL4);
    QUrl donnees2;
    QUrlQuery query2;
    QNetworkRequest requestClient(serviceUrlClient);
    requestClient.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QByteArray postDataClient;
    reply = myNWM->post(requestClient,postDataClient);
    connect(reply,SIGNAL(finished()),this,SLOT(afficherLesClients()));

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
        QString nomProd = jsArray[boucle].toObject()["userPrenom"].toString()+" "+jsArray[boucle].toObject()["userNom"].toString();
        BoutonProducteur *nouveauBouton = new BoutonProducteur(jsArray[boucle].toObject()["utilisateurID"].toString(),nomProd,0);
        nouveauBouton->setText(nomProd);
        //nouveauBouton->setProperty("idProducteur",jsArray[boucle].toObject()["utilisateurID"].toString());
        //nouveauBouton->setProperty("isOpen",false);
        //nouveauBouton->setProperty("adresseTab",NULL);
        connect(nouveauBouton,SIGNAL(clicked()),this,SLOT(afficheLaLivraison()));
        ui->maVerticalLayout->addWidget(nouveauBouton);
        boucle++;
    }

}

void MainWindow::afficheLaLivraison()
{
    BoutonProducteur* boutonClique=(BoutonProducteur*) sender();
    bool isOpen = boutonClique->estOuvert();
    if(boutonClique->getTabAdresse() != NULL && boutonClique->getTabAdresse()->isHidden() == true ){
        qDebug()<< "if tab isHidden == true : "<<boutonClique->getTabAdresse()->isHidden();
        boutonClique->getTabAdresse()->show();
    }
    else{if(boutonClique->getTabAdresse() != NULL && boutonClique->getTabAdresse()->isHidden() == false ){
        qDebug()<< "tab isHidden  == false: "<<boutonClique->getTabAdresse()->isHidden();
        boutonClique->getTabAdresse()->hide();
    }}
    if(!isOpen){
        qDebug()<<"void MainWindow::afficheLaLivraison()";
        QString sonId=boutonClique->getProducteur();
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

        QTableWidget *nouvelleTable = new QTableWidget(nbLDC,6  ,this);
        boutonClique->setTableWidget(nouvelleTable);
        //boutonClique->setProperty("adresseTab",QBitArray(nouvelleTable));
        nouvelleTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Produit"));
        nouvelleTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Quantité"));
        nouvelleTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Mesure"));
        int ligne=0;
        while(ligne < nbLDC)
        {
        //    nouvelleTable->setItem(ligne,0,);
            nouvelleTable->setItem(ligne,1,new QTableWidgetItem(jsArray[ligne].toObject()["lotDescription"].toString()));
            nouvelleTable->setItem(ligne,2,new QTableWidgetItem(jsArray[ligne].toObject()["qte"].toString()));
            nouvelleTable->setItem(ligne,3,new QTableWidgetItem(jsArray[ligne].toObject()["umNom"].toString()));
            nouvelleTable->setItem(ligne,4,new QTableWidgetItem(jsArray[ligne].toObject()["userPrenom"].toString()));
            nouvelleTable->setItem(ligne,5,new QTableWidgetItem(jsArray[ligne].toObject()["userNom"].toString()));
            ligne++;
        }
        ui->maVerticalLayout->addWidget(nouvelleTable);
    }
}

void MainWindow::afficherLesClients()
{
    qDebug()<<"void MainWindow::afficheLesClients()";
    QByteArray response_data = reply->readAll();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
    jsArray=jsonResponse.array();
    int nbLDC=jsArray.count();
    qDebug()<<nbLDC;
    int boucle=0;
    while(boucle < nbLDC)
    {
        QString nomProd = jsArray[boucle].toObject()["userPrenom"].toString()+" "+jsArray[boucle].toObject()["userNom"].toString();
        BoutonClient *nouveauBoutonClient = new BoutonClient(jsArray[boucle].toObject()["utilisateurID"].toString(),nomProd,0);
        nouveauBoutonClient->setText(nomProd);
        //nouveauBouton->setProperty("idProducteur",jsArray[boucle].toObject()["utilisateurID"].toString());
        //nouveauBouton->setProperty("isOpen",false);
        //nouveauBouton->setProperty("adresseTab",NULL);
        connect(nouveauBoutonClient,SIGNAL(clicked()),this,SLOT(afficheLaLivraison()));
        ui->maVerticalLayoutClient->addWidget(nouveauBoutonClient);
        boucle++;
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
