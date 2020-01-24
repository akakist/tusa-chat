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
else
    {
    $login=$_SESSION['login'];
    $uid=intval($_SESSION['uid']);

?>
<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=UTF-8">
<TITLE>Чат "Тусовка" - Консоль админа -> FireWall по IP</TITLE>
</head>
<?
//echo date('Y.m.d H:i:s');
        if(isset($arg_del_fw))
                {
                list($ip,$za,$uid,$time_ban,$time_free)=mysql_select1row("select ip,za,uid,time_ban,time_free from firewall where id='".mysql_escape_string($arg_del_fw)."'");
		$tmp = "$ip $uid $time_ban $time_free $za";
		$d = time();
		$d = date('Y.m.d H:i:s');
                mysql_query("insert into adm_events (login,date_events,type_events,events) values('".mysql_escape_string($login)."','$d','FW_DEL','$tmp')") or die(mysql_error());
	        mysql_query("delete from firewall where id='".mysql_escape_string($arg_del_fw)."'") or die(mysql_error());
//                echo "Файрвол снят $arg_del_fw";
		unset($d); unset($arg_del_fw); unset($tmp);
                }

        if(isset($arg_set_fw))
                {
		$add_ip_preg = preg_split("/\./", $arg_set_fw);
		if ( isset($add_ip_preg[3]) && !isset($add_ip_preg[4]) &&
		     ctype_digit($add_ip_preg[0]) && $add_ip_preg[0] < 256 && $add_ip_preg[0] >=0 &&
		     ctype_digit($add_ip_preg[1]) && $add_ip_preg[1] < 256 && $add_ip_preg[1] >=0 &&
		     ctype_digit($add_ip_preg[2]) && $add_ip_preg[2] < 256 && $add_ip_preg[2] >=0 &&
		   ((ctype_digit($add_ip_preg[3]) && $add_ip_preg[3] < 256 && $add_ip_preg[3] >=0) || $add_ip_preg[3] == '*')) 
		    {
		    $d = date('Y.m.d H:i:s');
            	    $time_free = date('Y.m.d H:i:s',time()+$arg_time_long);
            	    $t = $arg_time_long / 60;
		    if ( $t<60 ) $time_cnt = $t." м";
		    else 
		      {
		      $t /= 60;
		      if ( $t<24 ) $time_cnt = $t." ч";
			else 
		    	    {
		    	    $t /= 24;
		    	    if ( $t<7 ) $time_cnt = $t." дн";
			    else 
			    	{
		    		$t /= 7;
		    		$time_cnt = $t." нд";
		    		}
		    	    }
		    	}
		      
		     
		    $tmp = "$arg_set_fw $d $time_cnt $arg_za_set";
//            	    echo $uid $login $tmp;
            	    mysql_query("insert into adm_events (login,date_events,type_events,events) values('".mysql_escape_string($login)."','$d','FW_SET','$tmp')") or die(mysql_error());
	    	    mysql_query("insert into firewall (ip,time_ban,time_free,time_cnt,uid,za) values('".mysql_escape_string($arg_set_fw)."','$d','$time_free','$time_cnt','$uid','$arg_za_set')") or die(mysql_error());

            	    $msg="IP $arg_set_fw заблокирован";
            	    unset ($arg_set_fw); unset ($tmp); unset ($d); unset ($time_free); unset ($time_cnt); unset ($add_ip_preg); unset($arg_za_set);

            	    }
		
		else
		    {
		    print "Вы допустили ошибку в IP-адресе";
		    unset ($arg_set_fw);
		    }
                
                }
//            mysql_query("insert into level_colors (id,cpack) values('$arg_id','$n')") or die(mysql_error());
                                                                                                                                                                                                            
                                                                                                                                                                                                            
?>
                                                                                                                                                                                                            
                                                                                                                                                                                                            

<LINK rel="stylesheet" type="text/css" href="/css/main.css">
<script>
<!--

//-->
</script>
<body>
<big><big><center><b>Файрвол по IP</b></center></big></big><br>


<table width=100% cellspacing=1 cellpadding=5 class=border>
<?
$head="<tr>
	<td><center>IP</center></td>
	<td><center>Дата</center></td>
	<td><center>На сколько</center></td>
	<td><center>Когда истекает срок</center></td>
	<td><center>Кем</center></td>
	<td><center>За что</center></td>
	<td><center>Снять</center></td>
</tr>";

	echo $head;
	$cur_base_lev = intval($_SESSION['level']/100);
	$req=mysql_query("select ip,time_ban,time_cnt,time_free,uid,za,id from firewall order by ip") or die(mysql_error());
	while($row=mysql_fetch_row($req))
	{
		$ip=		$row[0];
		$time_ban=	$row[1];
		$time_cnt=	$row[2];
		$time_free=	$row[3];
		$login_ban_auth= mysql_select1("select login from tbl_users where id='$row[4]'");
		$za=	$row[5];
		$id=	$row[6];
		$dis="";
	
		echo "<tr>
		<td><right>$ip</right></td>
		<td><right>$time_ban</right></td>
		<td><center>$time_cnt</center></td>
		<td>$time_free</td>
		<td><right>$login_ban_auth</right></td>
		<td>$za</td>
		<td class=tdrk><input type=button value=\"Снять\" onclick=\"location.href='/c2/admin/firewall.php?del_fw=".$id."'\"$dis></td></tr>";

	}
//	<input type=submit value="OK" style="width: 2em" onclick="location.href=/c2/admin/firewall.php?del_fw=\".$id."'"
?>

</table>


	<form name=ip_add action="/c2/admin/firewall.php">
        <br>Заблокировать IP: <input type=text name="set_fw" maxlen=15 size=15 style="height: 19"> 
        Комментарий <input type=text name="za_set" maxlen=30 size=30 style="height: 19">
        на  <select name=time_long>
	<option value=60>1 минуту
	<option value=300 SELECTED>5 минут
	<option value=600>10 минут
	<option value=1200>20 минут
	<option value=1800>30 минут
	<option value=3600>1 час
	<option value=7200>2 часа
	<option value=21600>6 часов
	<option value=43200>12 часов
	<option value=86400>1 день
	<option value=172800>2 дня
	<option value=604800>1 неделю
	<option value=1209600>2 недели
	</select>
	<input type=submit value="OK" style="width: 2em" onclick="location.href=/c2/admin/firewall.php"
        </form>


<p>
<center>
<input type=button value="Закрыть" onclick="window.close();">
</center>
<p>
</form>
<?
}
?>


