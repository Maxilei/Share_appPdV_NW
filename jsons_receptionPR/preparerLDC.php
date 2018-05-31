<?php
include("mini.php");
if(isset($_SESSION['login']))
{
	$req="SELECT prID as identifiant FROM utilisateur INNER JOIN pointRelais ON utilisateur.utilisateurID=pointRelais.utilisateurID WHERE userMail='".$_SESSION['login'];
	$res=mysqli_query($base,$req);
	$tabInfo=mysqli_fetch_array($res);
	if(mysqli_num_rows($res)==1)
	$prID=$tabInfo[0];

	$lotID=$_POST['lotID'];
	$cmdID=$_POST['cmdID'];
	$txtReq="update LDC set status="Livré au point relais" where cmdID=".$cmdID." AND lotID=".$lotID." AND prID=".$prID;
	$res=mysqli_query($base,$txtReq);
    echo "good job!!!";
}
else
print_r($_SESSION);
?>
