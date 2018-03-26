<?
session_start();
$host='localhost';
$user='tonUser';
$pass='CeluiQueTuVeux';
$nomBase="nomDeLaBase";
mysql_connect($host,$user,$pass);
mysql_select_db('nomDeLaBase');
$base_url="http://gthom.btsinfogap.org/newWorld/";
$base=mysqli_connect($host,$user,$pass,$nomBase);
mysqli_query($base,"set collation utf8mb4_unicode_520_ci");
?>
