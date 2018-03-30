#ifndef Produit
#define Produit 
using namespace std;
#include <iostream>
#include <QString>

class Produit
{
private:
	QString idProduit;
    QString libProduit;
public:
	Produit(QString idProd,QString libProd);
	QString versChaine();
};

#endif