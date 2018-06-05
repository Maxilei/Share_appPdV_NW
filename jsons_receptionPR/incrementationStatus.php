<?php
include("mini.php");
//$_SESSION['login']=$_GET['login'];
if(isset($_SESSION['login']))
{   
    $pointRelaisMail =$_SESSION['login'];
    $lotID =$_POST['lotID'];
    $cmdID =$_POST['cmdID'];

	$resultat=array();
    $req="
    	UPDATE LDC 
    	SET idStatus = idStatus+1 
    	WHERE lotID = '.$lotID.' 
    		AND cmdID = '.$cmdID.'
    		AND prID=(SELECT  prID FROM pointRelais INNER JOIN utilisateur ON pointRelais.utilisateurID = utilisateur.utilisateurID WHERE userMail='".$pointRelaisMail."')";
//AND cmdDateLivraison=(SELECT DATE_ADD(curdate(), INTERVAL 1 DAY) AS Tomorrow)
	mysqli_query($base,$req);

}
else
print_r($_SESSION);
?> 
