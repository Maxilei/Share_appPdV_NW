<?php
include("mini.php");
if(isset($_SESSION['login']))
{   
    $pointRelaisMail =$_SESSION['login']; 
    //$pointRelaisMail ="user7@gmail.com";
    //Requete qui ressort les producteurs qui auront une livraison demain
	$resultat=array();
    $req="
        SELECT userNom, userPrenom, utilisateur.utilisateurID
        FROM pointRelais
            INNER JOIN LDC
                ON pointRelais.prID=LDC.prID
            INNER JOIN commande
                ON LDC.cmdID=commande.cmdID
            INNER JOIN lot 
                ON LDC.lotID=lot.lotID
            INNER JOIN producteur 
                ON lot.producID=producteur.producID 
            INNER JOIN utilisateur 
                ON producteur.utilisateurID = utilisateur.utilisateurID
        WHERE userRole = 'Prod'
            AND pointRelais.prID=(SELECT  prID FROM pointRelais INNER JOIN utilisateur ON pointRelais.utilisateurID = utilisateur.utilisateurID WHERE userMail='".$pointRelaisMail."');";
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
