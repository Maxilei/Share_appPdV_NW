#include "mainwindow.h"
#include "ui_mainwindow.h"
#define URL2 "http://172.29.56.5/~miori/NewWorld/Share_appPdV_NW/jsons_receptionPR/prodDuJour.php"
#include <QUrl>
#include <QUrlQuery>
#include <QJsonArray>
#include<QJsonObject>
#include<QCheckBox>
#include <QJsonDocument>
#include <QNetworkReply>

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
    QByteArray response_data = reply->readAll();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
    jsArray=jsonResponse.array();
    int nbLDC=jsArray.count();
    qDebug()<<nbLDC;
    qDebug()<<jsArray[0].toObject()["userNom"].toString();
    int boucle=0;
    while(boucle < nbLDC)
    {
        QPushButton *nouveauBouton = new QPushButton(jsArray[boucle].toObject()["userNom"].toString()+jsArray[boucle].toObject()["userPrenom"].toString(),this);
        nouveauBouton->setProperty("idProducteur",jsArray[boucle].toObject()["utilisateurId"].toString());
        connect(nouveauBouton,SIGNAL(clicked()),this,SLOT(afficheLaLivraison()));
        ui->maVerticalLayout->addWidget(nouveauBouton);
        boucle++;
    }

}

void MainWindow::afficheLaLivraison()
{
    //
    QPushButton* boutonClique=(QPushButton*) sender();
    QString sonId=boutonClique->property("idProducteur").toString();
    //la suite

}

MainWindow::~MainWindow()
{
    delete ui;
}
