<?
	session_start();
	header("Content-Type: text/html; charset=\"UTF-8\"");
        import_request_variables("gp", "arg_");
	
	include "$BASE_DIR/inc/db_conn.php";
	include "$BASE_DIR/inc/str_nick.php";
	include "$BASE_DIR/inc/unescape_rus.php";
	check_conn();
     if(isset($_SESSION['uid']))
     {
	$uid=intval($_SESSION['uid']);
     }
     if(!isset($uid))
     {
     	header("Location: /");die;
     }
#	$top=mysql_escape_string(unescape_rus($arg_top));
		
	$channel=intval($arg_channel);
	mysql_query("update tbl_users set last_channel='$channel' where id='$uid'") or die(mysql_error());
?>