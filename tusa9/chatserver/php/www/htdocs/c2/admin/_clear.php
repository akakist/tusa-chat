<?
session_start();
import_request_variables("gp", "arg_");
include "inc/db_conn.php";
check_conn();
/*
|| 
*/
    
if ($_SESSION['ip']!=$_SERVER["REMOTE_ADDR"] || !isset($_SESSION['login']) || $_SESSION['level']<900 || !isset($_SESSION['privs']['vote']) ) //|| $_SESSION['level'])!=1000
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
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1251">
<TITLE>Чат "Тусовка" - Консоль админа -> Обнуление</TITLE>
</head>
<LINK rel="stylesheet" type="text/css" href="/css/main.css">
<script>
<!--

//-->
</script>
<body>


<?
if(!isset($arg_clear)||$arg_clear==1)
    {
    
    mysql_query("DROP TABLE IF EXISTS `_tmp`");
    /*!40101 SET @saved_cs_client     = @@character_set_client */;
    /*!40101 SET character_set_client = utf8 */;
    mysql_query("CREATE TABLE `_tmp` (
	`ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
        `login` char(18) NOT NULL DEFAULT '',
	`score` int(10) NOT NULL DEFAULT '0',
        PRIMARY KEY (`ID`),
        KEY `_login` (`login`),
        KEY `_score` (`score`)
        ) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=cp1251 PACK_KEYS=1");
    
        $quiz=mysql_query("
	SELECT login,SUM(score) AS val FROM(
        SELECT login,score from quiz_all_score
        UNION ALL SELECT login,score from quiz_rating ) AS u
        GROUP BY login ORDER by val desc           ") or die(mysql_error());
                                                                                
    while($row=mysql_fetch_row($quiz))
	{    mysql_query("    INSERT INTO _tmp (login,score) VALUES ('$row[0]','$row[1]')    ");    }    

    mysql_query("DROP TABLE IF EXISTS _t_q");
    mysql_query(" ALTER TABLE quiz_all_score RENAME _t_q ") or die(mysql_error());
    mysql_query(" ALTER TABLE _tmp  RENAME quiz_all_score ") or die(mysql_error());

    mysql_query("DROP TABLE IF EXISTS _tmp_");
    mysql_query("CREATE TABLE `_tmp_` (
	`ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
	`login` char(18) NOT NULL DEFAULT '',
	`win` int(11) NOT NULL DEFAULT '0',
	`loose` int(11) NOT NULL DEFAULT '0',
	`score` int(11) NOT NULL DEFAULT '0',
	PRIMARY KEY (`ID`),
	KEY `_login` (`login`),
	KEY `_win` (`win`),
	KEY `_loose` (`loose`),
	KEY `_score` (`score`)
	) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=cp1251 PACK_KEYS=1")or die(mysql_error());
                    

    $mafia=mysql_query("
	SELECT login,SUM(win),SUM(loose),SUM(score) AS val FROM(
        SELECT login,win,loose,score from mafia_all_score
        UNION ALL  SELECT login,win,loose,score from mafia_score ) AS u
        GROUP BY login ORDER by val desc           ") or die(mysql_error());
                                                                                
    while($row=mysql_fetch_row($mafia))
	{    mysql_query("    INSERT INTO _tmp_ (login,win,loose,score) VALUES ( '$row[0]', '$row[1]', '$row[2]', '$row[3]' )    ")or die(mysql_error());    }    
    mysql_query("DROP TABLE IF EXISTS _t_m");
    mysql_query(" ALTER TABLE mafia_all_score RENAME _t_m ") or die(mysql_error());
    mysql_query(" ALTER TABLE _tmp_  RENAME mafia_all_score ") or die(mysql_error());

//раздача призов и сохранение топов
    $quiz=mysql_query("SELECT login,score from quiz_rating ORDER by score desc limit 10") or die(mysql_error());
    for ($i=1;$i<=10;$i++)
	{
	$row=mysql_fetch_row($quiz);
	$zid=mysql_select1("select id  from tbl_users where login='$row[0]'");
	$summa=(11-$i)*$row[1];
        mysql_query("update tbl_users set credit_summa=credit_summa+$summa where id='$zid'") or die(mysql_error().__FILE__.__LINE__);
        mysql_query("insert into ext_events (event) values ('cmd=flush obj=tbl_users uid=$zid')") or die(mysql_error().__FILE__.__LINE__);
        mysql_query("insert into ext_events (event,d1) values ('cmd=sysmsg uid=$zid',
                'Вам перечислено $summa кредитов за топ викторины')") or die(mysql_error().__FILE__.__LINE__);
        mysql_query("insert into ext_events (event,d1,d2) values ('cmd=systemnote uid=$zid','Перечисление кредитов',
                'Вам перечислено $summa кредитов за топ викторины')") or die(mysql_error().__FILE__.__LINE__);
	}

    $mafia=mysql_query("SELECT login,score from mafia_score ORDER by score desc limit 10") or die(mysql_error());
    for ($i=1;$i<=10;$i++)
	{
	$row=mysql_fetch_row($mafia);
	$zid=mysql_select1("select id  from tbl_users where login='$row[0]'");
	$summa=(11-$i)/20*$row[1];
        mysql_query("update tbl_users set credit_summa=credit_summa+$summa where id='$zid'") or die(mysql_error().__FILE__.__LINE__);
        mysql_query("insert into ext_events (event) values ('cmd=flush obj=tbl_users uid=$zid')") or die(mysql_error().__FILE__.__LINE__);
        mysql_query("insert into ext_events (event,d1) values ('cmd=sysmsg uid=$zid',
                'Вам перечислено $summa кредитов за топ мафии')") or die(mysql_error().__FILE__.__LINE__);
        mysql_query("insert into ext_events (event,d1,d2) values ('cmd=systemnote uid=$zid','Перечисление кредитов',
                'Вам перечислено $summa кредитов за топ мафии')") or die(mysql_error().__FILE__.__LINE__);
	}


//Обнуление
mysql_query("delete from mafia_score") or die(mysql_error());
mysql_query("delete from quiz_rating") or die(mysql_error());

?>
<center>
<form name=exit action="/c2/admin/_clear.php?clear=1">
<big>Топы успешно обнулены</big>
<br>
<p>
<input type=button value="Закрыть" style="width: 10em"  onclick="window.close();">
</center>

<?
    }
?>

</form>
                                                                                                                                                                


<?
?>


