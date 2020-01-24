<?
	session_start();
        import_request_variables("gp", "arg_");
	include "$BASE_DIR/inc/db_conn.php";
	include "$BASE_DIR/inc/make_user_info.php";
	include "$BASE_DIR/inc/date.php";
	check_conn();
     if(isset($_SESSION['uid']))
     {
     	$login=$_SESSION['login'];
	$uid=intval($_SESSION['uid']);
	
     }
     if(!isset($login) || $_SESSION['level']<800)
     {
     	header("Location: /");
     }
     else
     {
?>
<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=UTF-8">
<TITLE>Чат "Тусовка" - Консоль админа -> Информация о логине</TITLE>
</head>

<LINK rel="stylesheet" type="text/css" href="/css/main.css">
<script>
<!--
var uf=0;
function do_f(id)
{
        var r=Math.random();
	locat='/userphotos/'+id;
	sx=screen.width/3*2;
	sy=screen.height/5*4;
	if(!uf || uf.closed)
	{
		uf=open(locat,'uf','toolbar=0,status=0,resizable=1,scrollbars=1,width='+sx+',height='+sy);
	}
	else
	{
		uf.focus();
		uf.location=locat;
	}	
//	return true;
}
//-->
</script>
<BODY>
<hr width=100% size=2>
<table cellspacing=1 cellpadding=1 border=0>
<?
	$zid=0;
	if(isset($arg_id)) $zid=intval($arg_id);
	else
	{
		if(isset($arg_login)) 
		{
				$zid=mysql_select1("select id from tbl_users where login='".mysql_escape_string($arg_login)."'");
		}	
	}
	if($zid==0)
	echo "<script>alert('Логин не найден');window.close();</script>\n";
	list($zlevel,$zlogin,$zlast_nick,$zlast_nick_id,$zinfo,$zstat_m_count,$zstat_t_count,$zstat_v_count,$zkick_count,$zkicked_count,$zreg_date,$zstat_last_date,$zstat_last_ip,$zpoweshen,$zcredit_summa,$zbought_invisibility,$zvote_balls)=
	mysql_select1row("select level,login,last_nick,last_nick_id,info,stat_m_count,stat_t_count,stat_v_count,kick_count,kicked_count,reg_date,stat_last_date,stat_last_ip,poweshen,credit_summa,bought_invisibility,vote_balls from tbl_users where id='$zid'");
?>
<tr><td align=right>Логин:</td><td><font class=infd><b><?=$zlogin?></b></td></tr>
<tr><td align=right>ID:</td><td><font class=infd><?=$zid?></td></tr>
<tr valign=top><td align=right>Ники:</td><td><font class=infd><?


	if($_SESSION['level']<800)
	 echo mysql_select1("select count(*) from nicks where uid='$zid'")." шт.";
	else
	{
		echo join(", ",mysql_select1column("select nick from nicks where uid='$zid' order by nick"));
	} 
?></td></tr>
<?
// echo make_user_info($zlast_nick_id,true);
?>
<tr valign=top><td align=right>Последний_ник:</td><td><font class=infd><?=$zlast_nick?></td></tr>
<?
//	if(strlen($zinfo)){ echo $zinfo."<hr>";}
?>

<tr><td align=right>Сообщений: </td><td><font class=infd><?=$zstat_m_count?></td></tr>
<tr><td align=right>Время в чате: </td><td><font class=infd><?=$zstat_t_count?></td></tr>
<tr><td align=right>Кол-во заходов: </td><td><font class=infd><?=$zstat_v_count?></td></tr>
<tr><td align=right>Сообщений в час: </td><td><font class=infd><?=$zstat_m_count/(1+$zstat_t_count/3600)?></td></tr>
<tr><td align=right>Кикнул: </td><td><font class=infd><?=$zkick_count?></td></tr>
<tr><td align=right>Кикнули: </td><td><font class=infd><?=$zkicked_count?></td></tr>
<tr><td align=right>Дата регистрации: </td><td><font class=infd><?=get_rusdate($zreg_date)." ".get_time($zreg_date)?></td></tr>
<tr><td align=right>Последний раз был(а): </td><td><font class=infd><?=get_rusdate($zstat_last_date)." ".get_time($zstat_last_date)?></td></tr>
<tr><td align=right>Прошлый АйПи: </td><td><font class=infd><?=$zstat_last_ip?></td></tr>
<tr><td align=right>Уровень_изменен: </td><td><font class=infd><? 
	if($zpoweshen==0) echo "VOTE"; else if($zpoweshen==-1) echo "Куплен"; else if($zpoweshen==-2) echo "Голосованием";else echo mysql_select1("select login from tbl_users where id='$zpoweshen'")
?></td></tr>
<tr><td align=right>Кредитов: </td><td><font class=infd><?=$zcredit_summa?></td></tr>
<tr><td align=right>Невидимость_(купленная):</td><td><font class=infd><?=$zbought_invisibility?></td></tr>
<tr><td align=right>Баллов голосовки: </td><td><font class=infd><?=$zvote_balls?></td></tr>
<tr><td align=right>Уровень: </td><td><font class=infd><?=mysql_select1("select id from levels where id='$zlevel'")?></td></tr>

<tr><td colspan=2 align=center><br><a href="javascript: window.close()">Закрыть<br><br></td></tr>
</table>
<p>
</center>
     
<?
include "c2/banners/tbe.php";
include "c2/banners/metka_catalog.php";
?>

     
<?
     }

?>
