<?
	session_start();
        import_request_variables("gp", "arg_");
	include "inc/db_conn.php";
	check_conn();
if (!isset($_SESSION['ip']) || $_SESSION['ip']!=$_SERVER['REMOTE_ADDR'] || !isset($_SESSION['login']) || $_SESSION['level']!=1000) //|| $_SESSION['level'])!=1000
    {
    $name = $_SERVER["SCRIPT_FILENAME"];
    $ip = $_SERVER["REMOTE_ADDR"];    $d = date('Y.m.d H:i:s');
    if (!isset($_SESSION['login'])) { $login = "������"; }    else { $login = $_SESSION['login']; }
    if (!isset($_SESSION['ip'])) { $ip1 = "������"; }    else { $ip1 = $_SESSION['ip']; }
    $tmp = "$name � IP $ip ������� ����� � ������ ������ $login (������ IP $ip1)";
    mysql_query("insert into adm_events (login,date_events,type_events,events) values('$login','$d','CRACK','$tmp')") or die(mysql_error());
    session_destroy();	header("Location: /");
    }
                                
$login=$_SESSION['login'];
$uid=$_SESSION['uid'];
$abl=mysql_select1("select levels.levelup_ability from levels,tbl_users where tbl_users.level=levels.id and tbl_users.id='$uid'");
if ( $abl>899 ) {$abl=599;}
if ( $_SESSION['uid']==60610) {$abl=1100;}

?>

<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1251">
<TITLE>��� "�������" - ������� ������ -> ������� ������</TITLE>
</head>

<LINK rel="stylesheet" type="text/css" href="/css/main.css">
<script>
<!--

//-->
</script>
<body>
<big><big><center><b>������� ������</b></center></big></big><br>
<form name="f" method="POST">
<input type=hidden name="cmd" value="">
<?
$msg="";
if(isset($arg_chid))
{
	$arg_chid=intval($arg_chid);
	if($arg_pass!=$arg_pass2){ $msg="������������� ������ �� ���������";$error=1;}
	else if(strlen($arg_pass)<3){$msg="������ ������ ���� �� ����� 3 ��������";$error=1;}
	else {
	mysql_query("update tbl_users set pass=md5('$arg_pass') where id='$arg_chid'") or die(mysql_error());
	$msg='������ �������';
	}
}
if(!isset($arg_login) && !isset($arg_nick) && !isset($arg_chid))
{
?><center>
��� ���� ����� �������� ���-�� ������� ������, ������� ���� ��� ����� ���� ��� ������.<p>
<table cellspacing=1 border=0>
<tr><td align=right>����� �� ����:</td><td><input type=text name="nick"></td><td rowspan=2 valign=middle><input type=submit value="������"></td></tr>
<tr><td align=right>����� �� ������:</td><td><input type=text name="login"></td></tr>
			<input type=hidden name='search' value=1>
</table>
<br>
<?
} else {
	if(isset($arg_nick) && strlen($arg_nick)>0 )
	{
	$zid=mysql_select1("select uid from nicks where nick='$arg_nick'");
//	echo "���";
	}
	else if(isset($arg_login))
	{
	$zid=mysql_select1("select id from tbl_users where login='$arg_login'");
//	echo "�����";
	}
	if(isset($arg_chid))
	$zid=$arg_chid;
	
	if(!isset($arg_chid) && !isset($arg_search))
	{
		echo "<center><big>������ �� �������</big></center><p>";
		?>
		<center>��� ���� ����� �������� ���-�� ������� ������, ������� ���� ��� ����� ���� ��� ������.<p>
		<table cellspacing=1 border=0>
		<tr><td align=right>����� �� ����:</td><td><input type=text name="nick"></td><td rowspan=2 valign=middle><input type=submit value="������"></td></tr>
		<tr><td align=right>����� �� ������:</td><td><input type=text name="login"></td></tr>
			<input type=hidden name='search' value=1>
		</table>
		<br>
		<?
	}
	else 
	{
		if(isset($zid)){ 
			if(!isset($msg))$msg="�������";
			echo "<center><big>$msg</big></center><p>";
			list($znick,$zlogin,$zlevel)=mysql_select1row("select a.last_nick,a.login,b.name from tbl_users a, level_names b where a.level=b.id and a.id='$zid' and b.gender='0'");
		}
		else 
		{
			list($znick,$zlogin,$zlevel)=mysql_select1row("select a.last_nick,a.login,b.name from tbl_users a, level_names b where a.level=b.id and a.id='$arg_chid' and b.gender='0'");
			echo "<center><big>$msg</big></center><p>";
		}
		?>
		<center>
		<table cellspacing=1 border=0>
		<tr><td align=right>�����:</td><td><?=$zlogin?></td></tr>
		<tr><td align=right>��������� ���:</td><td><?=$znick?></td></tr>
		<tr><td align=right>�������:</td><td><?=$zlevel?></td></tr>
		<?if(!isset($arg_chid)||isset($error)){?>
			<TR><TD align=right>����� ������:</TD><TD><INPUT TYPE="password" MAXLENGTH=16 SIZE=20 NAME="pass"></TD></TR>
			<TR><TD align=right>������������� ������:</TD><TD><INPUT TYPE="password" MAXLENGTH=16 SIZE=20 NAME="pass2"></TD></TR>
			<input type=hidden name='chid' value=<?=$zid?>>
			<TR><TD align=right colspan=2><INPUT TYPE="submit" value='��������'></TD></TR>
		<?}?>
		</table>
		<?
		
	}
?>
	

<?
}
?>
<center>
<input type=button value="��������" onclick="document.location.reload();">
<input type=button value="�������" onclick="window.close();">
</center>
</form>
<p>

<?

?>
