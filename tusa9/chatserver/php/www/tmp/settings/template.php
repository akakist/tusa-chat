<?
	session_start();
        import_request_variables("gp", "arg_");

	
	include "c2/inc/db_conn.php";
	include "c2/inc/conf.php";
	check_conn();

	if(isset($_SESSION['uid']))
	$uid=$_SESSION['uid'];
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
<script type="text/javascript" src="/js/md5.js"></script>

</head>
<script>
	
</script>
<body onload='$("#online").load("/c2/online.php");'>

<div id="wrapper">
<div id="head">
<a href="#"><img src="logo.gif" alt=""></a>
</div>

<div id="content">

	<div id="left">
	<?
	include "menu.php";
	?>
	</div>
	
	<div id="center">
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