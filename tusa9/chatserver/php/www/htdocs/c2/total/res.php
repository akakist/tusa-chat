<?
session_start();
import_request_variables("gp", "arg_");
include "inc/db_conn.php";
include "inc/date.php";
check_conn();
if(!isset($_SESSION['login']) || !isset($arg_id) || !isset($_SESSION['uid'])) {         header("Location: /");     }

$uid=$_SESSION['uid'];


$result=mysql_query("select command1,command2,date_game from bookmaker where id=$arg_id") or die(mysql_error());
if (!$row=mysql_fetch_row($result))  {         header("Location: /");     }
$main_cred=mysql_select1("select credit_summa from tbl_users where id='$uid'");
if ($main_cred>300000 && $uid!=60610 && $uid!=203509 ) {         header("Location: /");     }

?>
<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1251">
<TITLE>��� "�������" - ����� ������</TITLE>
</head>

<LINK rel="stylesheet" type="text/css" href="/css/main.css">
<script>
<!--
var uf=0;

function do_f(id)
{
        var r=Math.random();
	locat='/userphotos/'+id;
	sx=screen.width/3*2;
	sy=screen.height/5*4;
	if(!uf || uf.closed)
	{
		uf=open(locat,'uf','toolbar=0,status=0,resizable=1,scrollbars=1,width='+sx+',height='+sy);
	}
	else
	{
		uf.focus();
		uf.location=locat;
	}	
//	return true;
}
//-->
</script>
<BODY>
<big><big><center><b>����� ������</b></center></big></big>
    <hr width=100% size=2>
<?
//    <table cellspacing=1 cellpadding=1 border=0>


echo "<center><b> <font class='yelmsg' size=6> ���� </font></b></center><br>";
echo "<center><b> <font class='yelmsg' size=4>" .$row[0] ." - " .$row[1] ."</font></b></center>";
         
//<form method=post name=add_st action="bookmaker.php">
?>

<center>
<form method=post name=add_st action="bookmaker.php">
<br>

<center>
<input type="radio" name="res" value="1"> ������� <?=$row[0] ?>
<input type="radio" name="res" value="2"checked="1"> ����� � �������� �����
<input type="radio" name="res" value="3"> ������� <?=$row[1] ?> <br> <br>
<input type=textfield style='width: 65px' size='8' maxlength='8' name="score"> <br><br>
<input type="hidden" name="match" value="<?=$arg_id?>">
<input type=submit name="save_res" value="�������� ���������" >
</center>
</center>
</form>

<?                                                                                                                                                                                                                     
?>
</table>
<?
?>
