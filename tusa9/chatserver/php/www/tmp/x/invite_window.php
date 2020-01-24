<?
	session_start();
      import_request_variables("gp", "arg_");
	include "inc/conf.php";
	include "inc/db_conn.php";
	include "inc/unescape_rus.php";
	check_conn();
	if(!isset($_SESSION['uid']))
	{
		header("Location: /c2/");die;
	}
	$uid=$_SESSION['uid'];
	$login=$_SESSION['login'];
  
      list($setting_invite_sound,$last_nick)=mysql_select1row("select setting_invite_sound, last_nick from tbl_users where id='$uid'");
?>

	<html> <title>Чат \"Тусовка\" - <?unescape_rus($arg_time)?></title>
	<LINK rel="stylesheet" type="text/css" href="/c2/css/main2.css">
	
	<script src="invite_user.js" type="text/javascript"></script>
	
	<BODY>
	
<?	
	if($setting_invite_sound){
		echo "<bgsound src=ringout.wav>";
	}
?>	
	<table border=0 width=100%>
	<tr><td>Пользователь <font class=nick><b><?unescape_rus($arg_who)?>
	</b></font> пытается привлечь внимание <font class=nick><b><?=$last_nick?></b></font>
	</td></tr>
	<?
	if (isset($arg_txt) && strlen($arg_txt)){
	
		?>
		<tr>
			<td width='90%' valign='top'><font class=yelmsgnb><?=unescape_rus($arg_txt)?></font></td>
			<td valign=top>
				<form name=frm>
					<input name=repl type=button OnClick="InviteUser('<?=unescape_rus($arg_who)?>',<?=$arg_sid?>);	window.close();" value="Ответить" class=b_l>
				</form>
			</td>
		</tr>
		<?
	}
	?>
	</table></html>
