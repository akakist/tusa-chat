<?
	session_start();
	header("Content-Type: text/html; charset=\"windows-1251\"");
        import_request_variables("gp", "arg_");
	
	include "inc/db_conn.php";
	include "inc/str_nick.php";
	check_conn();
     if(isset($_SESSION['login']))
     {
     	$login=$_SESSION['login'];
	$uid=$_SESSION['uid'];
     }
     if(!isset($login))
     {
     	header("Location: /");
     }
					$credits=mysql_select1("select credit_summa from tbl_users where id='$uid'");
?>

	<?
	
	?>

				<b><?=sprintf("%2.2f",$credits)?></b>	
