<?
session_start();
header("Content-Type: text/html; charset=\"windows-1251\"");
import_request_variables("gp", "arg_");
	
include "inc/db_conn.php";
include "inc/str_nick.php";
check_conn();
 if(isset($_SESSION['uid']))
    {
    $uid=$_SESSION['uid'];
    $login=$_SESSION['login'];
    }
if(!isset($uid))
    {    header("Location: /");die;    }
$credits=mysql_select1("select credit_summa from tbl_users where id='$uid'");
//if ( !($credits < 200000 || $uid==60610 || $uid==203509 || $uid==26 || $uid==449687 ) )
//    {	echo "<h1>��� �� ������ N!2</h1>";  die;     }
$summa=abs($arg_summa);
mysql_query("set charset utf8");
$r=mysql_select1("select id  from nicks where nick='$arg_nick'");
mysql_query("set charset cp1251");
list($zid,$nick)=mysql_select1row("select uid,nick from nicks where id='$r'");
if(!isset($zid))
    {	echo "<h3>��� �� ������</h3>";	}
else
    {
    $sum=mysql_select1("select credit_summa from tbl_users where id='$uid'");
    if(
    //(
    $sum<$summa
    //)||($_SESSION['ip']=='95.174.210.204')||($_SESSION['ip']=='95.174.214.22')
    )	    
    {
    	    echo  "<h3>������������ ������� �� �����</h3>";		
    }
    else
	{
	mysql_query("update tbl_users set credit_summa=credit_summa-$summa where id='$uid'") or die(mysql_error().__FILE__.__LINE__);
	mysql_query("update tbl_users set credit_summa=credit_summa+$summa where id='$zid'") or die(mysql_error().__FILE__.__LINE__);
	echo  "<h3>� ������ ����� ������� $summa �������� � ������ $nick</h3>";
	mysql_query("insert into ext_events (event) values ('cmd=flush obj=tbl_users uid=$uid')") or die(mysql_error().__FILE__.__LINE__);
	mysql_query("insert into ext_events (event) values ('cmd=flush obj=tbl_users uid=$zid')") or die(mysql_error().__FILE__.__LINE__);
	mysql_query("insert into ext_events (event,d1) values ('cmd=sysmsg uid=$zid','��� ����������� $summa �������� �� $login')") or die(mysql_error().__FILE__.__LINE__);
	mysql_query("insert into ext_events (event,d1,d2) values ('cmd=systemnote uid=$zid','������������ ��������','��� ����������� $summa �������� �� $login')") or die(mysql_error().__FILE__.__LINE__);
	$d=date('Y-m-d H:i:s');
	mysql_query("insert into cr_transfer (fromid,toid,summa,date_transf) values ('$uid','$zid','$summa','$d')") or die(mysql_error().__FILE__.__LINE__);
	}
    }
?>
