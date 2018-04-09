<?php
include("mini.php");
if(isset($_POST['login'])&&isset($_POST['password']))
{
	$req="SELECT userMail as identifiant, userNom as nom, userPrenom as prenom FROM utilisateur WHERE userMail='".$_POST['login']."' and userMdp='".$_POST['password']."'";
	$res=mysqli_query($base,$req);
	$tabInfo=mysqli_fetch_array($res);
	if(mysqli_num_rows($res)==1)
	$_SESSION['login']=$tabInfo[0];
	echo json_encode($tabInfo);
}
else
print_r($_POST);
?>