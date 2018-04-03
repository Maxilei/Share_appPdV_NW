<?php 
include("mini.php");
if(isset($_SESSION['login']) && isset($_POST['utilisateurID']))
{
    $pointRelaisMail = $_SESSION['login'];
	$producteurId = $_POST['utilisateurID'];
	$resultat=array();
    $req="
	    	SELECT  lotDescription, LDC.qte, uniteMesure.umNom
			FROM pointRelais  
				INNER JOIN LDC  
					ON pointRelais.prID=LDC.prID
				INNER JOIN producteur 
					ON LDC.producID=producteur.producID 
				INNER JOIN commande 
					ON LDC.cmdID=commande.cmdID 
				INNER JOIN consommateur 
					ON commande.consID=consommateur.consID 
				INNER JOIN utilisateur 
					ON consommateur.utilisateurID = utilisateur.utilisateurID 
				INNER JOIN lot 
					ON LDC.lotID = lot.lotID
				INNER JOIN uniteMesure 
					ON lot.umId=uniteMesure.umId
			WHERE userRole = 'Cons'
				AND cmdDateLivraison=CURDATE()
				AND pointRelais.prID=(SELECT  prID FROM pointRelais INNER JOIN utilisateur ON pointRelais.utilisateurID = utilisateur.utilisateurID WHERE userMail='user7@gmail.com')
				AND producteur.producID = (SELECT producteur.producID FROM producteur INNER JOIN utilisateur ON producteur.utilisateurID = utilisateur.utilisateurID WHERE utilisateur.utilisateurID= ".$producteurId." )";
	
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
