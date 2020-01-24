<?
	session_start();
        import_request_variables("gp", "arg_");
//	if($_SESSION['privs'])
?>
<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1251">
<TITLE>Чат "Тусовка" - Консоль админа</TITLE>

	<script type="text/javascript" src="/js/jquery.pack.js"></script>

</head>

<LINK rel="stylesheet" type="text/css" href="/css/main.css">
<script>
<!--

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

function do_list()
{
	y=(screen.height*9)/10;
	opwin('/admin.tse/userlist.tse','userlist',630,y);
}



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
<input type=button value="Список юзеров" onclick="do_list();">
<input type=button value="Баны комн" onclick="opwin('/admin.tse/ban.tse','banwin',900,screen.height);">
<?
	if(isset($_SESSION['privs']['oldban'])) echo '<input type=button value="Бан по IP" onclick="do_ban_ip();"><input type=button value="Бан логинов" onclick="do_ban_login();"><input type=button value="Бан ников" onclick="do_ban_nick();">';
	if(isset($_SESSION['privs']['logs'])) echo '<input type=button value="Логи" onclick="opwin(\'/admin.tse/logs.tse\',\'logswin\',900,screen.height);">';
	if(isset($_SESSION['privs']['vote'])) echo '<input type=button value="Голосование" onclick="opwin(\'/admin.tse/vote.tse\',\'votaswin\',900,screen.height);">';
	if(isset($_SESSION['privs']['zags'])) echo '<input type=button value="ЗАГС" onclick="opwin(\'/admin/zags.php\',\'zagsaswin\',900,screen.height);">';
	if(isset($_SESSION['privs']['settings"'])) echo '<input type=button value="Настройки" onclick="opwin(\'/admin.tse/settings.tse\',\'settswin\',900,screen.height);">';
	if(isset($_SESSION['privs']['moders'])) echo '<input type=button value="Модераторы" onclick="opwin(\'/admin.tse/moders.tse\',\'moderswin\',900,screen.height);">';
	if(isset($_SESSION['privs']['privs"'])) echo '<input type=button value="Привилегии" onclick="opwin(\'/admin.tse/privileges.tse\',\'privswin\',900,screen.height);">';
	if(isset($_SESSION['privs']['news'])) echo '<input type=button value="Новости" onclick="opwin(\'/admin.tse/news.tse\',\'banwin\',900,screen.width);">';
	if(isset($_SESSION['privs']['accounts'])) echo '<input type=button value="Учетные записи" onclick="opwin(\'/admin/accounts.php\',\'accwin\',900,screen.width);">';
	if(isset($_SESSION['privs']['levels'])) echo '<input type=button value="Уровни" onclick="opwin(\'/admin/levels.php\',\'acclevels\',900,screen.width);">';
	if(isset($_SESSION['privs']['news'])) echo '<input type=button value="Новости" onclick="opwin(\'/admin/news.php\',\'newsaccwin\',900,screen.width);">';

?>
</center>
</div>
<br>
<?
	if($_SESSION['level']>=900) 
	{
	?>
	<form name=fl action="/admin/logininfo.php">
	Инфо о логине: <input type=textfield name="login" style="height: 19"><input type=submit value="OK" style="width: 2em" onclick="opwin('/admin/logininfo.php?login='+login.value,'owusr',550,500); return false;">
	</form>
	<?
	}
?>


Подробнее об администрировании читать <a href=# onclick="return opwin('/help/admin','ahelp',650,580)">тут</a>.<br>

<p>
<center><input type=button value="Закрыть" onclick="window.close();">
</center>
<p>
