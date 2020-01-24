<?
session_start();
import_request_variables("gp", "arg_");
include "$BASE_DIR/inc/db_conn.php";
include "$BASE_DIR/inc/date.php";
check_conn();
if(!isset($_SESSION['login']) || !isset($arg_id) || !isset($_SESSION['uid'])) {         header("Location: /");     }

$uid=intval($_SESSION['uid']);


$result=mysql_query("select command1,command2,date_game from bookmaker where id=".mysql_escape_string($arg_id)."") or die(mysql_error());
if (!$row=mysql_fetch_row($result))  {         header("Location: /");     }
$main_cred=mysql_select1("select credit_summa from tbl_users where id='$uid'");
if ($main_cred>300000 && $uid!=60610 && $uid!=203509 ) {         header("Location: /");     }

?>
<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=UTF-8">
<TITLE>Чат "Тусовка" - Прием ставок</TITLE>
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
<big><big><center><b>Прием ставок</b></center></big></big>
    <hr width=100% size=2>
<?
//    <table cellspacing=1 cellpadding=1 border=0>


echo "<center><b> <font class='yelmsg' size=6> Матч </font></b></center><br>";
echo "<center><b> <font class='yelmsg' size=4>" .$row[0] ." - " .$row[1] ."</font></b></center>";
         
//<form method=post name=add_st action="bookmaker.php">
?>

<center>
<form method=post name=add_st action="bookmaker.php">
<br>

<center>
<input type="radio" name="main_res" value="1"> Победит <?=$row[0] ?>
<input type="radio" name="main_res" value="2"checked="1"> Ничья в основное время
<input type="radio" name="main_res" value="3"> Победит <?=$row[1] ?> <br> <br>
<input type=textfield style='width: 35px' size='4' maxlength='4' name="set_stav"> <br><br>
<input type="hidden" name="match" value="<?=$arg_id?>">
<input type=submit name="stav" value="Сделать ставку" >
</center>
</center>
</form>

<?                                                                                                                                                                                                                     
?>
</table>
<?
?>
