<?
	session_start();
        import_request_variables("gp", "arg_");

	
	include "$BASE_DIR/inc/db_conn.php";
	include "$BASE_DIR/c2/inc/conf.php";
	check_conn();
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset='UTF-8'">
<meta http-equiv="Cache-Control" content="no-cache">
<meta http-equiv="Pragma" content="no-cache">
<link rel="icon" href="/favicon.ico" type="image/x-icon">
<link rel="shortcut icon" href="/favicon.ico" type="image/x-icon">
<link href="/c2/css/reset.css" type="text/css" rel="stylesheet">
<link href="/c2/css/main2.css" type="text/css" rel="stylesheet">
<title>Чат "Тусовка"</title>
<script src="/c2/js/jquery.min.js" type="text/javascript"></script>
<script src="/c2/js/main.js" type="text/javascript"></script>
<script type="text/javascript" src="/js/md5.js"></script>

</head>
<script>
	
</script>
<?
	include "$BASE_DIR/inc/conf.php";
?>
<?
if ( $_SERVER["SCRIPT_FILENAME"] != "top.php" )
    {
?>
<body onload='$("#online").load("/c2/online.php?r=<?=rand()?>");'> <!--"<??> "--><??>
<?

    }
?>
        

<div id="wrapper">
<div id="head">
<div style='float:left'><a href="#"><img src="/img/logo.gif" alt=""></a></div>
<!---banner-->
<center>
<span  style="margin-right: 145px;">
<script type="text/javascript">//<![CDATA[
var tbpd=document.getElementsByTagName("script");tbpd=tbpd[tbpd.length-1];function t_tbpd(){var s=document.createElement("SCRIPT");s.type="text/javascript";s.src="http://tbe.tom.ru/?jg=x&s=46860&a=tusovka.tomsk.ru&id=tbpd&rnd="+(new Date().getTime());document.documentElement.firstChild.appendChild(s);}setTimeout("t_tbpd()",1)
//]]></script><noscript><p style="display:inline"><a href="http://tbe.tom.ru/?gl=x&s=46860&amp;a=tusovka.tomsk.ru"><img src="http://tbe.tom.ru/?gi=x&amp;a=tusovka.tomsk.ru" alt="TBE" style="border:0" /></a></p></noscript>
</span>
</center>
<!---banner-->

</div>

<div id="content">

	<div id="left">
	<?
	include "menu.php";
	?>
	</div>
	
	<div id="center">
	<?
	include $_SERVER["SCRIPT_FILENAME"].".php";
	?>
	</div>

</div>

<div id="right">
<ul id="online">
</ul>

</div>

</div>

<div id="foot">

<?
include "banners/tbe.php";
include "banners/metka_catalog.php";
?>

</div>
</body>
</html>