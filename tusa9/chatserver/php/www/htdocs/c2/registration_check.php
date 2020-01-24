<?
	session_start();
	header("Content-Type: text/html; charset=\"windows-1251\"");
        import_request_variables("gp", "arg_");
	
	include "inc/db_conn.php";
	include "inc/str_nick.php";
	include "inc/unescape_rus.php";
	check_conn();
	if(isset($arg_nick))
	{
		$arg_nick=unescape_rus($arg_nick);
		$strn=str_nick($arg_nick);
		list($nid)=mysql_select1row("select id from nicks where str_nick='$strn'");
		if(isset($nid))
		{
			echo "Такой ник уже занят";
			die;
		}
		list($nid)=mysql_select1row("select id from nicks where nick='$arg_nick'");
		if(isset($nid))
		{
			echo "Такой ник уже занят";
			die;
		}
		echo "Ник свободен";
		die;
	}
	if(isset($arg_email))
	{
		$arg_email=unescape_rus($arg_email);
		$strn=str_nick($arg_email);
		list($nid)=mysql_select1row("select id from tbl_users where upperlogin='$strn'");
		if(isset($nid))
		{
			echo "Такой email уже занят";
			die;
		}
		list($nid)=mysql_select1row("select id from tbl_users where login='$arg_email'");
		if(isset($nid))
		{
			echo "Такой email уже занят";
			die;
		}
		echo "Email свободен";
		die;
	}
//	$credits=mysql_select1("select credit_summa from tbl_users where id='$uid'");
?>

