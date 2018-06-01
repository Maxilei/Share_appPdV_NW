<?php
include("mini.php");
//$_SESSION['login']=$_GET['login'];
if(isset($_SESSION['login']))
{   
    $pointRelaisMail =$_SESSION['login'];
    //Requete qui ressort les producteurs qui auront une livraison demain
	$resultat=array();
    $req="
        SELECT DISTINCT(utilisateur.utilisateurID),userNom, userPrenom 
        FROM pointRelais
            INNER JOIN commande
                ON pointRelais.prID=commande.prID
            INNER JOIN consommateur 
                ON commande.consID=consommateur.consID
            INNER JOIN utilisateur 
                ON consommateur.utilisateurID = utilisateur.utilisateurID
        WHERE userRole = 'Cons'
            AND cmdDate='2018-03-27'
            AND pointRelais.prID=(SELECT  prID FROM pointRelais INNER JOIN utilisateur ON pointRelais.utilisateurID = utilisateur.utilisateurID WHERE userMail='".$pointRelaisMail."')";
//AND cmdDate='2018-03-27'
//AND cmdDateLivraison=(SELECT DATE_ADD(curdate(), INTERVAL 1 DAY) AS Tomorrow)

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
