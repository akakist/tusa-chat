<script>
</script>

<?
if(isset($_SESSION['rega'])) unset ($_SESSION['rega']);

if(isset($arg_DATA))
{

	$channel=0;if(isset($arg_channel))$channel=intval($arg_channel);
	$nick=""; if(isset($arg_nick)) $nick=intval($arg_nick);
	$ininv=0; if(isset($arg_ininv)) $ininv=$arg_ininv=="on";
	$showadm=0; if(isset($arg_showadm))$showadm=$arg_showadm=="on";
	$eye=0;if(isset($arg_eye))$eye=intval($arg_eye);
	$strnick=mysql_escape_string(mysql_select1("select nick from nicks where uid='".intval($uid)."' and id='".mysql_escape_string($nick)."'"));
	mysql_query("update nicks set last_usage_date=NOW() where uid='".intval($uid)."' and id='".mysql_escape_string($nick)."'") or die(mysql_error().__FILE__.__LINE__);
	mysql_query("update tbl_users set last_channel='$channel',last_nick_id='".mysql_escape_string($nick)."',last_nick='".mysql_escape_string($strnick)."',setting_show_eye='$showadm', setting_neye='$eye', last_invis_state='$ininv' where id='".intval($uid)."'") or die(mysql_error().__FILE__.__LINE__);
	$ip=$_SERVER['REMOTE_ADDR'];
	mysql_query("update tbl_users set stat_last_ip='".mysql_escape_string($ip)."', stat_v_count=stat_v_count+1, stat_last_date=NOW() where id='$uid'") or die(mysql_error().__FILE__.__LINE__);
			
	echo "<script>window.top.location='/c2/chat2/';</script>";
	die;
}
list($name,$setting_show_eye,$setting_neye)=mysql_select1row("select name,setting_show_eye,setting_neye from tbl_users where id='$uid'");
include "$BASE_DIR/inc/date.php";
//print_r($_SESSION);
?>

<div class='first-line'>Здравствуйте, <?echo "$name";?></div>
<div class='text' style='text-align: center;'>Рады снова видеть Вас в нашем чате ;)<p style='padding-top:10px'>

		<a href='#' onclick='return open_n();'> Записки</a>
		<a href='/c2/settings/chat.php'> Настройки чата</a>
		<a href='/c2/settings/status.php'> Статусы</a>
		<!--a href='/c2/settings/color.php'> Цвета</a-->
		<a href='/c2/settings/credit.php'> Кредиты</a>
		<a href='/c2/settings/priv.php'> Привилегии</a>
		
		<a href='/c2/settings/info.php'> Инфа</a>
		<a href='/c2/settings/fotki.php'> Фотки</a>
		<a href='/c2/settings/chpass.php'> Смена пароля</a>

		
</div>

<?
list($stat_last_ip,$stat_v_count,$stat_m_count,$stat_t_count,$kick_count,$kicked_count,$credit_summa,$stat_last_date,$last_nick,$last_channel,$level,$unread_notes,$last_invis_state,$gender,$reg_date)=
mysql_select1row("select stat_last_ip,stat_v_count,stat_m_count,stat_t_count,kick_count,kicked_count,FORMAT(credit_summa,2),stat_last_date,last_nick,last_channel,level,unread_notes,last_invis_state,gender,reg_date from tbl_users where id='$uid'");
$lvname=mysql_select1("select name from level_names where id='$level' and gender='$gender'");
list($kick_shield,$kick_ability,$levelup_ability)=mysql_select1row("select kick_shield,kick_ability,levelup_ability from levels where id='$level'");
$max_nicks=mysql_select1("select a.nicks_count from levels a, tbl_users b where b.id='$uid' and b.level=a.id");
$inv=mysql_select1("select a.invisibility+b.bought_invisibility from levels a, tbl_users b where b.id='$uid' and b.level=a.id");
?>
	
<style>
table, caption, tbody, tfoot, thead, tr, th, td
{
background-position:0 0;
background-repeat:no-repeat;
border:0 none;
font-size:100%;
font-style:inherit;
font-weight:inherit;
margin:0;
padding:0;
text-align:left;
vertical-align:baseline;

}
</style>
<div class='black-border' style='text-align:center'>
<div class="second-line" style="border: none; border-bottom: 1px solid black">Вход</div>

	<center>
	<form action="/login.tse/settings.tse" name="tempform"><input type="hidden" name="removenick" value=""> <input type="hidden" name="nick" value=""></form>
	<form method="post" name="loginform" onsubmit="return chk_f();">
 		<input type=hidden name='DATA' value="YES">
			<center>
				<table align="center" border="0" cellpadding="4" cellspacing="4">
					<tr height="5"><td></td></tr>
				 	<tr>
						<td align="right">Ник: </td>
			 			<td>
							<?
							list($last_nick,$last_channel,$level,$unread_notes,$last_invis_state)=mysql_select1row("select last_nick,last_channel,level,unread_notes,last_invis_state from tbl_users where id='$uid'");
							$max_nicks=mysql_select1("select a.nicks_count from levels a, tbl_users b where b.id='$uid' and b.level=a.id");
							$inv=mysql_select1("select a.invisibility+b.bought_invisibility from levels a, tbl_users b where b.id='$uid' and b.level=a.id");
							?>
							<SELECT name="nick" id='_nick' onchange='ch_nick();' class=sl>
							<?
								$result=mysql_query("select id,nick from nicks where uid='$uid'") or die(mysql_error().__FILE__.__LINE__);
								$nick_count=mysql_num_rows($result);
 						 		while (list($nid,$n)=mysql_fetch_row($result)){
									echo "<OPTION VALUE=$nid";
									if($n==$last_nick){ echo " SELECTED";}
									echo ">$n\n";
								}	
			 				?>
							</SELECT>
							<?
							if($nick_count)
							{
								?>
								<a href="#" onclick="return remove_nick();"><img src="/pics/del.gif" border="0" width="16" height="16" alt="Удалить ник"></a>
								<?
				 			}
							if($nick_count<$max_nicks)
						 	{
								?>
									<input type="button" onclick="return AddNick();" value="Добавить ник" class="b_l">
								<?
							}
							?>
						 </td>
					 </tr>
					<tr>
						<td align="right">Тусуемся в: </td>
						<td>
							<SELECT name="channel" class=sl>
							<?
							$result=mysql_query("select id,name from channels order by id") or die(mysql_error().__FILE__.__LINE__);
							while (list($cid,$cname)=mysql_fetch_row($result)){
								echo "<OPTION VALUE='$cid'";
								if($cid==$last_channel){ echo " SELECTED";}
								echo ">$cname\n";
							}
			 
							 ?>
							 </SELECT>
						</td>
					</tr>
					<tr>
<?
$ip=$_SERVER["REMOTE_ADDR"];
list($time_cnt,$time_free,$descr)=mysql_select1row("select time_cnt,time_free,za from banned_ip where ip='".mysql_escape_string($ip)."' and time_free>NOW()");
if(isset($time_cnt) && ($level<900))
	{
	$error="Ваш IP адрес забанен за $descr на $time_cnt, дата окончания $time_free";
	$errscr= "<script> document.start.login.focus();</script>";
	}
else							
	{ ?>
						<td align="center"></td>
						<td align="center">
							<br>
							<input type="submit" value="Войти в чат" class="button" name="subbtn"> 
							<? 
							if($level>=600)
							{
							?>
								<br>
								<br>
								<input type="button" value="Консоль админа" onclick="n=window.open('/c2/admin/index.php','admpage','toolbar=0,status=0,scrollbars=0,width=450,height=500,resizable=1');n.focus();">
								<br>
						 	<?
						 	}
						 	}
						 	?>
<script type="text/javascript">
<!--
document.loginform.subbtn.focus();
//-->
</script><br>
							<?
						 	if($inv>0)
							{
								echo "<input type=checkbox class=c_b name=ininv ";
								if($last_invis_state) echo "CHECKED";
								echo ">Войти невидимым(ой)";
							}	
							if($level>=900)
							{
						 		?>
								 <br><input type=checkbox class=c_b name=showadm <?=$setting_show_eye?"CHECKED":""?>>Показывать 
								<SELECT name="eye" > 
								<OPTION value="0" <?=$setting_neye==0?"selected":""?> >Голубой глаз
								<OPTION value="1" <?=$setting_neye==1?"selected":""?>>Желтый глаз
								<?if($level>=1000){?>
									<OPTION value="2" <?=$setting_neye==2?"selected":""?>>Красный глаз
									<OPTION value="3" <?=$setting_neye==3?"selected":""?>>Зелёный глаз
									<OPTION value="4" <?=$setting_neye==4?"selected":""?>>Оранжевый глаз
								<?}?>
								</SELECT> глаз
								<?
							}
							?>
							<br>
							<?
							if($unread_notes>0)
							{
							 ?>
								У вас <?=$unread_notes?>. <a href="/notes">Читать?</a><br>
							 <?
							}
							?>
						</td>
					</tr>
					<tr height="15"><td></td></tr>
				</table>
			</center>	
	</form>

</div> <!--back-border-->
		
			
<div style='padding-top:10px'>
<div style='border: 1px solid black;' id='my_stat'>
	
	<div class="second-line" style="border: none; ">Моя статистика</div>
	
	<div style=' border-top: 1px solid black'>
		<table style='margin: 5px'>
			<tr>
				<td>Уровень</td><td class=tdr><?=$lvname?></td>
				<td>Последний IP</td><td class=tdr><?=$stat_last_ip?></td>
			</tr>
			<tr>
				<td>Дата регистрации</td><td class=tdr><?=get_rusdate($reg_date)?></td>
				<td>Заходов в чат</td><td class=tdr><?=$stat_v_count?></td>
			</tr>
			<tr>
				<td>Последний заход</td><td class=tdr><?=get_rusdate($stat_last_date)?></td>
				<td>Время в чате</td><td class=tdr><?=sprintf("%2.2f",$stat_t_count/3600)?> часов</td>
			</tr>
			<tr>
				<td>Кредитов</td><td class=tdr><?=$credit_summa?> &nbsp;&nbsp;&nbsp; <a href='/c2/settings/credit.php'>Пополнить</a></td>
				<td>Сообщений</td><td class=tdr><?=$stat_m_count?></td>
			</tr>
			<tr>
				<td>Невидимость</td><td class=tdr><?=$inv?></td>
				<td>У меня контактов</td><td class=tdr><?=mysql_select1("select count(*) from contact where uid='$uid'")?></td>
			</tr>
			<tr>
				<td>Кикнул</td><td class=tdr><?=$kick_count?></td>
				<td>Я в контактах</td><td class=tdr><?=mysql_select1("select count(*) from contact where cuid='$uid'")?></td>				
			</tr>
			<tr>
				<td>Кикнули</td><td class=tdr><?=$kicked_count?></td>
				<tr><td>Защита от кика</td><td class=tdr><?=$kick_shield?></td></tr>
			</tr>
			<tr>
				<td>Повышалка</td><td class=tdr><?=$levelup_ability?></td>
				<tr><td>Возможность кика</td><td class=tdr><?=$kick_ability?></td></tr>
			</tr>

		 </table>
	 </div>



		
	</div>
</div>
