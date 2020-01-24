<?
	session_start();
	header("Content-Type: text/html; charset=\"windows-1251\"");
        import_request_variables("gp", "arg_");
	
	include "inc/db_conn.php";
	check_conn();
     if(isset($_SESSION['uid']))
     {
	$uid=$_SESSION['uid'];
     }
     if(!isset($uid))
     {
     	header("Location: /");die;
     }
?>

	<?
	if(isset($arg_v))
	{
				$r=split("[\\-]",$arg_v);
				if(count($r)==3)
				{
					$v1=$r[0];
					$v2=$r[1];
					$v3=$r[2];
					$summa=mysql_select1("select summa from pincodes where v1='$v1' and v2='$v2' and v3='$v3' and accepted='0'");
					if(!$summa)
					{
						echo "<h1>Неверный пинкод</h1>";
					}
					else
					{
						mysql_query("update tbl_users set credit_summa=credit_summa+$summa where id='$uid'") or die(mysql_error().__FILE__.__LINE__);
						mysql_query("update pincodes set accepted='1' where v1='$v1' and v2='$v2' and v3='$v3'") or die(mysql_error().__FILE__.__LINE__);
						echo "Поздравляем, вам зачислено $summa кредитов";
					}
				}
				else
				{
						echo "<h1>Неверный пинкод</h1>";
						#print_r ($r);
				}		
	}
	else
	echo "!isset arg_v";
	?>

