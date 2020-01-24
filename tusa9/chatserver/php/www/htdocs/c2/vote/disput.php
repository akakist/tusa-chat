<?
session_start();
import_request_variables("gp", "arg_");
include "inc/db_conn.php";
include "inc/date.php";
check_conn();
//    if(!isset($_SESSION['login']) || !isset($arg_id) || !isset($_SESSION['uid'])) {         header("Location: /");     }
$login=$_SESSION['login'];
$uid=$_SESSION['uid'];
if ( mysql_select1("select vote_balls from tbl_users where id=$uid") < 1 )  {       header("Location: /");     }
$adm_vote=0;  
if (isset($_SESSION['privs']['vote']))      {       $adm_vote=1;    } 
$main_nick=mysql_select1("select last_nick from tbl_users where id='$uid'");


function nick_select($uid)
{
$out="";
$out.='<select name="main_nick">';
                
$nid=mysql_select1("select last_nick_id from tbl_users where id='$uid'");
$res=mysql_query("select id,nick from nicks where uid='$uid' order by 2") or die(mysql_error());
while($r=mysql_fetch_row($res))
    {
    $ssid=$r[0];
    $n=$r[1];
    if($nid==$ssid)   	$out.="<option value=$ssid selected> $n\n";
    else		$out.= "<option value=$ssid> $n\n";
    }
$out.=" </select>";
return $out;
}




?>
<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1251">
<TITLE>Чат "Тусовка" - Голосование -> Информация о кандидате</TITLE>
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
<big><big><center><b>Информация о кандидате</b></center></big></big>
    <hr width=100% size=2>
    <table cellspacing=1 cellpadding=1 border=0>
<?
	$zid=0;
	if(isset($arg_id)) $zid=intval($arg_id);
	$vid=mysql_select1("select id from grant_vote where uid='$zid'");
	if($vid==0)
	echo "<script>alert('Логин не найден');window.close();</script>\n";
        $read=mysql_select1("select readden from grant_readden where uid='$uid' and gid='$vid'");
        if ( $read != 1 ) 
    	    {
	    mysql_query("insert into grant_readden values( 1, '$uid' ,'$vid' )") or die(mysql_error());
    	    }

if(isset($arg_msg) && strlen($arg_msg)>0 ) 
    {
    $d = date('Y.m.d H:i:s');
    if(isset($arg_hide_nick)) { $h=0; } else { $h=1; }
//    echo $vid,"<br>",$main_nick,"<br>",$_SERVER["REMOTE_ADDR"],"<br>",$arg_msg,"<br>",$d,"<br>",$h,"<br>";
    $ip=$_SERVER["REMOTE_ADDR"];
    if ( !isset($_SESSION['last_msg']) || strcmp($_SESSION['last_msg'], $arg_msg)!=0 )
	{
	$_SESSION['last_msg']=$arg_msg;
	mysql_query("insert into grant_messages (gid,from_nick,ip,msg,add_date,show_nick) 
	    values('$vid', '$main_nick', '$ip' ,'$arg_msg','$d','$h')") or die(mysql_error());

	mysql_query("delete from grant_readden where uid!='$uid' and gid='$vid'") or die(mysql_error());
	
         
//        $read=mysql_select1("select readden from grant_readden where uid='$uid' and gid='$vid'");
//     header("Location: /c2/vote/disput.php?id=$arg_id");
	}
    }


	list($zlevel,$zlogin,$zlast_nick,$zlast_nick_id,$zinfo,$zstat_m_count,$zstat_t_count,$zstat_v_count,$zkick_count,$zkicked_count,$zreg_date,$zstat_last_date,$zstat_last_ip,$zpoweshen,$zcredit_summa,$zbought_invisibility,$zvote_balls)=
	mysql_select1row("select level,login,last_nick,last_nick_id,info,stat_m_count,stat_t_count,stat_v_count,kick_count,kicked_count,reg_date,stat_last_date,stat_last_ip,poweshen,credit_summa,bought_invisibility,vote_balls from tbl_users where id='$zid'");
?>
<tr><td align=right>Логин:</td><td><font class=infd><b><?=$zlogin?></b></td></tr>
<tr><td align=right>ID:</td><td><font class=infd><?=$zid?></td></tr>
<tr valign=top><td align=right>Ники:</td><td><font class=infd><?


//	if($_SESSION['level']<1000)
//	 echo mysql_select1("select count(*) from nicks where uid='$zid'")." шт.";
//	else
//	{
		echo join(", ",mysql_select1column("select nick from nicks where uid='$zid' order by nick"));
//	} 
?></td></tr>
<tr valign=top><td align=right>Последний_ник:</td><td><font class=infd><?=$zlast_nick?></td></tr>
<tr><td align=right>Сообщений: </td><td><font class=infd><?=$zstat_m_count?></td></tr>
<tr><td align=right>Время в чате: </td><td><font class=infd><?=sprintf("%2.2f",$zstat_t_count/3600)?></td></tr>
<tr><td align=right>Кол-во заходов: </td><td><font class=infd><?=$zstat_v_count?></td></tr>
<tr><td align=right>Сообщений в час: </td><td><font class=infd><?=$zstat_m_count/($zstat_t_count/3600)?></td></tr>
<tr><td align=right>Кикнул: </td><td><font class=infd><?=$zkick_count?></td></tr>
<tr><td align=right>Кикнули: </td><td><font class=infd><?=$zkicked_count?></td></tr>
<tr><td align=right>Дата регистрации: </td><td><font class=infd><?=get_rusdate($zreg_date)." ".get_time($zreg_date)?></td></tr>
<tr><td align=right>Последний раз был(а): </td><td><font class=infd><?=get_rusdate($zstat_last_date)." ".get_time($zstat_last_date)?></td></tr>
<tr><td align=right>Прошлый АйПи: </td><td><font class=infd><?=$zstat_last_ip?></td></tr>
<tr><td align=right>Уровень_изменен: </td><td><font class=infd><? 
	if($zpoweshen==0) echo "VOTE";
	else if($zpoweshen==-1) echo "Куплен";
	else if($zpoweshen==-2) echo "Голосованием";
	else echo mysql_select1("select login from tbl_users where id='$zpoweshen'")
?></td></tr>
<tr><td align=right>Кредитов: </td><td><font class=infd><?=sprintf("%2.2f",$zcredit_summa)?></td></tr>
<tr><td align=right>Невидимость_(купленная):</td><td><font class=infd><?=sprintf("%2.2f",$zbought_invisibility)?></td></tr>
<tr><td align=right>Баллов голосовки: </td><td><font class=infd><?=$zvote_balls?></td></tr>
<tr><td align=right>Уровень: </td><td><font class=infd><?=$zlevel?></td></tr>
<?
$zautor=mysql_select1("select add_by from grant_vote where uid='$zid'");
?>

<tr><td align=right>Поставил на голосование: </td><td><font class=infd><?=mysql_select1("select login from tbl_users where id='$zautor'")?></td></tr>

</table>
<p>
</center>
<hr width=100% size=3>
<?

$tmp = mysql_query("select from_nick,ip,msg,add_date,show_nick  from grant_messages where gid=$vid order by add_date" ) or die(mysql_error());
while ( $v_m=mysql_fetch_row($tmp) )
    {
    $str=get_rusdate($v_m[3])." ".get_time($v_m[3])."<br>";
    if ($v_m[4]==1 || $adm_vote) { $str .= " $v_m[0] "; }    
    if ( $adm_vote) { $str .= "<small> ($v_m[1])</small>"; }
/*<font class=nick id='au<?=$mid?>'><?=$author?></font> 
*/
//    if ($adm_vote) { $str .= "<small>".$v_m[1]."</small>"; }
    $str .="<br>".$v_m[2]."<br>";
    echo $str;
?>
<hr width=100% size=3>     
<?
    }
//$str_yes = "За ";
//$str_no = "Против ";
$str_yes = "";
$str_no = "";
$yes =0;
$no=0;
$tmp = mysql_query("select uid,yes,no  from grant_agrees where gid=$vid" ) or die(mysql_error());
while ( $v_m=mysql_fetch_row($tmp) )
    {
    $yes += $v_m[1];
    $no += $v_m[2];
    if ($v_m[1]>0) 
	{ 
	if ( strlen($str_yes)>2) { $str_yes .=", "; }
	$str_yes .= mysql_select1("select login from tbl_users where id='$v_m[0]'"); 
	}
    if ($v_m[2]>0) 
	{ 
	if ( strlen($str_no)>2) { $str_no .=", "; }
	$str_no .= mysql_select1("select login from tbl_users where id='$v_m[0]'"); 
	}
    }
/*
<? echo 'CHECKED'?>
<input type=hidden name="main_nick" value="$main_nick">От: <?=nick_select($uid)?>
<form name=add_vote action="/c2/vote/disput.php">
    
?>
*/
?>

<center>
<form method=post name=add_vote action="">
<br>
<textarea style='width: 450px' rows=8 cols=56 name="msg" maxlength=1024></textarea><br><br>
<input type="hidden" name="id" value="<?=$arg_id?>">
<br>
<class=r><input type=checkbox id=hide_nick name=hide_nick class=c_b > <label for=hide_nick>Скрыть ник</label>
<input type=submit value="Добавить сообщение" >
</center>
</form>

<?
/*

//<class=r><input type=checkbox id=hide_nick name=hide_nick class=c_b > <label for=hide_nick>Скрыть ник</label>
//<class=tdrk><center> <input type=button value="Добавить сообщение"
// onclick="add_vote_msg(<?=.$arg_id,$msg,$hide_nick.?>);"></center>
*/
?>

<?                                                                                                                                                                                                                     
    if ($adm_vote>0)
	{
	$str_yes .=" (".$yes."%)<br>";
	$str_no  .=" (".$no."%)<br>";

?>
<hr width=100% size=3>     
</center>
<br>
    <table cellspacing=1 cellpadding=1 border=0>
<tr><td> За: </td><td><font class=vyes><?=$str_yes?></td></tr>
<tr><td>Против: </td><td><font class=vno><?=$str_no?></td></tr>
<?
//	echo $_POST;

//	echo $str_yes." (".$yes."%)<br>";
//	echo $str_no." (".$no."%)<br>";
	}
?>
</table>
<center>
<br><br>
<a href=# onclick="window.close();">Закрыть</a>
<br><br>
</center>
<?
?>
