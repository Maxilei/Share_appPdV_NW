#include "colProduit.h"

void ColProduit::ajouterObjet(Produit newProd)
{
	vectLesProduits.push_back(newProd);
}
Produit ColProduit::obtenirObjet(int index)
{
    return vectLesProduits[index];
}
int ColProduit::cardinal()
{
	return vectLesProduits.size();
}
