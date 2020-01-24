<?
session_start();
import_request_variables("gp", "arg_");
include "$BASE_DIR/inc/db_conn.php";
check_conn();

if ( !isset($_SESSION['ip']) || $_SESSION['ip']!=$_SERVER['REMOTE_ADDR'] || !isset($_SESSION['login']) || !isset($_SESSION['privs']['setting']) || $_SESSION['level']<1000 )
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
<TITLE>Чат "Тусовка" - Консоль админа -> Комнаты</TITLE>
</head>

<LINK rel="stylesheet" type="text/css" href="/css/main.css">
<script>
<!--

//-->
</script>
<body>
<big><big><center><b>Уровни</b></center></big></big><br>
<?
	if(isset($arg_delete))
	{
//		mysql_query("delete from channels where id='$arg_delete'") or die(mysql_error());
		$msg="Конал $arg_delete удален";
	}
	if(isset($arg_update))
	{
//		mysql_query("delete from levels where id='$arg_id' or id='$arg_oldid'") or die(mysql_error());
//		mysql_query("insert into levels (id,msg_len,nicks_count,invisibility,levelup_ability,kick_shield,kick_ability,replacements) values ('$arg_id','$arg_msg_len','$arg_nicks_count','$arg_invisibility','$arg_levelup_ability','$arg_kick_shield','$arg_kick_ability','$arg_replacements')") or die(mysql_error());
	}
	if(isset($arg_edit))
	{

		list($id,$msg_len,$nicks_count,$invisibility,$levelup_ability,$kick_shield,$kick_ability,$replacements)=mysql_select1row("select id,msg_len,nicks_count,invisibility,levelup_ability,kick_shield,kick_ability,replacements from levels where id='".mysql_escape_string($arg_edit)."'");
		$names=join(",",mysql_select1column("select concat(gender,':',name) from level_names where id='$id'"));
		$colors=join(",",mysql_select1column("select cpack from  level_colors where id='$id'"));
		?>
		<center>
		<form name="fedit" method="POST" action='/c2/admin/channels.php'>
		<table cellspacing=1 cellpadding=1 class=border>
		<tr><td align=right>id</td><td><input type=text name='id' value='<?=$id?>'></td></tr> <!--'<??> '-->
		<tr><td align=right>имена</td><td><input type=text name='names' size=40 value='<?=$names?>'></td></tr> <!--'<??> '-->
		<tr><td align=right>msg_len</td><td><input type=text name='msg_len' value='<?=$msg_len?>'></td></tr> <!--'<??> '-->
		<tr><td align=right>nicks_count</td><td><input type=text name='nicks_count' value='<?=$nicks_count?>'></td></tr> <!--'<??> '-->
		<tr><td align=right>invisibility</td><td><input type=text name='invisibility' value='<?=$invisibility?>'></td></tr><!--'<??> '-->
		<tr><td align=right>levelup_ability</td><td><input type=text name='levelup_ability' value='<?=$levelup_ability?>'></td></tr><!--'<??> '-->
		<tr><td align=right>kick_shield</td><td><input type=text name='kick_shield' value='<?=$kick_shield?>'></td></tr><!--'<??> '-->
		<tr><td align=right>kick_ability</td><td><input type=text name='kick_ability' value='<?=$kick_ability?>'></td></tr><!--'<??> '-->
		<tr><td align=right>colors</td><td><input type=text name='colors' value='<?=$colors?>'></td></tr><!--'<??> '-->
		<tr><td align=right>replacements</td><td><input type=text name='replacements' value='<?=$replacements?>'></td></tr><!--'<??> '-->
		
		</table>
		<input type=submit value='Изменить'>
		<input type=hidden name='update' value='1'>
		<input type=hidden name='oldid' value=<?=$id?>>
		
		</form>
		<?
		
	}
	else
	{
?>
<table cellspacing=1 cellpadding=1 class=border>
<?
$head="<tr>
	<td>ID</td>
	<td>Имя</td>
	<td>Тусуемся в</td>
	<td>Имя в IRC</td>
	<td>Нет Статы</td>
	<td>ReadL</td>
	<td>WriteL</td>
	<td>Смайлы</td>
	<td>Модер</td>
	<td>Move</td>
	<td>To</td>
	<td>Sens</td>
	<td>Save</td>
	<td>Owner</td>
	<td>&nbsp;</td>
</tr>";


	$req=mysql_query("select id,name2,name,irc_name,no_stat,read_level,write_level,smiles_allowed,
	moderated,move,move_to_channel,censored,save,owner     from channels order by id") or die(mysql_error());
	$n=0;
	while($row=mysql_fetch_row($req))
	{
		if(round($n%10)==0)
		echo $head;
		$n++;
		$id=		$row[0];
		$name2=		$row[1];
		$name=		$row[2];
		$irc_name=	$row[3];
		$no_stat=	$row[4];
		$read_level=	$row[5];
		$write_level=	$row[6];
		$smiles_allowed=$row[7];
		$moderated=	$row[8];
		$move=		$row[9];
		$move_to_channel=$row[10];
		$censored=	$row[11];
		$save=		$row[12];
		$owner=		$row[13];
		echo "<tr>
		<td>$n</td>
		<td><a href='/c2/admin/levels.php?edit=$id'>$id</a></td>
		<td>$names2</td>
		<td>$names</td>
		<td>$irc_name</td>
		<td>$no_stat</td>	
		<td>$read_level</td>
		<td>$write_level</td>
		<td>$smiles_allowed</td>
		<td>$moderated</td>
		<td>$move</td>
		<td>$move_to_channel</td>
		<td>$censored</td>
		<td>$save</td>
		<td>$owner</td>

		<td>
			<a href='/c2/admin/channels.php?delete=$id'><img src='/pics/del.gif' border=0></a>
		</td>
		</tr>";
	}
?>
</table>

<form method='post' name=fadd>
</form>
		<a href="#" onclick="getElementById('d_add').style.display='block';return false;">Добавить уровень</a>
		<div style="display: none" id='d_add'>

		<form name="fadd" method="POST" action='/c2/admin/levels.php'>
		<table cellspacing=1 cellpadding=1 class=border>
		<tr><td align=right>id</td><td><input type=text name='id' value=''></td></tr> 
		<tr><td align=right>имена</td><td><input type=text name='names' value=''></td></tr> 
		<tr><td align=right>msg_len</td><td><input type=text name='msg_len' value=''></td></tr>
		<tr><td align=right>nicks_count</td><td><input type=text name='nicks_count' value=''></td></tr>

		<tr><td align=right>invisibility</td><td><input type=text name='invisibility' value=''></td></tr>
		<tr><td align=right>levelup_ability</td><td><input type=text name='levelup_ability' value=''></td></tr>
		<tr><td align=right>kick_shield</td><td><input type=text name='kick_shield' value=''></td></tr>
		<tr><td align=right>kick_ability</td><td><input type=text name='kick_ability' value=''></td></tr>
		<tr><td align=right>colors</td><td><input type=text name='colors' value=''></td></tr>
		<tr><td align=right>replacements</td><td><input type=text name='replacements' value=''></td></tr>
		
		</table>
		<input type=submit value='Изменить'>
		<input type=hidden name='update' value='1'>
		<input type=hidden name='oldid' value=<?=$id?>>
		
		</form>
		</div>

<p>
<center>
<input type=button value="Закрыть" onclick="window.close();">
</center>
<p>
</form>
<?
     }
}
?>
