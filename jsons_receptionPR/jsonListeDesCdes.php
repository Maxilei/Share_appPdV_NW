<?php 
include("mini.php");
if(isset($_SESSION['login']))
    $pointRelaisMail = $_SESSION['login'];
	if(isset($_POST['utilisateurID'])){
		$prodId = $_POST['utilisateurID'];
	}
{
	$resultat=array();
    $req="
    	SELECT lotDescription 
    	FROM pointRelais  
    		INNER JOIN LDC  
    			ON pointRelais.prID=LDC.prID 
    		INNER JOIN commande 
    			ON LDC.cmdID=commande.cmdID 
    		INNER JOIN producteur 
    			ON LDC.producID=producteur.producID 
    		INNER JOIN utilisateur 
    			ON producteur.utilisateurID = utilisateur.utilisateurID 
    		INNER JOIN lot 
    			ON LDC.lotID = lot.lotID;
    	WHERE userRole = 'Prod'
			AND cmdDateLivraison=CURDATE()
			AND pointRelais.prID=(SELECT  prID FROM pointRelais INNER JOIN utilisateur ON pointRelais.utilisateurID = utilisateur.utilisateurID WHERE userMail='user7@gmail.com');
			AND utilisateurID=".$prodId.";";
	
	$res=mysqli_query($base,$req);
	while($tabInfos=mysqli_fetch_assoc($res))
	{
		$resultat[]=$tabInfos;
	}
	echo json_encode($resultat);
}
else
print_r($_SESSION);

"
SELECT  lotDescription, cmdDateLivraison, LDC.qte, uniteMesure.umNom
FROM pointRelais  
INNER JOIN LDC  
ON pointRelais.prID=LDC.prID 
INNER JOIN commande 
ON LDC.cmdID=commande.cmdID 
INNER JOIN producteur 
ON LDC.producID=producteur.producID 
INNER JOIN uniteMesure 
ON lot.umId=uniteMesure.umID
INNER JOIN utilisateur 
ON producteur.utilisateurID = utilisateur.utilisateurID 
INNER JOIN lot 
ON LDC.lotID = lot.lotID
WHERE userRole = 'Prod'
AND cmdDateLivraison=CURDATE()
AND pointRelais.prID=(SELECT  prID FROM pointRelais INNER JOIN utilisateur ON pointRelais.utilisateurID = utilisateur.utilisateurID WHERE userMail='user7@gmail.com');
AND utilisateurID=".$prodId.";";
"

?>