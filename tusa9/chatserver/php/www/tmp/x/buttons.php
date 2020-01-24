<div style='float: left'>
<?
	if($level>599)echo "<IMG SRC=\"/pics/cc/panel_adm.gif\" WIDTH=117 HEIGHT=60 BORDER=0 USEMAP=\"#panel_Map\">";
	else echo "<IMG SRC=\"/pics/cc/panel.gif\" WIDTH=117 HEIGHT=60 BORDER=0 USEMAP=\"#panel_Map\">";
?>
<MAP NAME="panel_Map">

<AREA SHAPE="rect" ALT="Форум" COORDS="51,2,70,20" HREF="/c2/forum/forum.php" target=_new>
<AREA SHAPE="rect" ALT="Помошь" COORDS="26,2,43,20" HREF="/c2/help" target=_new>
<AREA SHAPE="rect" ALT="Главная страница" COORDS="3,2,19,20" HREF="/c2/" target=_new>
<?
    if($level>599)
    {
?>
<AREA SHAPE="rect" ALT="Консоль админа" COORDS="81,39,97,58" HREF="#" onclick="n=window.open('/admin','admpage','toolbar=0,status=0,scrollbars=0,width=450,height=500'); n.focus(); return false;">
<?
    }
?>

<AREA SHAPE="rect" ALT="Записки" COORDS="51,40,69,58" HREF="#" onclick="return open_n('');">
<AREA SHAPE="rect" ALT="Настройки чата" COORDS="28,40,44,58" HREF="/settings/status.php" target=_new>
<AREA SHAPE="rect" ALT="Сменить инфу" COORDS="3,40,18,57" HREF="/registration/2.php" target=_new>
<AREA SHAPE="rect" ALT="Покинуть чат" COORDS="1,23,115,36" HREF="#" onclick="return exit_chat()">
<AREA SHAPE="rect" ALT="Галерея" COORDS="80,2,95,20" HREF="#" onclick="return o_l('/c2/gallery.php')"> 

</MAP>
</div>

<div style='float:right;'>
<form name=buttonsform>

<FONT class=gr>Ник:&nbsp;</FONT></td><td nowrap valign=bottom>
<select name=nick onchange='change_nick();' class=bsel>
<?
		$sql="select id,nick from nicks where uid='$uid' order by nick";
		$result=mysql_query($sql) or die(mysql_error());
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
 <input type=button value=">>" onclick="change_nick();" title="Сменить ник"><br>
 <FONT class=gr>Тусуемся в:&nbsp;</FONT></td><td nowrap><?=$c_select?> <input type=button value=">>" onclick="ch_room();" title="Перейти в комнату">

</div>
</form>