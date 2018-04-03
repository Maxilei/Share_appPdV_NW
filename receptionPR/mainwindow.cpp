#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QNetworkAccessManager *pmyNWM, QString theName, QString theSurname, QString theIdentifiant,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myNWM=pmyNWM;
    name=theName;
    surname=theSurname;
    id=theIdentifiant;
    QPushButton *nomDuBouton = new QPushButton("Texte",this);
    nomDuBouton->show();

    QPushButton *nomDuBouton2 = new QPushButton(" de  ",this);
    nomDuBouton2->show();
    connect(nomDuBouton2, SIGNAL(clicked()),qApp,SLOT(quit()));

    QPushButton *nomDuBouton3 = new QPushButton("  votre ",this);
    nomDuBouton3->show();

    QPushButton *nomDuBouton4 = new QPushButton("Bouton",this);
    nomDuBouton4->show();


    ui->maVerticalLayout->addWidget(nomDuBouton);
    ui->maVerticalLayout->addWidget(nomDuBouton2);
    ui->maVerticalLayout->addWidget(nomDuBouton3);
    ui->maVerticalLayout->addWidget(nomDuBouton4);
}

MainWindow::~MainWindow()
{
    delete ui;
}
