#include "mainwindow.h"
#include "ui_mainwindow.h"
#define URL2 "http://172.29.56.5/~miori/NewWorld/Share_appPdV_NW/jsons_receptionPR/prodDuJour.php"
#define URL3 "http://172.29.56.5/~miori/NewWorld/Share_appPdV_NW/jsons_receptionPR/listeDesCdes.php"
#define URL4 "http://172.29.56.5/~miori/NewWorld/Share_appPdV_NW/jsons_receptionPR/consommateurDuJour.php"
#define URL5 "http://172.29.56.5/~miori/NewWorld/Share_appPdV_NW/jsons_receptionPR/produitsDeLaCommande.php"
#define URL6 "http://172.29.56.5/~miori/NewWorld/Share_appPdV_NW/jsons_receptionPR/incrementationStatus.php"
#define URL7 "http://172.29.56.5/~miori/NewWorld/Share_appPdV_NW/jsons_receptionPR/decrementationStatus.php"
#include <QUrl>
#include <QUrlQuery>
#include <QJsonArray>
#include <QJsonObject>
#include <QCheckBox>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QTableWidget>
#include "boutonproducteur.h"
#include "boutonclient.h"

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
    replyClient = myNWM->post(requestClient,postDataClient);
    connect(replyClient,SIGNAL(finished()),this,SLOT(afficherLesClients()));

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
        //validerLivraison->setProperty("coche",)
        nouvelleTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Valider"));
        nouvelleTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Produit"));
        nouvelleTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Quantité"));
        nouvelleTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Mesure"));
        int ligne=0;
        while(ligne < nbLDC)
        {
            QCheckBox *nouvelleCheckBox=new QCheckBox(nouvelleTable);
            nouvelleCheckBox->setProperty("lotID",jsArray[ligne].toObject()["lotID"].toString());
            nouvelleCheckBox->setProperty("cmdID",jsArray[ligne].toObject()["cmdID"].toString());
            connect(nouvelleCheckBox,SIGNAL(clicked(bool)),this,SLOT(preparedCheckBox(bool)));
            nouvelleTable->setCellWidget(ligne,0,nouvelleCheckBox );
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
    QByteArray response_data = replyClient->readAll();

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
        connect(nouveauBoutonClient,SIGNAL(clicked()),this,SLOT(afficherCommandeClient()));
        ui->maVerticalLayoutClient->addWidget(nouveauBoutonClient);
        boucle++;
    }
}

void MainWindow::afficherCommandeClient(){
    BoutonClient* boutonClique=(BoutonClient*) sender();
    bool estOuvert = boutonClique->isOpen();
    if(boutonClique->getTabAdresse() != NULL && boutonClique->getTabAdresse()->isHidden() == true ){
        qDebug()<< "if tab isHidden == true : "<<boutonClique->getTabAdresse()->isHidden();
        boutonClique->getTabAdresse()->show();
    }
    else{if(boutonClique->getTabAdresse() != NULL && boutonClique->getTabAdresse()->isHidden() == false ){
        qDebug()<< "tab isHidden  == false: "<<boutonClique->getTabAdresse()->isHidden();
        boutonClique->getTabAdresse()->hide();
    }}
    if(!estOuvert){
        qDebug()<<"void MainWindow::afficherCommandeClient()";
        QString sonId=boutonClique->getClient();
        //la suite
        qDebug()<<"ID du client : " <<sonId;
        QUrl serviceUrl(URL5);
        QUrl donnees;
        QUrlQuery query;
        query.addQueryItem("utilisateurID",sonId);
        donnees.setQuery(query);
        QByteArray postData(donnees.toString(QUrl::RemoveFragment).remove("?").toLatin1());
        QNetworkRequest request(serviceUrl);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        QNetworkReply *replyClient2 = myNWM->post(request,postData);
        qDebug() <<"Donnée : "<< donnees;
        while(!replyClient2->isFinished())
        {
            qApp->processEvents();
        }
        QByteArray response_data = replyClient2->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
        jsArray=jsonResponse.array();
        int nbLDC=jsArray.count();
        qDebug()<<"nombre de produit : " <<nbLDC;
        qDebug()<<jsArray[0].toObject()["lotDescription"].toString();

        QTableWidget *nouvelleTable = new QTableWidget(nbLDC,4  ,this);
        boutonClique->setTableWidget(nouvelleTable);
        //boutonClique->setProperty("adresseTab",QBitArray(nouvelleTable));
        nouvelleTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Valider"));
        nouvelleTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Produit"));
        nouvelleTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Quantité"));
        nouvelleTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Mesure"));
        int ligne=0;
        while(ligne < nbLDC)
        {
            QCheckBox *nouvelleCheckBox=new QCheckBox(nouvelleTable);
            nouvelleCheckBox->setProperty("lotID",jsArray[ligne].toObject()["lotID"].toString());
            nouvelleCheckBox->setProperty("cmdID",jsArray[ligne].toObject()["cmdID"].toString());
            connect(nouvelleCheckBox,SIGNAL(clicked(bool)),this,SLOT(preparedCheckBox(bool)));
            nouvelleTable->setCellWidget(ligne,0,nouvelleCheckBox );
            nouvelleTable->setItem(ligne,1,new QTableWidgetItem(jsArray[ligne].toObject()["lotDescription"].toString()));
            nouvelleTable->setItem(ligne,2,new QTableWidgetItem(jsArray[ligne].toObject()["qte"].toString()));
            nouvelleTable->setItem(ligne,3,new QTableWidgetItem(jsArray[ligne].toObject()["umNom"].toString()));

            ligne++;
        }
        ui->maVerticalLayoutClient->addWidget(nouvelleTable);
    }}
void MainWindow::preparedCheckBox(bool coche)
{
    qDebug()<<"void MainWindow::preparedCheckBox(bool coche)";
    if(coche)
    {
        qDebug()<<((QCheckBox*)sender())->property("lotID").toString();
        qDebug()<<((QCheckBox*)sender())->property("cmdID").toString();
        QUrl serviceUrl(URL6);
        QUrl donnees;
        QUrlQuery query;
        query.addQueryItem("lotID", ((QCheckBox*)sender())->property("lotID").toString());
        query.addQueryItem("cmdID", ((QCheckBox*)sender())->property("cmdID").toString());
        donnees.setQuery(query);
        QByteArray postData(donnees.toString(QUrl::RemoveFragment).remove("?").toLatin1());
        qDebug()<<postData;
        QNetworkRequest request(serviceUrl);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        reply = myNWM->post(request,postData);
        qDebug()<<"hello"<<reply->readLine();
        connect(reply,SIGNAL(finished()),this,SLOT(rendreCompte()));
    }
    else
    {
        qDebug()<<((QCheckBox*)sender())->property("lotID").toString();
        qDebug()<<((QCheckBox*)sender())->property("cmdID").toString();
        QUrl serviceUrl(URL7);
        QUrl donnees;
        QUrlQuery query;
        query.addQueryItem("lotID", ((QCheckBox*)sender())->property("lotID").toString());
        query.addQueryItem("cmdID", ((QCheckBox*)sender())->property("cmdID").toString());
        donnees.setQuery(query);
        QByteArray postData(donnees.toString(QUrl::RemoveFragment).remove("?").toLatin1());
        qDebug()<<postData;
        QNetworkRequest request(serviceUrl);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        reply = myNWM->post(request,postData);
        qDebug()<<"hello"<<reply->readLine();
    }
}

void MainWindow::rendreCompte()
{
    qDebug()<<"La Préparation est bien enregistrée";
}


MainWindow::~MainWindow()
{
    delete ui;
}
