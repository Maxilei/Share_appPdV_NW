#include "boutonproducteur.h"

BoutonProducteur::BoutonProducteur(QString leProducteur,QString nomProd, QWidget *parent) :producteur(leProducteur),
    QPushButton(parent)
{
    sonTableWidget=NULL;
    ouvert=false;
}

QString BoutonProducteur::getProducteur()
{
    return producteur;
}

QTableWidget* BoutonProducteur::getTabAdresse()
{
    return sonTableWidget;
}

bool BoutonProducteur::estOuvert()
{
    return ouvert;
}

void BoutonProducteur::setTableWidget(QTableWidget *leTableWidget)
{
    sonTableWidget=leTableWidget;
    ouvert=true;
}
