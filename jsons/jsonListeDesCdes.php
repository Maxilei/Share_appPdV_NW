<?
include("mini.php");
if(isset($_SESSION['identifiant']))
{
	$resultat=array();
    $req="select ldc.numero as numeroLDC, dateLivraison,heureRetraitPrevue,pointDeVente.nom as PDV,produit.libelle, ldc.quantite, lot.uniteDeVente, utilisateur.prenom, utilisateur.nom from liste inner join sousListe on sousListe.numeroliste=liste.numeroliste inner join pointDeVente on sousListe.no=pointDeVente.no inner join ldc on ldc.numeroSousListe=sousListe.numeroSousListe inner join lot on ldc.nolot=lot.nolot inner join produit on lot.produit=produit.numero  inner join utilisateur on utilisateur.identifiant=liste.identifiant where datediff(now(),dateLivraison)=-1 and lot.producteur=".$_SESSION['identifiant'];
	
	$res=mysqli_query($base,$req);
	while($tabInfos=mysqli_fetch_assoc($res))
	{
		$resultat[]=$tabInfos;
	}
	echo json_encode($resultat);
}
else
print_r($_SESSION);
?>
