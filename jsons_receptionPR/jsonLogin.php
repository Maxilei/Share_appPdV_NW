<?php
include("mini.php");
if(isset($_GET['login'])&&isset($_GET['password']))
{
	$req="SELECT userMail, userNom, userPrenom FROM utilisateur WHERE userMail='".$_GET['login']."' and userMdp='".$_GET['password']."' and userRole='PtRl'";
	$res=mysqli_query($base,$req);
	$tabInfo=mysqli_fetch_array($res);
	if(mysqli_num_rows($res)==1)
	$_SESSION['login']=$tabInfo[0];
	echo json_encode($tabInfo);
}
else
print_r($_GET);
?>