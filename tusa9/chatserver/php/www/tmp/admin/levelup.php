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
     if(isset($uid))
     {
     	$abl=mysql_select1("select levels.levelup_ability from levels,tbl_users where tbl_users.level=levels.id and tbl_users.id='$uid'");
     }
     if(!isset($login) || !isset($abl))
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
<TITLE>Чат "Тусовка" - Консоль админа -> Уровни</TITLE>
</head>

<LINK rel="stylesheet" type="text/css" href="/css/main.css">
<script>
<!--

var ow=0;
function l_info(id)
{
	l='logininfo?id='+id;
	if(!ow || ow.closed){
		ow=open(l,'owusr','toolbar=0,status=0,resizable=1,scrollbars=1,width=550,height=500');
		ow.focus();
	}
	else{
		ow.focus();
		ow.location=l;
	}
	return false;
}
function fupdate(n)
{
	document.f.cmd.value=n;
	document.f.submit();
}
function chk_form()
{
	if(document.f.nick.value=="" && document.f.login.value==""){
		alert('Введите ник или логин для поиска');
		return false;
	}
	if(document.f.nick.value!="" && document.f.login.value!=""){
		alert('Введите что то одно!');
		return false;
	}
	return true;
}
function do_change(id)
{
	document.f.cmd.value='change';
	document.f.id.value=id;
	var sel;
	eval('sel=document.f.level'+id);
	document.f.level.value=sel.options[sel.selectedIndex].value;
	document.f.submit();
	return false;
}
//-->
</script>
<body>
<big><big><center><b>Повышение уровней</b></center></big></big><br>
<form name="f" method="POST" onsubmit="return chk_form();">
<input type=hidden name="cmd" value="">
<input type=hidden name="id" value="">
<input type=hidden name="level" value="">
Чтобы изменить уровень ползователя выбирете уровень и нажмите "ОК" на против данного пользователя.<br>
Информацию о выбранном логине можно посмотреть нажав на этот логин (если у вас есть права ессно).<p>
<table cellspacing=1 border=0>
<tr><td align=right>Поиск по нику:</td><td><input type=text name="nick" value="<?if(isset($arg_nick)) echo $arg_nick;?>"> <!--"<??> "--> </td><td rowspan=2 valign=middle><input type=submit value="Искать"></td></tr>
<tr><td align=right>Поиск по логину:</td><td><input type=text name="login" value="<?if(isset($arg_login)) echo $arg_login;?>"> <!--"<??> "--> </td></tr>
</table>
<br>

<center><big>Найдено</big></center><p>
<table cellspacing=1 cellpadding=1 class=border>
<tr><td class=trdd>Логин</td><td class=trdd>Сообщений</td><td class=trdd>Время</td><td class=trdd>Уровень</td><td class=trdd></td></tr>
<?
	if(isset($arg_cmd) && isset($arg_id) && $arg_cmd=="change" && isset($arg_level))
	{
		
		list($zlevel)=mysql_select1row("select level from tbl_users where id='$arg_id'");
		if($zlevel<$abl)
		{
			mysql_query("update tbl_users set level='$arg_level' poweshen='$uid' where id='$arg_id'") or die(mysql_error());
			mysql_query("insert into ext_events (event) values ('cmd=flush obj=tbl_users uid=$arg_id')") or die(mysql_error().__FILE__.__LINE__);

			
		}	
	}
	
	if(isset($arg_nick))
		$zid=mysql_select1("select uid from nicks where nick='$arg_nick'");
	else if(isset($arg_login))	
		$zid=mysql_select1("select id from tbl_users where nick='$arg_login'");
	if(isset($zid))	
	{
		list($zlogin,$zstat_m_count,$zstat_t_count,$zlevel)=mysql_select1row("select login, stat_m_count,stat_t_count,level from tbl_users where id='$zid'");
		$sel="<select name=sel>";
		$res=mysql_query("select a.id,b.name from levels a, level_names b where a.id=b.id and b.gender='0' order by 1") or die(mysql_error());
		while($row=mysql_fetch_row($res))
		{
			$lid=$row[0];
			$lname=$row[1];
			$selected=$zlevel==$lid?"SELECTED": "";
			$sel.="<option value=$lid $selected> $lid $lname\n";
		}
		$sel.="</select>";
		$dis=$zlevel>=$abl?"DISABLES":"";
		echo "<tr><td align=right class=tdrk><a href=\"#\" onclick=\"return l_info($zid);\" class=nick>$zlogin</a></td>
			<td class=tdrk>$zstat_m_count</td>
			<td class=tdrk>$zstat_t_count</td>
			<td class=tdrk>$sel</td>
			<td class=tdrk><input type=button value=\"OK\" onclick=\"return do_change($zid)\" $dis></td></tr>"
	}	
?>
</table>

<p>
<center>
<input type=button value="Обновить" onclick="fupdate('');">
<input type=button value="Закрыть" onclick="window.close();">
</center>
<p>
</form>
<?
     }

?>
