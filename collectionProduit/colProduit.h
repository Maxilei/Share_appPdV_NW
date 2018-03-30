#ifndef COLProduit
#define COLProduit
using namespace std;
#include <iostream>
#include <vector>
#include "produit.h"


class ColProduit
{
private:
	vector <Produit> vectLesProduits;
public:
	void ajouterObjet(Produit newEquip);
	Produit obtenirObjet(int index);
	int cardinal();
};
#endif