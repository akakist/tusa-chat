<?
	session_start();
	header("Content-Type: text/html; charset=\"windows-1251\"");
        import_request_variables("gp", "arg_");
	
	include "inc/db_conn.php";
	include "inc/str_nick.php";
	include "inc/unescape_rus.php";
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
		mysql_query("insert into ext_events(event,d1,d2) values('set_topic $uid $channel','$top','')") or die(mysql_error());
//		echo "T���� ������� �� $top";
	}
	else
	{
		echo "������������ ����������";
	}
?>