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
    if (!isset($_SESSION['login'])) { $login = "������"; }    else { $login = $_SESSION['login']; }
    if (!isset($_SESSION['ip'])) { $ip1 = "������"; }    else { $ip1 = $_SESSION['ip']; }
    $tmp = "$name � IP $ip ������� ����� � ������ ������ $login (������ IP $ip1)";
    mysql_query("insert into adm_events (login,date_events,type_events,events) values('$login','$d','CRACK','$tmp')") or die(mysql_error());
    session_destroy();  header("Location: /");
    }
                                    
?>
<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1251">
<TITLE>��� "�������" - ������� ������ -> ���������</TITLE>
</head>
<LINK rel="stylesheet" type="text/css" href="/css/main.css">
<script>
<!--

//-->
</script>
<body>

<form name=clear action="/c2/admin/_clear.php?clear=1">
<big><center><b>��������� �����</b></center></big><br>
<big><big><center><b>�� ������� ????</b></center></big></big><br>
<center>

<p>
<big><big>
<input type=submit value="��" style="width: 10em" onclick="location.href=/c2/admin/_clear.php?clear=1">
<input type=button value="�������" style="width: 10em"  onclick="window.close();">
</big></big>
</center>
</form>
                                                                                                                                                                


<?
?>


