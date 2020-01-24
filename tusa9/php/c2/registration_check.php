<?
	session_start();
	header("Content-Type: text/html; charset=\"UTF-8\"");
        import_request_variables("gp", "arg_");
	
	include "$BASE_DIR/inc/db_conn.php";
	include "$BASE_DIR/inc/str_nick.php";
	include "$BASE_DIR/inc/unescape_rus.php";
	check_conn();
	if(isset($arg_nick))
	{
		$arg_nick=unescape_rus($arg_nick);
		$strn=str_nick($arg_nick);
		list($nid)=mysql_select1row("select id from nicks where str_nick='".mysql_escape_string($strn)."'");
		if(isset($nid))
		{
			echo "Такой ник уже занят";
			die;
		}
		list($nid)=mysql_select1row("select id from nicks where nick='".mysql_escape_string($arg_nick)."'");
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
		list($nid)=mysql_select1row("select id from tbl_users where upperlogin='".mysql_escape_string($strn)."'");
		if(isset($nid))
		{
			echo "Такой email уже занят";
			die;
		}
		list($nid)=mysql_select1row("select id from tbl_users where login='".mysql_escape_string($arg_email)."'");
		if(isset($nid))
		{
			echo "Такой email уже занят";
			die;
		}
		echo "Email свободен";
		die;
	}
?>

