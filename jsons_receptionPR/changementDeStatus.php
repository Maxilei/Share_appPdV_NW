<?php
include("mini.php");
//$_SESSION['login']=$_GET['login'];
if(isset($_SESSION['login']))
{   
    $pointRelaisMail =$_SESSION['login'];
    $lotID =$_POST['lotID'];
    $cmdID =$_POST['cmdID'];
    //Requete qui ressort les producteurs qui auront une livraison demain
	$resultat=array();
    $req="
    	UPDATE LDC 
    	SET status = 'Livré au point relais' 
    	WHERE lotID = '.$lotID.' 
    		AND cmdID = '.$cmdID.'
    		AND prID=(SELECT  prID FROM pointRelais INNER JOIN utilisateur ON pointRelais.utilisateurID = utilisateur.utilisateurID WHERE userMail='.$pointRelaisMail.')";
//AND cmdDateLivraison=(SELECT DATE_ADD(curdate(), INTERVAL 1 DAY) AS Tomorrow)

	$res=mysqli_query($base,$req);
	while($tabInfos=mysqli_fetch_assoc($res))
	{
		$resultat[]=$tabInfos;
	}
	//echo json_encode($resultat);
}
else
print_r($_SESSION);
?> 
