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
<TITLE>��� "�������" - ������� ������ -> ��� �����</TITLE>
</head>
<?

if(isset($arg_del_login))
    {
//    list($uid,$za,$adm_uid,$time_ban,$time_free)=mysql_select1row("select uid,descr,adm_uid,time_ban,time_free from banned_login where id='$arg_del_login'");
//    $tmp = "$uid $adm_uid $time_ban $time_free $za";
//    $d = date('Y.m.d H:i:s');
//    mysql_query("insert into adm_events (login,date_events,type_events,events) values('$login','$d','LOGIN_DEL','$tmp')") or die(mysql_error());
    mysql_query("delete from bans where id='$arg_del_login'") or die(mysql_error());
    }

$c_t = mktime();
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
    if ( $cur_base_lev <= intval($zlevel/100) )	{    $strerr="������ ��������"; }
    else
	{
	$req=mysql_query("select id from channels") or die(mysql_error());
	while($row=mysql_fetch_row($req))
	    {
	    $tvar = "arg_$row[0]";
	    $cc_t=$c_t+$arg_time_long;
	    if ( isset(${$tvar}) && ${$tvar} == 'on' ) 
		{
//		echo $tvar,"<br>",${$tvar},"<br>";
//	    $ch = mysql_select1("select name2 from channels where id='$row[0]'");     //     �����;
		$dct=date('Y.m.d H:i:s',$row[0]);
		$dlv=$_SESSION['level'];
		$tmp = "$zlogin ������� $row[0] �� $time_cnt �� $arg_za_set";
		mysql_query("insert into adm_events (login,date_events,type_events,events) values('$login','$d','KLAP_SET','$tmp')") or die(mysql_error());
$tid=	mysql_select1("select MAX(id) from bans"); $tid++;
    		mysql_query("insert into bans (id,type,uid,descr,ip,time_cnt_str,time_ban_start,time_ban_end,adm_name,user_name) 
    		values('$tid','$zid','$c_t','$cc_t','$arg_za_set','$uid','$time_cnt','$dct','$dlv','zlevel')") or die(mysql_error());
		$stderr="����� $zlogin ������������";
		}
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
<big><big><center><b>�����</b></center></big></big><br>


<table width=100% cellspacing=1 cellpadding=5 class=border>
<?
$head="<tr>
	<td><center>�����</center></td>
	<td><center>�������</center></td>
	<td><center>����</center></td>
	<td><center>�� �������</center></td>
	<td><center>����� �������� ����</center></td>
	<td><center>���</center></td>
	<td><center>�����������</center></td>
	<td><center>�����</center></td>
	</tr>";

	echo $c_t," ",date('Y.m.d H:i:s',$c_t);;

	echo $head;

	$req=mysql_query("select id,type,uid,adm_uid,channel,descr,ip,time_cnt_str,time_ban_start,time_ban_end,adm_name,user_name,alevel,ulevel from bans where descr > '$c_t' order by descr") or die(mysql_error());
	$numb=0;
	while($row=mysql_fetch_row($req))
	    {
	    $numb++;
	    $bid=	$row[0];
	    $zid=	$row[1];
	    $aid=	$row[7];
	    $ch=	strtotime($row[9]);
	    $channel=   	
	    mysql_select1("select name2 from channels where id='$ch'");     //     �����;
	    $time_ban=	date('Y.m.d H:i:s',$row[2]);
//	    $time_cnt=	$row[5];
//	    $time_cnt=	strtotime($row[8]);
//$row[8];
	    $time_free=	date('Y.m.d H:i:s',$row[5]);
//	    $time_free=	$row[5];
//$row[5];
	    $za=	$row[6];
	    $dis="";

    	    list($login_ban,$login_ban_last)=mysql_select1row("select login,last_nick from tbl_users where id='$zid'");
    	    list($login_ban_auth,$login_ban_level,$adm_ln)=mysql_select1row("select login,level,last_nick from tbl_users where id='$aid'");
                $login_ban_level = intval ($login_ban_level/100);

            if ($cur_base_lev>$login_ban_level || $login_ban_auth==$login || $_SESSION['level']==1000 )
        	{  $str_but = " class=tdrk><center> <input type=button value=\"�����\" onclick=\"location.href='/c2/admin/klap.php?del_login=".$bid."'\"$dis></center>";                }
            else
        	{  $str_but = " "; }
	
    $t = ($row[5]-$row[2]) / 60;
    if ( $t<60 ) $time_cnt = $t." �";
    else {	$t /= 60;
	if ( $t<24 ) $time_cnt = $t." �";
	else {	    $t /= 24;
	    if ( $t<7 ) $time_cnt = $t." ��";
	    else {	$t /= 7;	$time_cnt = $t." ��";	}
	     }
	  }
	
	    echo "<tr>
	    <td><right><a href='/c2/chat_userinfo2.php?id=$zid' target=_blank>$login_ban_last($login_ban)</a></right></td>
	    <td><center>$channel</center></td>
	    <td><right>$time_ban</right></td>
	    <td><center>$time_cnt</center></td>
	    <td>$time_free</td>
	    <td><right>$adm_ln($login_ban_auth)</right></td>
	    <td>$za</td>
	    <td $str_but</td></tr>";
	    }
	    
//method="POST"	    
?>

</table>
<br>
<left>
<form name=login_add  action="/c2/admin/klap.php">
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
<td rowspan=3 valign=middle> <input type=submit value="OK" style="width: 2em" onclick="location.href=/c2/admin/klap.php" </td>
</tr>

<tr> <td align=right>��� �� ������:</td><td><input type=text name="login" maxlen=18 size=18 style="height: 19></td><td></td><td></td></tr>

<td align=right> &nbsp; ����������� <input type=text name="za_set" maxlen=30 size=30 style="height: 19"> </td>

</table>

<table>

<?
	$req=mysql_query("select channel from moderators where uid = '$uid' order by channel") or die(mysql_error());
$che=0;
$old_ch=0;
	while($row=mysql_fetch_row($req))
	    {
$che++;
	    $ch = mysql_select1("select name2 from channels where id='$row[0]'");     //     �����;
	    if($row[0] != $old_ch)
	      {
	    if ($che==1) 
		{	echo "<tr><td>�������</td><td>$ch</td><td>    <input id='$row[0]' type=checkbox name='$row[0]' class=c_b>    </td></tr>";    }
	    else
		{	echo "<tr><td></td><td>$ch</td><td>    <input id='$row[0]' type=checkbox name='$row[0]' class=c_b>    </td></tr>";    }
	      $old_ch=$row[0];
	      }
	    }	

/*
	if($row=mysql_fetch_row($req))
	    {
	    $ch = mysql_select1("select name2 from channels where id='$row[0]'");     //     �����;
	    echo "<tr><td></td><td>$ch</td><td>
	    <input id=kch2 type=checkbox name=kch2 class=c_b>
	    </td></tr>";
	    }                                  

*/

/*<td class=r><input id=hide_name type=checkbox name=hide_name class=c_b <?if($hide_name) echo "CHECKED" ?> >
 <label for=hide_name>������ ���</label></td>
*/                                  
?>

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
<form name=login_add_rl method="POST" action="/c2/admin/klap.php">
<input type=submit value="��������" onclick="location.href=/c2/admin/klap.php">
<form name=login_add method="POST" action="/c2/admin/klap.php">
</form>
<input type=button value="�������" onclick="window.close();">
</center>
<p>
</form>
<?
}
?>


