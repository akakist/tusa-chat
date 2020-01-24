<?
	session_start();
	header("Content-Type: text/html; charset=\"windows-1251\"");
        import_request_variables("gp", "arg_");
	
	include "inc/db_conn.php";
	include "inc/str_nick.php";
	check_conn();
     if(isset($_SESSION['uid']))
     {
	$uid=$_SESSION['uid'];
     }
     if(!isset($uid))
     {
     	header("Location: /");die;
     }
					$credits=mysql_select1("select credit_summa from tbl_users where id='$uid'");
?>

	<?
	
	?>

				<b><?=sprintf("%2.2f",$credits)?></b>	
