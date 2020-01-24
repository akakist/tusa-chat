<?
	session_start();
	header("Content-Type: text/html; charset=\"windows-1251\"");
        import_request_variables("gp", "arg_");
	
	include "inc/db_conn.php";
	include "inc/str_nick.php";
	check_conn();
     if(isset($_SESSION['uid']))
     {
	$uid=$_SESSION['uid'];
	$login=$_SESSION['login'];
     }
     if(!isset($uid))
     {
     	header("Location: /");die;
     }
     if($uid==250489 || $uid==250489)
     {
	echo "<h1>Ник не найден N!2</h1>";        
	die;
     }
?>

	<?
	
	
				$summa=abs($arg_summa);
				mysql_query("set charset utf8");
				$r=mysql_select1("select id  from nicks where nick='$arg_nick'");
				mysql_query("set charset cp1251");
				list($zid,$nick)=mysql_select1row("select uid,nick from nicks where id='$r'");
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
						mysql_query("update tbl_users set credit_summa=credit_summa-$summa where id='$uid'") or die(mysql_error().__FILE__.__LINE__);
						mysql_query("update tbl_users set credit_summa=credit_summa+$summa where id='$zid'") or die(mysql_error().__FILE__.__LINE__);
						echo  "<h3>С вашего счета списано $summa кредитов в пользу $nick</h3>";
			mysql_query("insert into ext_events (event) values ('cmd=flush obj=tbl_users uid=$uid')") or die(mysql_error().__FILE__.__LINE__);
			mysql_query("insert into ext_events (event) values ('cmd=flush obj=tbl_users uid=$zid')") or die(mysql_error().__FILE__.__LINE__);
						
						
						mysql_query("insert into ext_events (event,d1) values ('cmd=sysmsg uid=$zid','Вам перечислено $summa кредитов от $login')") or die(mysql_error().__FILE__.__LINE__);
						mysql_query("insert into ext_events (event,d1,d2) values ('cmd=systemnote uid=$zid','Перечисление кредитов','Вам перечислено $summa кредитов от $login')") or die(mysql_error().__FILE__.__LINE__);
					
					}
				}
////				}
//				else echo "<h1>Ник не найден N!2</h1>";
	
	?>

