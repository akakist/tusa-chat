<?
session_start();
import_request_variables("gp", "arg_");
include "inc/db_conn.php";
check_conn();

if ( !isset($_SESSION['ip']) || $_SESSION['ip']!=$_SERVER["REMOTE_ADDR"] || !isset($_SESSION['login']) || !(($_SESSION['level']>=800) || isset($_SESSION['privs']['oldban']))) //|| $_SESSION['level'])!=1000
    {
    $name = $_SERVER["SCRIPT_FILENAME"];
    $ip = $_SERVER["REMOTE_ADDR"];    $d = date('Y.m.d H:i:s');
    if (!isset($_SESSION['login'])) { $login = "������"; }    else { $login = $_SESSION['login']; }
    if (!isset($_SESSION['ip'])) { $ip1 = "������"; }    else { $ip1 = $_SESSION['ip']; }
    $tmp = "$name � IP $ip ������� ����� � ������ ������ $login (������ IP $ip1)";
    mysql_query("insert into adm_events (login,date_events,type_events,events) values('$login','$d','CRACK','$tmp')") or die(mysql_error());
    session_destroy();  header("Location: /");
    }
else
    {
    $login=$_SESSION['login'];
    $uid=$_SESSION['uid'];
    $cur_base_lev = intval($_SESSION['level']/100);
?>
<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1251">
<TITLE>��� "�������" - ������� ������ -> ��� �� IP</TITLE>
</head>
<?
        if(isset($arg_del_ip))
                {
                list($ip,$za,$uid,$time_ban,$time_free)=mysql_select1row("select ip,za,uid,time_ban,time_free from banned_ip where id='$arg_del_ip'");
		$tmp = "$ip $uid $time_ban $time_free $za";
		$d = date('Y.m.d H:i:s');
                mysql_query("insert into adm_events (login,date_events,type_events,events) values('$login','$d','IP_DEL','$tmp')") or die(mysql_error());
	        mysql_query("delete from banned_ip where id='$arg_del_ip'") or die(mysql_error());
//                echo "������� ���� $arg_del_ip";
		unset($d); unset($arg_del_ip); unset($tmp);
                }

        if(isset($arg_set_ip))
                {
		$add_ip_preg = preg_split("/\./", $arg_set_ip);
		if ( isset($add_ip_preg[3]) && !isset($add_ip_preg[4]) &&
		     ctype_digit($add_ip_preg[0]) && $add_ip_preg[0] < 256 && $add_ip_preg[0] >=0 &&
		     ctype_digit($add_ip_preg[1]) && $add_ip_preg[1] < 256 && $add_ip_preg[1] >=0 &&
		     ctype_digit($add_ip_preg[2]) && $add_ip_preg[2] < 256 && $add_ip_preg[2] >=0 &&
		   ((ctype_digit($add_ip_preg[3]) && $add_ip_preg[3] < 256 && $add_ip_preg[3] >=0) || $add_ip_preg[3] == '*')) 
		    {
		    $d = date('Y.m.d H:i:s');
            	    $time_free = date('Y.m.d H:i:s',time()+$arg_time_long);
            	    $t = $arg_time_long / 60;
		    if ( $t<60 ) $time_cnt = $t." �";
		    else 
		      {
		      $t /= 60;
		      if ( $t<24 ) $time_cnt = $t." �";
			else 
		    	    {
		    	    $t /= 24;
		    	    if ( $t<7 ) $time_cnt = $t." ��";
			    else 
			    	{
		    		$t /= 7;
		    		$time_cnt = $t." ��";
		    		}
		    	    }
		    	}
		      
		     
		    $tmp = "$arg_set_ip $d $time_cnt $arg_za_set";
//            	    echo $tmp;
            	    mysql_query("insert into adm_events (login,date_events,type_events,events) values('$login','$d','IP_SET','$tmp')") or die(mysql_error());
	    	    mysql_query("insert into banned_ip (ip,time_ban,time_free,time_cnt,uid,za) values('$arg_set_ip','$d','$time_free','$time_cnt','$uid','$arg_za_set')") or die(mysql_error());

            	    $msg="IP $arg_set_ip ������������";
            	    unset ($arg_set_ip); unset ($tmp); unset ($d); unset ($time_free); unset ($time_cnt); unset ($add_ip_preg); unset($arg_za_set); unset ($arg_time_long);

            	    }
		
		else
		    {
		    print "�� ��������� ������ � IP-������";
		    unset ($arg_set_ip);
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
<big><big><center><b>��� �� IP</b></center></big></big><br>


<table width=100% cellspacing=1 cellpadding=5 class=border>
<?
$head="<tr>
	<td><center>IP</center></td>
	<td><center>����</center></td>
	<td><center>�� �������</center></td>
	<td><center>����� �������� ����</center></td>
	<td><center>���</center></td>
	<td><center>�� ���</center></td>
	<td><center>�����</center></td>
</tr>";

	echo $head;
	$req=mysql_query("select ip,time_ban,time_cnt,time_free,uid,za,id from banned_ip order by ip") or die(mysql_error());
	while($row=mysql_fetch_row($req))
	{
		$ip=		$row[0];
		$time_ban=	$row[1];
		$time_cnt=	$row[2];
		$time_free=	$row[3];
		$za=	$row[5];
		$id=	$row[6];
		$dis="";
                list($login_ban_auth,$login_ban_level)=mysql_select1row("select login,level from tbl_users where id='$row[4]'");
                $login_ban_level = intval ($login_ban_level/100);
                if ($cur_base_lev>$login_ban_level || $login_ban_auth==$login || $_SESSION['level']==1000 )
                  {
                  $str_but = " class=tdrk><center> <input type=button value=\"�����\" onclick=\"location.href='/c2/admin/ip_ban.php?del_ip=".$id."'\"$dis></center>";
                  }
                else
                  $str_but = " ";

		
	
		echo "<tr>
		<td><right>$ip</right></td>
		<td><right>$time_ban</right></td>
		<td><center>$time_cnt</center></td>
		<td>$time_free</td>
		<td><right>$login_ban_auth</right></td>
		<td>$za</td>
		<td $str_but</td></tr>";

	}
?>

</table>


	<form name=ip_add action="/c2/admin/ip_ban.php">
        <br>������������� IP: <input type=text name="set_ip" maxlen=15 size=15 style="height: 19"> 
        ����������� <input type=text name="za_set" maxlen=30 size=30 style="height: 19">
        ��  <select name=time_long>
	<option value=60>1 ������
	<option value=300 SELECTED>5 �����
	<option value=600>10 �����
	<option value=1200>20 �����
	<option value=1800>30 �����
	<option value=3600>1 ���
	<option value=7200>2 ����
	<option value=21600>6 �����
	<option value=43200>12 �����
	<option value=86400>1 ����
	<option value=172800>2 ���
	<option value=604800>1 ������
	<option value=1209600>2 ������
	</select>
	<input type=submit value="OK" style="width: 2em" onclick="location.href=/c2/admin/ip_ban.php"
        </form>


<p>
<center>
<input type=button value="�������" onclick="window.close();">
</center>
<p>
</form>
<?
}
?>


