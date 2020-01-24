<?
	session_start();	
		
    include 'inc/db_conn.php';
    check_conn();
    global $name;
    if(isset($_SESSION['login']))
    {
    	$uid=intval($_SESSION['uid']);
    	$name=mysql_select1("select name from tbl_users where id='$uid'");
	$_SESSION=array();
	
	    session_destroy();	
    
    }
    else
    {
    	?>
//	<script>window.top.location='/c2/';</script>
    	<?
    }

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset='windows-1215'">
<meta http-equiv="Cache-Control" content="no-cache">
<meta http-equiv="Pragma" content="no-cache">
<link rel="icon" href="/favicon.ico" type="image/x-icon">
<link rel="shortcut icon" href="/favicon.ico" type="image/x-icon">
<link href="/c2/css/reset.css" type="text/css" rel="stylesheet">
<link href="/c2/css/main2.css" type="text/css" rel="stylesheet">
<title>Чат "Тусовка"</title>
<script src="/c2/js/jquery.min.js" type="text/javascript"></script>
<script src="/c2/js/main.js" type="text/javascript"></script>
</head>
<script>
	
</script>
<body onload='$("#online").load("/c2/online.php");'>
<div id="wrapper">
<div id="head">
<a href="#"><img src="/img/logo.gif" alt=""></a>
</div>

<div id="content">

	<div id="left">
	<?
	include "menu.php";
	?>
	</div>

	<div id="center">
		<div class="first-line">До свидания, <?=$name?>!</div>
		<div class="text">
			Мы надеемся, что Вам у нас понравилось и Вы еще не раз к нам вернётесь, а также
			можете позвать своих друзей, чтоб веселее было :)<br>
    			До скорых встреч в <b>Тусовке</b> :-)

		</div>
	
	</div>

</div>

<div id="right">
<ul id="online">
</ul>

</div>

</div>

<div id="foot">

</div>
</body>
</html>
