<?
session_start();
import_request_variables("gp", "arg_");
include "inc/db_conn.php";
check_conn();

if ( !isset($_SESSION['ip']) || $_SESSION['ip']!=$_SERVER["REMOTE_ADDR"] || !isset($_SESSION['login']) || !(($_SESSION['level']>=800) || isset($_SESSION['privs']['oldban']))) //|| $_SESSION['level'])!=1000
    {
    $name = $_SERVER["SCRIPT_FILENAME"];
    $ip = $_SERVER["REMOTE_ADDR"];    $d = date('Y.m.d H:i:s');
    if (!isset($_SESSION['login'])) { $login = "������"; }    else { $login = $_SESSION['login']; }
    if (!isset($_SESSION['ip'])) { $ip1 = "������"; }    else { $ip1 = $_SESSION['ip']; }
    $tmp = "$name � IP $ip ������� ����� � ������ ������ $login (������ IP $ip1)";
    mysql_query("insert into adm_events (login,date_events,type_events,events) values('$login','$d','CRACK','$tmp')") or die(mysql_error());
    session_destroy();  header("Location: /");
    }
else
    {
    $login=$_SESSION['login'];
    $uid=$_SESSION['uid'];
    $cur_base_lev = intval($_SESSION['level']/100);
?>
<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1251">
<TITLE>��� "�������" - ������� ������ -> ��� �������</TITLE>
</head>
<?

if(isset($arg_del_login))
    {
    list($uid,$za,$adm_uid,$time_ban,$time_free)=mysql_select1row("select uid,descr,adm_uid,time_ban,time_free from banned_login where id='$arg_del_login'");
    $tmp = "$uid $adm_uid $time_ban $time_free $za";
    $d = date('Y.m.d H:i:s');
    mysql_query("insert into adm_events (login,date_events,type_events,events) values('$login','$d','LOGIN_DEL','$tmp')") or die(mysql_error());
    mysql_query("delete from banned_login where id='$arg_del_login'") or die(mysql_error());
    }


$zid=0;
$msg="";
if(isset($arg_nick) && strlen($arg_nick)>0 )
    {
    $zid=mysql_select1("select uid from nicks where nick='$arg_nick'");     //      echo "���";    
        if( $zid < 2 )    	{    $strerr="��� �� ������"; }
    }
if(isset($arg_login) && strlen($arg_login)>0 )
    {
    $zid=mysql_select1("select id from tbl_users where login='$arg_login'");     //      echo "�����";
        if( $zid < 2 )	{    $strerr="����� �� ������"; }
    }
if( $zid>0 && strlen($arg_za_set)<1)
	{    $strerr="������ ���� �����������"; $zid=0; }
if( $zid>1 )
    {
    $d = date('Y.m.d H:i:s');
    $time_free = date('Y.m.d H:i:s',time()+$arg_time_long);
    $t = $arg_time_long / 60;
    if ( $t<60 ) $time_cnt = $t." �";
    else {	$t /= 60;
	if ( $t<24 ) $time_cnt = $t." �";
	else {	    $t /= 24;
	    if ( $t<7 ) $time_cnt = $t." ��";
	    else {	$t /= 7;	$time_cnt = $t." ��";	}
	     }
	  }

    list($zlogin,$zlevel)=mysql_select1row("select login,level from tbl_users where id='$zid'");
    if ( $cur_base_lev <= intval($zlevel/100) )
	{    $strerr="������ ��������"; }
    else
	{
	$ttt=mysql_select1("select id from banned_login where login='$zlogin'");     //      echo "�����";
	if ( $ttt> 0 )
	  {    $strerr="����� ��� �������"; }
	else
	    {
	    $tmp = "$zlogin $d $time_cnt $arg_za_set";
	    mysql_query("insert into adm_events (login,date_events,type_events,events) values('$login','$d','LOGIN_SET','$tmp')") or die(mysql_error());
    	    mysql_query("insert into banned_login (login,time_ban,time_free,time_cnt,uid,descr,adm_uid) values('$zlogin','$d','$time_free','$time_cnt','$zid','$arg_za_set','$uid')") or die(mysql_error());
	    $msg="����� $zlogin ������������";
	    }
	}
    }
		
if (!isset($strerr))     {   $strerr="";        }
echo "<center><b> <font class='yelmsg'>".$strerr."</font></b></center>";
$strerr="";


?>
<LINK rel="stylesheet" type="text/css" href="/css/main.css">
<script>
<!--

//-->
</script>
<body>
<big><big><center><b>��� �������</b></center></big></big><br>


<table width=100% cellspacing=1 cellpadding=5 class=border>
<?
$head="<tr>
	<td><center>�����</center></td>
	<td><center>����</center></td>
	<td><center>�� �������</center></td>
	<td><center>����� �������� ����</center></td>
	<td><center>���</center></td>
	<td><center>�����������</center></td>
	<td><center>�����</center></td>
	</tr>";

	echo $head;
	$req=mysql_query("select uid,time_ban,time_cnt,time_free,descr,adm_uid,id from banned_login order by time_free") or die(mysql_error());
	$numb=0;
	while($row=mysql_fetch_row($req))
	    {
	    $numb++;
    	    list($login_ban,$login_ban_last)=mysql_select1row("select login,last_nick from tbl_users where id='$row[0]'");
	    $id=	$row[6];
	    $time_ban=	$row[1];
	    $time_cnt=	$row[2];
	    $time_free=	$row[3];
	    $za=	$row[4];
	    $dis="";
    	    list($login_ban_auth,$login_ban_level)=mysql_select1row("select login,level from tbl_users where id='$row[5]'");
                $login_ban_level = intval ($login_ban_level/100);
            if ($cur_base_lev>$login_ban_level || $login_ban_auth==$login || $_SESSION['level']==1000 )
        	{
                $str_but = " class=tdrk><center> <input type=button value=\"�����\" onclick=\"location.href='/c2/admin/login_ban.php?del_login=".$id."'\"$dis></center>";
                }
            else
        	$str_but = " ";

		
	
	    echo "<tr>
	    <td><right><a href='/c2/chat_userinfo2.php?id=$row[0]' target=_blank>$login_ban_last($login_ban)</a></right></td>
	    <td><right>$time_ban</right></td>
	    <td><center>$time_cnt</center></td>
	    <td>$time_free</td>
	    <td><right>$login_ban_auth</right></td>
	    <td>$za</td>
	    <td $str_but</td></tr>";
	    }
?>

</table>
<br>
<left>
<form name=login_add method="POST" action="/c2/admin/login_ban.php">
<table cellspacing=1 border=0>
<tr><td align=right>��� ������ �� ����:</td><td><input type=text name="nick" maxlen=18 size=18 style="height: 19"></td>
<td rowspan=3 valign=middle align=right> ����������� <input type=text name="za_set" maxlen=30 size=30 style="height: 19"> </td>
<td rowspan=3 valign=middle>    ��  <select name=time_long>
	<option value=60>1 ������
	<option value=300 SELECTED>5 �����
	<option value=600>10 �����
	<option value=1200>20 �����
	<option value=1800>30 �����
	<option value=3600>1 ���
	<option value=7200>2 ����
	<option value=21600>6 �����
	<option value=43200>12 �����
	<option value=86400>1 ����
	<option value=172800>2 ���
	<option value=604800>1 ������
	<option value=1209600>2 ������
	</select>
</td>
<td rowspan=3 valign=middle> <input type=submit value="OK" style="width: 2em" onclick="location.href=/c2/admin/login_ban.php" </td>
</tr>

<tr> <td align=right>��� �� ������:</td><td><input type=text name="login" maxlen=18 size=18 style="height: 19></td><td></td><td></td></tr>

<td align=right> &nbsp; ����������� <input type=text name="za_set" maxlen=30 size=30 style="height: 19"> </td>

</table>
                                                                
<br><br>
����� <?=$numb ?>  ��������� �����a(��). <br><br>
<big><big> ������� </big></big> <br><br>
����� ��������� ����� ���� ������ ���, ��� ����� � ����������� � ����.<br>
����� ���������� ���� �� ������, �������� �� �����.<br>
���� ���� �������� ���������, �� ���� ������� ������ "��������" (�����)<br>
����� ���������� �����, ���� ������ �� ������ ���� ������ "�����"<br><br>

	
<p>
<center>
<form name=login_add_rl method="POST" action="/c2/admin/login_ban.php">
<input type=submit value="��������" onclick="location.href=/c2/admin/login_ban.php">
<form name=login_add method="POST" action="/c2/admin/login_ban.php">
</form>
<input type=button value="�������" onclick="window.close();">
</center>
<p>
</form>
<?
}
?>


