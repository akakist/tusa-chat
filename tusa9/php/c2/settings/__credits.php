<?
	session_start();
	header("Content-Type: text/html; charset=\"UTF-8\"");
        import_request_variables("gp", "arg_");
	
	include "$BASE_DIR/inc/db_conn.php";
	include "$BASE_DIR/inc/str_nick.php";
	check_conn();
     if(isset($_SESSION['uid']))
     {
	$uid=intval($_SESSION['uid']);
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
