 #include "produit.h"

Produit::PRoduit(QString idProd, QString libProd)
{
	idProduit = idProd;
	libProduit = libProd;
}

QString Produit::versChaine()
{
	return libProduit;
}