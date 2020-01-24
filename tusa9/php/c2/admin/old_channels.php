<?
session_start();
import_request_variables("gp", "arg_");
include "$BASE_DIR/inc/db_conn.php";
check_conn();
	
if ( !isset($_SESSION['ip']) || $_SESSION['ip']!=$_SERVER["REMOTE_ADDR"] || !isset($_SESSION['login']) || !isset($_SESSION['privs']['settings']) ) 
//|| $_SESSION['level'])!=1000
    {
    $name = $_SERVER["SCRIPT_FILENAME"];
    $ip = $_SERVER["REMOTE_ADDR"];    $d = date('Y.m.d H:i:s');
    if (!isset($_SESSION['login'])) { $login = "ПУСТОЙ"; }    else { $login = $_SESSION['login']; }
    if (!isset($_SESSION['ip'])) { $ip1 = "ПУСТОЙ"; }    else { $ip1 = $_SESSION['ip']; }
    $tmp = "$name С IP $ip попытка войти в сессию логина $login (старый IP $ip1)";
    mysql_query("insert into adm_events (login,date_events,type_events,events) values('$login','$d','CRACK','$tmp')") or die(mysql_error());
    session_destroy();  header("Location: /");
    }
else
    {
    $login=$_SESSION['login'];
    $uid=intval($_SESSION['uid']);
?>

<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=UTF-8">
<TITLE>Чат "Тусовка" - Консоль админа -> Настройки -> Комнаты</TITLE>
</head>
<script type="text/javascript" src="/js/jquery.pack.js"></script>

<LINK rel="stylesheet" type="text/css" href="/css/main.css">
<style>
.ci {background-color: #003060; border: 0}
</style>

<script>

function fupdate(n)
{
	document.f.cmd.value=n;
	document.f.submit();
	return false;
}

function opwin(url,nm,w,h)
{
	nw=window.open(url,nm,'toolbar=0,status=0,scrollbars=1,width='+w+',height='+h+',resizable=1');
	nw.focus();
	return false;
}
function do_del(id)
{
	document.f.id.value=id;
	document.f.cmd.value='del';
	document.f.submit();
	return false;
}
function do_change(id)
{
	document.f.id.value=id;
	document.f.cmd.value='change';
	document.f.submit();
	return false;
}
function edit_channel(id)
{
    window.open("edit_channel/"+id,"edit channel");
    return true;
}
</script>
<body>
<big><big><center><b>Админство комнат</b></center></big></big><br>
<?
if(isset($msg))echo "<center><font class=yelmsg>$msg</font></center>";
?>

<center>
<table class=border>
<?
	
?>
~namelist~
</table>


<form name="f" method="POST">
<input type=hidden name="cmd" value="">
<input type=hidden name="id" value="">
<input type=hidden name="msg" value="">


<p>

<b>Добавить комнату:</b><br>

<input type=text name='add_id' value="">

<input type=button value="Добавить" onclick="return fupdate('addchannel');">
<p>
</center>

</form>
<?
}
?>