<?
session_start();
import_request_variables("gp", "arg_");
include "$BASE_DIR/inc/db_conn.php";
check_conn();
if ( !isset($_SESSION['ip']) || $_SESSION['ip']!=$_SERVER["REMOTE_ADDR"] || !isset($_SESSION['login']) ) //|| $_SESSION['level'])!=1000 
    {
    $name = $_SERVER["SCRIPT_FILENAME"];
    $ip = $_SERVER["REMOTE_ADDR"];    $d = date('Y.m.d H:i:s');
    if (!isset($_SESSION['login'])) { $login = "ПУСТОЙ"; }    else { $login = $_SESSION['login']; }
    if (!isset($_SESSION['ip'])) { $ip1 = "ПУСТОЙ"; }    else { $ip1 = $_SESSION['ip']; }
    $tmp = "$name С IP $ip попытка войти в сессию логина $login (старый IP $ip1)";
    mysql_query("insert into adm_events (login,date_events,type_events,events) values('$login','$d','CRACK','$tmp')") or die(mysql_error());
    session_destroy();  header("Location: /");
    }

?>
<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=UTF-8">
<TITLE>Чат "Тусовка" - Консоль админа</TITLE>

	<script type="text/javascript" src="/js/jquery.pack.js"></script>

</head>

<LINK rel="stylesheet" type="text/css" href="/css/main.css">
<script>
<!--
function bot_reload(name)
{
    url="http://tusovka.tomsk.ru:8080/admin.tse/reload.tse/"+name;
    alert(url);
    $.post(name);
    return false;
}
function opwin(url,nm,sx,sy)
{
	nw=window.open(url,nm,'toolbar=0,status=0,scrollbars=1,width='+sx+',height='+sy+',resizable=1');
	nw.focus();
}

function opwinstd(url,nm)
{
	opwin(url,nm,750,500);
}

function do_ban_ip()
{
	opwinstd('/admin.tse/ipban.tse','ipban');
}

function do_ban_login()
{
	opwinstd('/admin.tse/loginban.tse','loginban');
}

function do_ban_nick()
{
	opwinstd('/admin.tse/nickban.tse','nickban');
}

/*function do_list()
{
	y=(screen.height*9)/10;
	opwin('/admin.tse/userlist.tse','userlist',630,y);
}
*/


//-->
</script>
<body>
<style>
input {width: 100;}
</style>
<form>
<big><big><center><b>Консоль админа</b></center></big></big>
<DIV align="justify">
Уважаемые администраторы (и прочие люди), надеюсь что вам не надо напоминать серьезность ваших действий.
Среди тех, против кого Вы примените свою "силу" могут оказаться очень серьёзные и уважаемые люди! Также, стоит
лояльнее относится к тем, кто в чате постоянный гость. Постарайтесь ему просто всё объяснить!<br>
В любом случае, имейте ввиду, что ведутся все логи и за каждое свое действие Вы будете отвечать.
<br><br>
<center>
<input type=button value="Кляпы" onclick="opwin('/admin.tse/ban.tse','banwin',900,screen.height);">
<?
//print_r($_SESSION['privs']);
//$lv=$_SESSION['level'];
//$levelup_ability=mysql_select1("select levelup_ability from levels where id='$lv'");

	if(isset($_SESSION['privs']['oldban']) && $_SESSION['level']>=900) echo '<input type=button value="Отл Кляпы" onclick="opwin(\'/c2/admin/klap.php\',\'newsaccwin\',1250,600);">';
	if($_SESSION['level']>=700) echo '<input type=button value="Бан логинов" onclick="opwin(\'/c2/admin/login_ban.php\',\'newsaccwin\',950,600);">';
	if($_SESSION['level']>=800) echo '<input type=button value="Бан по IP" onclick="opwin(\'/c2/admin/ip_ban.php\',\'newsaccwin\',950,600);">';
	if(isset($_SESSION['privs']['oldban']) && $_SESSION['level']>=700) echo '<input type=button value="Бан ников" onclick="do_ban_nick();">';
	if(isset($_SESSION['privs']['logs'])) echo '<input type=button value="Логи" onclick="opwin(\'/admin.tse/logs.tse\',\'logswin\',800,screen.height);">';
	if(isset($_SESSION['privs']['vote']) || $_SESSION['level']==1000) echo '<input type=button value="Голосование" onclick="opwin(\'/c2/admin/vote.php\',\'votaswin\',290,800);">';
	if(isset($_SESSION['privs']['settings'])) echo '<input type=button value="Настройки" onclick="opwin(\'/admin.tse/settings.tse\',\'settswin\',900,screen.height);">';
	if(isset($_SESSION['privs']['moders'])) echo '<input type=button value="Модераторы" onclick="opwin(\'/admin.tse/moders.tse\',\'moderswin\',900,screen.height);">';
	if(isset($_SESSION['privs']['privs']) || $_SESSION['level']==930 ) echo '<input type=button value="Привилегии" onclick="opwin(\'/admin.tse/privileges.tse\',\'privswin\',900,screen.height);">';
	if(isset($_SESSION['privs']['settings']) && $_SESSION['level']==1000) echo '<input type=button value="Уровни" onclick="opwin(\'/c2/admin/levels.php\',\'acclevels\',1200,screen.width);">';
	if(isset($_SESSION['privs']['settings']) && $_SESSION['level']>=1000) echo '<input type=button value="Файрвол" onclick="opwin(\'/c2/admin/firewall.php\',\'acclevels\',900,screen.width);">';
	if(isset($_SESSION['privs']['news'])) echo '<input type=button value="Новости" onclick="opwin(\'/c2/admin/news.php\',\'newsaccwin\',900,screen.width);">';
//	if($levelup_ability>0&&$_SESSION['level']>900) echo '<input type=button value="Повышалка" onclick="opwin(\'levelup.php\',\'acclevels\',900,screen.width);">';
	if($_SESSION['level']>=1000) echo '<input type=button value="Повышалка" onclick="opwin(\'levelup.php\',\'acclevels\',900,screen.width);">';
//	if(isset($_SESSION['privs']['bot_reload'])) echo '<input type=button value="Перезагрузить Веда" onclick="return bot_reload(\"mafia\");">';
//	if(isset($_SESSION['privs']['bot_reload'])) echo '<input type=button value="Reload Вопрос" onclick="return bot_reload(\'quiz\');">';
//	if(isset($_SESSION['privs']['bot_reload'])) echo '<input type=button value="Перезагрузить Крупа" onclick="return bot_reload(\"roulette\");">';
	if(isset($_SESSION['privs']['bot_reload'])) echo '<input type=button value="Обнуление топов" onclick="opwin(\'clear.php\',\'acclevels\',400,200);">';
	
	if(isset($_SESSION['privs']['setting']) || $_SESSION['level']==1000) echo '<input type=button value="Отл Комнаты" onclick="opwin(\'/c2/admin/channels.php\',\'votaswin\',290,800);">';
	
	if(isset($_SESSION['privs']['accounts']) && $_SESSION['level']==1000) echo '<input type=button value="Учетные записи" onclick="opwin(\'accounts.php\',\'accwin\',900,screen.width);">';
//	if(isset($_SESSION['privs']['levels'])) echo '<input type=button value="Уровни" onclick="opwin(\'/c2/admin/levels.php\',\'acclevels\',900,screen.width);">';
//	if(isset($_SESSION['privs']['zags'])) echo '<input type=button value="ЗАГС" onclick="opwin(\'zags.php\',\'zagsaswin\',900,screen.height);">';
//	if(isset($_SESSION['privs']['oldban']) && $_SESSION['level']>=800) echo '<input type=button value="Бан логинов" onclick="do_ban_login();">';
//	if(isset($_SESSION['privs']['oldban']) || $_SESSION['level']>=800) echo '<input type=button value="Бан по IP" onclick="do_ban_ip();">';

?>
</center>
</div>
<br>
<?
	if($_SESSION['level']>=800) 
	{
	?>
	<form name=fl action="/c2/admin/logininfo.php">
	Инфо о логине: <input type=textfield name="login" style="height: 19"><input type=submit value="OK" style="width: 2em" onclick="opwin('/c2/admin/logininfo.php?login='+login.value,'owusr',550,500); return false;">
	</form>
	<?
	}
?>


Подробнее об администрировании читать <a href=# onclick="return opwin('/c2/help/admin/index.php.php','ahelp',650,580)">тут</a>.<br>

<p>
<center><input type=button value="Закрыть" onclick="window.close();">
</center>
<p>
