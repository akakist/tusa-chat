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
<TITLE>Чат "Тусовка" - Консоль админа -> Админство голосования</TITLE>
</head>
<?

    if(isset($arg_add_ball)&&isset($arg_add_login))
        {
        $zid=mysql_select1("select id from tbl_users where login='$arg_add_login'");
        if ($zid<1)
    	    {
    	    echo "<center><big>Логин не найден</big></center><p>";
            }
        else
    	    {
    	    mysql_query("update tbl_users set vote_balls='$arg_add_ball' where id='$zid'") or die(mysql_error().__FILE__.__LINE__);
    	    list($t1,$t2,$t3,$t4)= mysql_select1row("select id,login,last_nick,vote_balls from tbl_users where id='$zid'") or die(mysql_error().__FILE__.__LINE__);
//	    array_push($a_id,$t1);
//    	    array_push($a_login,$t2);
//    	    array_push($a_last_nick,$t3);
//    	    array_push($a_ball,$t4);
//    	    $number++;
	    unset($arg_save);
            }
	unset($zid); unset($arg_add_login); unset($arg_add_ball);
        }
	

    if(!isset($arg_save)||$arg_save==0)
	{
	if(isset($a_id)) 	    {	    unset($a_id);	unset($a_login);	unset($a_last_nick);	    unset($a_ball); 	    }
	$a_id=array();	$a_login=array();	$a_last_nick=array();	$a_ball=array();
	$number=0;
	$req=mysql_query("select id,login,last_nick,vote_balls from tbl_users where vote_balls>0 order by id") or die(mysql_error());
	while($row=mysql_fetch_row($req))
	    {
	    array_push($a_id,$row[0]);
	    array_push($a_login,$row[1]);
	    array_push($a_last_nick,$row[2]);
	    array_push($a_ball,$row[3]);
	    $number++;
	    }
	$arg_save=-1;
	}

//            mysql_query("insert into level_colors (id,cpack) values('$arg_id','$n')") or die(mysql_error());
                                                                                                                                                                                                            
                                                                                                                                                                                                            
?>
                                                                                                                                                                                                            
                                                                                                                                                                                                            

<LINK rel="stylesheet" type="text/css" href="/css/main.css">
<script>
<!--

//-->
</script>
<body>
<big><big><center><b>Админство голосования</b></center></big></big><br>


<table width=100% cellspacing=1 cellpadding=5 class=border>
<?
    $head="<tr>
    <td><center>Ник(логин)</center></td>
    <td><center> % </center></td>
    </tr>";
    echo $head;
    $perc=0;
    for($i=0;$i<$number;$i++)
        {
        echo "<tr>     
        <td><center><a href='/c2/chat_userinfo2.php?id=$a_id[$i]' target=_blank>$a_last_nick[$i]($a_login[$i])</a></center></td>
        <td><center>$a_ball[$i]</center></td>";
        $perc+=$a_ball[$i];
        }
    

?>

</table>
        <form name=ip_add action="/c2/admin/vote.php">
	<br><b> Сумма баллов <?=$perc?> </b><br>
        <br>Добавить логин <input type=text name='add_login' value="" maxlength=16 size=16 onchange='add_login=this.value'>
        <input type=text name='add_ball' value="0" maxlength=2 size=2 onchange='add_ball=this.value'>
        <input type=submit value="OK" style="width: 2em" onclick="location.href=/c2/admin/vote.php"
        </form>
                                                                                                                                                                


<p>
<center>
<input type=button value="Сохранить" onclick="location.href=/c2/admin/vote.php?save=1">
<input type=button value="Закрыть" onclick="window.close();">
<input type=button value="Отмена(Обновить)" onclick="location.href=/c2/admin/vote.php?save=0">
</center>
<p>
</form>
<?
//}
?>


