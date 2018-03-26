<?
include("mini.php");
if(isset($_POST['login'])&&isset($_POST['password']))
{
	$req="select identifiant, nom, prenom from utilisateur where login='".$_POST['login']."' and motDePasse=password('".$_POST['password']."')";
	$res=mysqli_query($base,$req);
	$tabInfo=mysqli_fetch_array($res);
	if(mysqli_num_rows($res)==1)
	$_SESSION['identifiant']=$tabInfo[0];
	echo json_encode($tabInfo);
}
else
print_r($_POST);
?>