<?php
include("mini.php");
if(isset($_SESSION['login']))
{
	$numero=$_POST['numeroLDC'];
	$txtReq="update ldc set prepare=true where numero=$numero";
	$res=mysqli_query($base,$txtReq);
    echo "good job!!!";
}
else
print_r($_SESSION);
?>