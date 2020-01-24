<?
	session_start();
	include "inc/conf.php";
	include "inc/db_conn.php";
	check_conn();
	$uid=$_SESSION['uid'];
	$login=$_SESSION['login'];
	if(!isset($_SESSION['login']))
	{
		?>
		<script> window.top.location='/'; </script>
		<?
	}
	$uid=$_SESSION['uid'];
	$login=$_SESSION['login'];
      list($level,$last_channel,$last_nick_id)=select_1_row("select level,last_channel,last_nick_id from tbl_users where id='$uid'");
?>
<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1251">
<TITLE>buttons</TITLE>
</head>

<LINK href="/css/main.css" rel=stylesheet type=text/css>

<script>
<!--
function open_n(param)
{
    w=780;
    h=500;
    if(param!='undefined'){
    	param='?'+param;
    }else{
    	param='';
    }
	nwin=open('/notes.tse/frames.tse'+param, 'notes', 'toolbar=0,status=0,resizable=1,scrollbars=1,left=10,top=10,width='+w+',height='+h);
	nwin.focus();
	return false;
}

function o_l(url)
{
	r=Math.round(Math.random(123)*1000);
	n=window.open(url,'wind'+r,'toolbar=1,menubar=1,status=1,location=1,status=1,resizable=1,scrollbars=1,personalbar=1,directories=1');
	return false;
}
rooms=new Array();
<?
		$sql="select name,id from channels order by id";
		$result=mysql_query($sql) or die(mysql_error());
		$i=0;
		$c_select="<select name=channel onchange='ch_room();' class=bsel>";
    		while ($row=mysql_fetch_row($result)){
			$n=$row[0];
			echo "rooms[$i]=\"$n\";\r\n";
			$c_select.="<option value=$row[1]";
			if($last_channel==$row[1]) $c_select.=" SELECTED";
			$c_select.=">$n\n";
		    $i++;
		}	
		$c_select.="</select>";
    
?>

function ch_room()
{
	r=Math.round(Math.random(123)*1000);
	window.top.messages.location='/chat.tse/messages.tse?r='+r+'&c='+document.sf.channel.value;//.selectedIndex;
	window.top.addmessage.document.SendForm.msgbox.focus();
}
function ch_nick()
{
	document.sf.id.value=document.sf.nick.options[document.sf.nick.selectedIndex].value;
	document.sf.cmd.value='nick';
	document.sf.submit();
	window.top.addmessage.document.SendForm.msgbox.focus();
}
function exit_chat()
{
	parent.ex=1;
	window.top.location='/chat.tse/exit.tse';
	return false;
}
//-->
</script>

<style>
a:link, a:hover, a:visited {font-size: 8pt;}
</style>

<BODY OnMouseMove="parent.mm(0);" leftmargin=4 topmargin=1 onclick="window.top.messages.do_hide_menu()">

<FORM method="POST" action="/chat.tse/cmd.tse" name="sf" target="hidden">
<input type=hidden name="id" value="">
<input type=hidden name="msg" value="">
<input type=hidden name="cmd" value="">
<input type=hidden name="on" value="">

<table border=0 cellpadding=0 cellspacing=0 width=100% height=100%>
<tr>

<td align=left valign=top rowspan=2>
<?
	if($level>599)echo "<IMG SRC=\"/pics/cc/panel_adm.gif\" WIDTH=117 HEIGHT=60 BORDER=0 USEMAP=\"#panel_Map\">";
	else echo "<IMG SRC=\"/pics/cc/panel.gif\" WIDTH=117 HEIGHT=60 BORDER=0 USEMAP=\"#panel_Map\">";
?>
<MAP NAME="panel_Map">

<AREA SHAPE="rect" ALT="Форум" COORDS="51,2,70,20" HREF="/forum/forum.php" target=_new>
<AREA SHAPE="rect" ALT="Помошь" COORDS="26,2,43,20" HREF="/help" target=_new>
<AREA SHAPE="rect" ALT="Главная страница" COORDS="3,2,19,20" HREF="/" target=_new>
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
<AREA SHAPE="rect" ALT="Галерея" COORDS="80,2,95,20" HREF="#" onclick="return o_l('/gallery.php')"> 

</MAP>
</td>

<td rowspan=2 align=center valign=center width=20%>
</td>


<td rowspan=2 align=center valign=center width=70%>
<a  onclick="return o_l('/settings/credits.php#cassa')" href="#"><b>КУПИТЬ КРЕДИТЫ</b> Внимание, новые номера для SMS и другие цены</a>
&nbsp;&nbsp;&nbsp;
</td>


<td align=right valign=bottom colspan=2>
<FONT class=gr>Ник:&nbsp;</FONT></td><td nowrap valign=bottom>
<select name=nick onchange='ch_nick();' class=bsel>
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
 <input type=button value=">>" onclick="ch_nick();" title="Сменить ник"></td>
</tr>

<tr>
<td align=left valign=top>
</td>

<td align=right nowrap><FONT class=gr>Тусуемся в:&nbsp;</FONT></td><td nowrap><?=$c_select?> <input type=button value=">>" onclick="ch_room();" title="Перейти в комнату"></td>
</tr>
</table>

</form>
</BODY>
</HTML>