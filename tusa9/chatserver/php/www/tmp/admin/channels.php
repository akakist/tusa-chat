<?
	session_start();
        import_request_variables("gp", "arg_");
	include "inc/db_conn.php";
	check_conn();
     if(isset($_SESSION['login']))
     {
     	$login=$_SESSION['login'];
	$uid=$_SESSION['uid'];
	
     }
     if(!isset($login) || !isset($_SESSION['privs']['settings']))
     {
     	header("Location: /");
     }
     else
     {
?>

<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1251">
<TITLE>��� "�������" - ������� ������ -> ��������� -> �������</TITLE>
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
<big><big><center><b>��������� ������</b></center></big></big><br>
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

<b>�������� �������:</b><br>

<input type=text name='add_id' value="">

<input type=button value="��������" onclick="return fupdate('addchannel');">
<p>
</center>

</form>
<?
}
?>