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
	if(isset($_SESSION["privs"]["topic"]) && $_SESSION["level"]>=500)
	{
		$top=mysql_escape_string(unescape_rus($arg_top));
		
		$channel=intval($arg_chan);
		mysql_query("insert into ext_events(event,d1,d2) values('cmd=set_topic uid=$uid channel=$channel','$top','')") or die(mysql_error());
//		echo "Tопик изменен на $top";
	}
	else
	{
		echo "Недостаточно привилегий";
	}
?>