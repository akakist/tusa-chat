<?
	session_start();
	header("Content-Type: text/html; charset=\"windows-1251\"");
        import_request_variables("gp", "arg_");
	
	include "inc/db_conn.php";
	include "inc/str_nick.php";
	check_conn();
     if(isset($_SESSION['login']))
     {
     	$login=$_SESSION['login'];
	$uid=$_SESSION['uid'];
     }
     if(!isset($login))
     {
     	header("Location: /");
     }
?>

	<?
	
	
				$summa=abs($arg_summa);
//				$n=str_nick($arg_nick);
//echo $arg_nick;
//die;
				mysql_query("set charset utf8");
				$r=mysql_select1("select id  from nicks where nick='$arg_nick'");
				mysql_query("set charset cp1251");
#				echo count($r);
				list($zid,$nick)=mysql_select1row("select uid,nick from nicks where id='$r'");
#				print_r($r);
//				if(count($r)>=2)
//				{
////					$zid=$r[0];
//					$nick=$r[1];
				if(!isset($zid))
				{
					echo "<h3>Ник не найден</h3>";
				}
				else
				{
					$sum=mysql_select1("select credit_summa from tbl_users where id='$uid'");
					if($sum<$summa)
					{
						echo  "<h3>Недостаточно средств на счете</h3>";
					}
					else
					{
						mysql_query("update tbl_users set credit_summa=credit_summa-$summa where id='$uid'") or die(mysql_error());
						mysql_query("update tbl_users set credit_summa=credit_summa+$summa where id='$zid'") or die(mysql_error());
						echo  "<h3>С вашего счета списано $summa кредитов в пользу $nick</h3>";
						mysql_query("insert into ext_events (event) values ('flush tbl_users $uid')") or die(mysql_error());
						mysql_query("insert into ext_events (event) values ('flush tbl_users $zid')") or die(mysql_error());
						
						mysql_query("insert into ext_events (event,d1) values ('sysmsg $zid','Вам перечислено $summa кредитов от $login')") or die(mysql_error());
						mysql_query("insert into ext_events (event,d1,d2) values ('systemnote $zid','Перечисление кредитов','Вам перечислено $summa кредитов от $login')") or die(mysql_error());
					
					}
				}
////				}
//				else echo "<h1>Ник не найден N!2</h1>";
	
	?>

