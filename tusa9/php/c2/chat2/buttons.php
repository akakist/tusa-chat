<div style='float: left; margin:3px'>
<?
	if($level>599)echo "<IMG SRC=\"/pics/cc/panel_adm.gif\" WIDTH=117 HEIGHT=60 BORDER=0 USEMAP=\"#panel_Map\">";
	else echo "<IMG SRC=\"/pics/cc/panel.gif\" WIDTH=117 HEIGHT=60 BORDER=0 USEMAP=\"#panel_Map\">";
?>
	<MAP NAME="panel_Map">

		<AREA SHAPE="rect" ALT="Форум" COORDS="51,2,70,20" HREF="/c2/forum/forum.php" target=_new>
		<AREA SHAPE="rect" ALT="Помошь" COORDS="26,2,43,20" HREF="/c2/help/index.php" target=_new>
		<AREA SHAPE="rect" ALT="Главная страница" COORDS="3,2,19,20" HREF="/c2/" target=_new>
<?
		    if($level>599)
		    {
?>
			<AREA SHAPE="rect" ALT="Консоль админа" COORDS="81,39,97,58" HREF="#" onclick="n=window.open('/c2/admin/index.php','admpage','toolbar=0,status=0,scrollbars=0,width=450,height=500'); n.focus(); return false;">
<?
		    }
?>

		<AREA SHAPE="rect" ALT="Записки" COORDS="51,40,69,58" HREF="#" onclick="return open_n('');">
		<AREA SHAPE="rect" ALT="Настройки чата" COORDS="28,40,44,58" HREF="/c2/settings/status.php" target=_new>
		<AREA SHAPE="rect" ALT="Сменить инфу" COORDS="3,40,18,57" HREF="/c2/settings/info.php" target=_new>
		<AREA SHAPE="rect" ALT="Покинуть чат" COORDS="1,23,115,36" HREF="#" onclick="return exit_chat()">
		<AREA SHAPE="rect" ALT="Галерея" COORDS="80,2,95,20" HREF="#" onclick="return o_l('/c2/gallery.php')"> 

	</MAP>
</div>
	<span style='position: relative;top:25px;left: 20px;'><a href='/c2/settings/credit.php' target=_blank>Кредиты</a></span>
	<span style='position: relative;top:25px;left: 20px;'><a href='/c2/settings/fotki.php' target=_blank>Фотки</a></span>
	<span style='position: relative;top:25px;left: 20px;'><a href='/c2/settings/status.php' target=_blank>Статусы</a></span>
	<span style='position: relative;top:25px;left: 20px;'><a href='/c2/settings/priv.php' target=_blank>Привилегии</a></span>
	<span style='position: relative;top:25px;left: 40px;'> <a href="http://billex.tomsk.ru" target=_new><font color=red><big>BillEX</big></font> - антикризисная система расчетов между гражданами</a></span>

<!--span style='position: relative;top:25px;left: 90px;'>
<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab##version=9,0,0,0" width="88" height="31" id="bn34" border="0">
<param name="AllowScriptAccess" value="always" /> <param name="movie" value="http://abc.russpartner.com/image?p=992&b=34&r=545" /> <param name="FlashVars" value="link=http://www.russiancasino.ru/p/992/b/34/r/545.html"/><param name="menu" value="false" /><param name="quality" value="high" /><param name="scale" value="exactfit" />
<embed src="http://abc.russpartner.com/image?p=992&b=34&r=545" menu="false" quality="high" width="88" height="31" name="bn34" FlashVars="link=http://www.russiancasino.ru/p/992/b/34/r/545.html" type="application/x-shockwave-flash" pluginspace="http://www.macromedia.com/go/getflashplayer" AllowScriptAccess="always"></embed></object>
</span-->	

<div style='float:right;'>
	<form name=buttonsform>






		<div style='margin: 5px'>
		<table>
		<tr>
			<td class=gr align=right>Ник:&nbsp;</td>
			<td>
				<select name=nick onchange='change_nick();' class=bsel>
<?
		$result=mysql_query("select id,nick from nicks where uid='$uid' order by nick") or die(mysql_error());
    		while ($row=mysql_fetch_row($result)){
			$id=$row[0];
			$n=$row[1];
			
			echo "<option value=$id";
			if($id==$last_nick_id) echo " SELECTED";
			echo ">$n\r\n";
		    $i++;
		}	
?>
			    </select>
			
			</td>
		</tr>	

		<tr>
			<td class=gr align=right>Тусуемся в:&nbsp;</td>
			<td><?=$c_select?></td>
		</tr>	
		</table>
		</div>
	</div>
</form>