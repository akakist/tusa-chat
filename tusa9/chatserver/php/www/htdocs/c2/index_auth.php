<?
	session_start();
	header("Content-Type: text/html; charset=\"windows-1251\"");
        import_request_variables("gp", "arg_");
	include "inc/db_conn.php";
	include "inc/unescape_rus.php";
	include "inc/str_nick.php";
	check_conn();

	function set_privs($uid)
	{
			$res=mysql_query("select priv from tbl_privs where uid='$uid'") or die(mysql_error().__FILE__.__LINE__);
			$privs=array();
			while($rw=mysql_fetch_row($res))
			{
				$privs[substr($rw[0],1)]="1";
			}
			if(count($privs))$_SESSION['privs']=$privs;
	}

	function set_moders($uid)
	{
			$res=mysql_query("select channel from moderators where uid='$uid'") or die(mysql_error().__FILE__.__LINE__);
			$m=array();
			while($rw=mysql_fetch_row($res))
			{
				$m[$rw[0]]="1";
			}
			if(count($m))$_SESSION['moder']=$m;
	}
    function check_auth($l,$p) 
    {

	
	return;
    }
    

    if(isset($arg_login))
     {
	$_SESSION=array();
	$arg_login=unescape_rus($arg_login);
	$arg_pass=unescape_rus($arg_pass);
	//echo $arg_pass;
	if(isset($uid))unset($uid);
	if(!isset($arg_pass)) $error="Не указан пароль";
	$l=$arg_login;
	if(!isset($error))
    	    list($uid)=mysql_select1row("select id from tbl_users where login='".mysql_escape_string($l)."'");
	if(!isset($error)&&!isset($uid)) list($uid,$banned)=mysql_select1row("select uid,banned from nicks where str_nick='".mysql_escape_string(str_nick($l))."'");
	if(isset($banned) && $banned==1)
	{
		 $error="Ник забанен";
		$errscr= "<script> document.start.login.focus();</script>";
	}
	if(!isset($error)&&!isset($uid))
	{ 
		$error="Неверный логин или ник 1";
		$errscr= "<script> document.start.login.focus();</script>";
	}
	$uid=intval($uid);
	if(!isset($error) && isset($uid))
	{
	    list($login,$id,$level,$gender,$pass,$last_nick,$last_nick_id)=mysql_select1row("select login,id,level,gender,lower(pass),last_nick,last_nick_id from tbl_users where id='$uid'");
	    if(md5($arg_pass)!=$pass)
	    {
	    	$error="Неверный пароль";
		$errscr= "<script> document.start.pass.focus();</script>";
	    }
	}
	
	list($time_cnt,$time_free,$descr)=mysql_select1row("select time_cnt,time_free,descr from banned_login where uid='$uid' and time_free>NOW()");
	if(isset($time_cnt))
	{
		$error="Логин забанен за $descr на $time_cnt, дата окончания $time_free";
		$errscr= "<script> document.start.login.focus();</script>";
	}
	if($level<900)
	{
		$ip=$_SERVER["REMOTE_ADDR"];
		list($time_cnt,$time_free,$descr)=mysql_select1row("select time_cnt,time_free,za from banned_ip where ip='$ip' and time_free>NOW()");
		if(isset($time_cnt))
		{
			$error="Ваш IP адрес забанен за $descr на $time_cnt, дата окончания $time_free";
			$errscr= "<script> document.start.login.focus();</script>";
		}
	}
	

	if(!isset($error))
        {
	    $_SESSION['login']=$login;
	    $_SESSION['uid']=$uid;
	    $_SESSION['level']=$level;
	    $_SESSION['gender']=$gender;
	    $_SESSION['ip']=$_SERVER["REMOTE_ADDR"];
	    set_privs($uid);
	    set_moders($uid);

	    $_SESSION['last_nick']=$last_nick;
    	    $_SESSION['last_nick_id']=$last_nick_id;
	    $sid=md5(session_id());
	    $oldsid=mysql_select1("select  php_session_id from tbl_users where id='$uid'");
	    if($sid!=$oldsid)
	    {
	 	   mysql_query("update tbl_users set php_session_id='$sid' where id='$uid'") or die(mysql_error());
	    }
	}

     }

     if(isset($_SESSION['login']))
     {
     	$login=$_SESSION['login'];
	$uid=$_SESSION['uid'];
     }
     if(!isset($error))
     {
        echo "<div style='color:yellow;text-align: center;font-weight:bold; margin:5px'>Входим в систему</div>";
     	echo("<script>window.top.location='/c2/url_login.php'</script>");
	die;
     }
	
?>

				<?
				if(isset($error)) echo "<div class=error>$error</div>";
				?>
			
			<div class="login-text">
				Логин: 
				<div style="padding-bottom: 7px;"></div>
				Пароль:
			</div>
			<div class="login-input">
				<?
				    $l="";
				    if(isset($arg_login)) $l=$arg_login;
				?>
				<input type="text" name="login" style="width: 130px;" value='<?=$l?>'>  <!--'<??> '-->
				<div style="padding: 2px 0;"></div>
				<input type="password" name="pass" style="width: 130px;">
			</div>
			<div class="login-button">
				<input type="submit" value="Войти" style="width: 50px;" onclick=' 
//					document.write(document.start.pass.value);
//				document.start.pass.value=md5(document.start.pass.value);
					$.post("index_auth.php",{ 
						login: escape(document.start.login.value),
						pass: escape(document.start.pass.value), 
						r: Math.random(),
						scr: screen.width+"x"+screen.height+"x"+screen.colorDepth},function(data){$("#auth").html(data); });
						
						return false;
						'>

			</div>
			<?
				if(isset($errscr))
				echo $errscr;
			?>
			

