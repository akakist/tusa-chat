<?
session_start();
import_request_variables("gp", "arg_");
include "$BASE_DIR/inc/db_conn.php";
check_conn();

if ( !isset($_SESSION['ip']) || $_SESSION['ip']!=$_SERVER['REMOTE_ADDR'] || !isset($_SESSION['login']) || $_SESSION['level']!=1000 ) //|| $_SESSION['level'])!=1000
    {
    $name = $_SERVER["SCRIPT_FILENAME"];
    $ip = $_SERVER["REMOTE_ADDR"];    $d = date('Y.m.d H:i:s');
    if (!isset($_SESSION['login'])) { $login = "ПУСТОЙ"; }    else { $login = $_SESSION['login']; }
    if (!isset($_SESSION['ip'])) { $ip1 = "ПУСТОЙ"; }    else { $ip1 = $_SESSION['ip']; }
    $tmp = "$name С IP $ip попытка войти в сессию логина $login (старый IP $ip1)";
    mysql_query("insert into adm_events (login,date_events,type_events,events) values('".mysql_escape_string($login)."','$d','CRACK','$tmp')") or die(mysql_error());
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
<TITLE>Чат "Тусовка" - Консоль админа -> Уровни</TITLE>
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
		mysql_query("delete from levels where id='$arg_delete'") or die(mysql_error());
		mysql_query("delete from level_names where id='$arg_delete'") or die(mysql_error());
		mysql_query("delete from level_colors where id='$arg_delete'") or die(mysql_error());
		$msg="Уровень $arg_delete удален";
	}
	if(isset($arg_update))
	{
		mysql_query("delete from levels where id='$arg_id' or id='$arg_oldid'") or die(mysql_error());
		mysql_query("insert into levels (id,msg_len,nicks_count,invisibility,levelup_ability,kick_shield,kick_ability,replacements) values ('$arg_id','$arg_msg_len','$arg_nicks_count','$arg_invisibility','$arg_levelup_ability','$arg_kick_shield','$arg_kick_ability','$arg_replacements')") or die(mysql_error());
		mysql_query("delete from level_names where id='$arg_id' or id='$arg_oldid'") or die(mysql_error());
		mysql_query("delete from level_colors where id='$arg_id' or id='$arg_oldid'") or die(mysql_error());
		$r=split(",",$arg_names);
		foreach($r as $n)
		{
			$rr=split(":",$n);
			$name=$rr[1];
			$g=$rr[0];
			mysql_query("insert into level_names (id,name,gender) values('$arg_id','$name','$g')") or die(mysql_error());
		}

		$r=split(",",$arg_colors);
		foreach($r as $n)
		{
			mysql_query("insert into level_colors (id,cpack) values('$arg_id','$n')") or die(mysql_error());
		}
	}
	if(isset($arg_edit))
	{

		list($id,$msg_len,$nicks_count,$invisibility,$levelup_ability,$kick_shield,$kick_ability,$replacements)=mysql_select1row("select id,msg_len,nicks_count,invisibility,levelup_ability,kick_shield,kick_ability,replacements from levels where id='$arg_edit'");
		$names=join(",",mysql_select1column("select concat(gender,':',name) from level_names where id='$id'"));
		$colors=join(",",mysql_select1column("select cpack from  level_colors where id='$id'"));
		?>
		<center>
		<form name="fedit" method="POST" action='/c2/admin/levels.php'>
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
	<td>N</td>
	<td>ID</td>
	<td>Имена</td>
	<td>msglen</td>
	<td>nicks</td>
	<td>invis</td>
	<td>levelup</td>
	<td>kick_shield</td>
	<td>kick_ability</td>
	<td>colors</td>
	<td>repls</td>
	<td>&nbsp;</td>
	<td>&nbsp;</td>
</tr>";


	$req=mysql_query("select id,msg_len,nicks_count,invisibility,levelup_ability,kick_shield,kick_ability,replacements from levels order by id") or die(mysql_error());
	$n=0;
	while($row=mysql_fetch_row($req))
	{
		if(round($n%10)==0)
		echo $head;
		$n++;
		$id=		$row[0];
		$msg_len=	$row[1];
		$nicks_count=	$row[2];
		$invisibility=	$row[3];
		$levelup_ability=$row[4];
		$kick_shield=	$row[5];
		$kick_ability=	$row[6];
		$replacements=	$row[7];
		$names=join(",",mysql_select1column("select concat(gender,':',name) from level_names where id='$id'"));
		$colors=join(",",mysql_select1column("select cpack from level_colors where id='$id'"));
		echo "<tr>
		<td>$n</td>
		<td><a href='/c2/admin/levels.php?edit=$id'>$id</a></td>
		<td>$names</td>
		<td>$msg_len</td>
		<td>$nicks_count</td>
		<td>$invisibility</td>
		<td>$levelup_ability</td>
		<td>$kick_shield</td>
		<td>$kick_ability</td>
		<td>$colors</td>
		<td>$replacements</td>
		<td>
			<a href='/c2/admin/levels.php?delete=$id'><img src='/pics/del.gif' border=0></a>
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
