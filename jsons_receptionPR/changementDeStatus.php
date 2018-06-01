<?php
include("mini.php");
//$_SESSION['login']=$_GET['login'];
//if(isset($_SESSION['login']))
//{   
    $pointRelaisMail =$_GET['login'];
    $lotID =$_GET['lotID'];
    $cmdID =$_GET['cmdID'];
    //Requete qui ressort les producteurs qui auront une livraison demain
	$resultat=array();
    $req="
    	UPDATE LDC 
    	SET status = 'Livré au point relais' 
    	WHERE lotID = '".$lotID."' 
    	AND cmdID = '".$cmdID."'
    	AND prID=(SELECT  prID FROM pointRelais INNER JOIN utilisateur ON pointRelais.utilisateurID = utilisateur.utilisateurID WHERE userMail='".$pointRelaisMail."')";
//AND cmdDateLivraison=(SELECT DATE_ADD(curdate(), INTERVAL 1 DAY) AS Tomorrow)
	echo $req;
	mysqli_query($base,$req);


/*}
else
print_r($_SESSION);*/
?> 
