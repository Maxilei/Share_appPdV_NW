<?php
include("mini.php");
//$_SESSION['login']=$_GET['login'];
if(isset($_SESSION['login']))
{   
    $pointRelaisMail =$_SESSION['login'];
    //Requete qui ressort les producteurs qui auront une livraison demain
	$resultat=array();
    $req="UPDATE LDC 
    SET status = 'Livré au point relais' 
    WHERE ";
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