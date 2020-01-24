<?
	session_start();
        import_request_variables("gp", "arg_");

	
	include "inc/db_conn.php";
	include "c2/inc/conf.php";
	check_conn();
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
<script src="/c2/js/jquery.min.js" type="text/javascript"></script>
<script src="/c2/js/main.js" type="text/javascript"></script>
<script type="text/javascript" src="/js/md5.js"></script>

</head>
<?
$s=sprintf("%02d",rand()%130);
?>
<img src=http://www.sama-sama-sama.ru/0cumsutr01/s<?=$s?>.gif><p>
Поза <?=$s?>
</html>