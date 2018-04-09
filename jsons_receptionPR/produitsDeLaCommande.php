<?php
include("mini.php");
if(isset($_GET['login']) && isset($_GET['utilisateurID'])){
    $_SESSION['login']=$_GET['login'];
    $_POST['utilisateurID']=$_GET['utilisateurID'];
}
if(isset($_SESSION['login']) && isset($_POST['utilisateurID']))
{   
    $consommateurId = $_POST['utilisateurID'];
    $pointRelaisMail =$_SESSION['login'];
    //Requete qui ressort les producteurs qui auront une livraison demain
	$resultat=array();
    $req="
        SELECT  lotDescription, LDC.qte, uniteMesure.umNom
        FROM pointRelais
            INNER JOIN commande
                ON pointRelais.prID=commande.prID
            INNER JOIN LDC  
                    ON commande.prID=commande.prID
            INNER JOIN lot 
                ON LDC.lotID = lot.lotID
            INNER JOIN uniteMesure 
                ON lot.umId=uniteMesure.umId
            INNER JOIN consommateur 
                ON commande.consID=consommateur.consID
            INNER JOIN utilisateur 
                ON consommateur.utilisateurID = utilisateur.utilisateurID
        WHERE userRole = 'Cons'
            AND utilisateur.utilisateurID = '".$consommateurId."'
            AND cmdDateLivraison='2018-03-27'
            AND pointRelais.prID=(SELECT  prID FROM pointRelais INNER JOIN utilisateur ON pointRelais.utilisateurID = utilisateur.utilisateurID WHERE userMail='".$pointRelaisMail."')";
        //echo $req;
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