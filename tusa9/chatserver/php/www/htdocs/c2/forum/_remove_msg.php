<?
	session_start();
	header("Content-Type: text/html; charset=\"windows-1251\"");
        import_request_variables("gp", "arg_");
	
	include "inc/db_conn.php";
	check_conn();
     if(isset($_SESSION['login']))
     {
     	$login=$_SESSION['login'];
	$uid=$_SESSION['uid'];
	
     }
     if(!isset($login))
     {
     }

	if(isset($_SESSION['privs']['forum']))
	{
	    $arg_n=intval($arg_n);
		$tid=mysql_select1("select tid from Forum_messages where id='$arg_n'");
		mysql_query("delete from Forum_messages where id='$arg_n'") or die(mysql_error());
		mysql_query("update Forum_themes set msgcnt=msgcnt-1 where id='$tid'") or die(mysql_error());
	}
	return "<tr><td>Сообщение удалено</td></tr>";
	?>
