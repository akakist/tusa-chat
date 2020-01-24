<?
	session_start();
	include "inc/conf.php";
	include "inc/db_conn.php";
	check_conn();
	if(!isset($_SESSION['login']))
	{
		?>
		<script> window.top.location='/'; </script>
		<?
	}
	$uid=$_SESSION['uid'];
	$login=$_SESSION['login'];
  
  if ($uid)
  {
      list($level,$last_status_id,$last_channel,$last_nick_id)=select_1_row("select level,last_status_id,last_channel,last_nick_id from tbl_users where id='$uid'");
      $cansettopic=$level>499;
      $msglen=select_1("select msg_len from levels where id='$level'");
      $moderated=select_1("select moderated from channels where id='$last_channel'");
?>
<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1251">
<TITLE>add message</TITLE>
</head>

<LINK href="/css/main.css" rel=stylesheet type=text/css>

<script>



var can_set_topic=<?=isset($cansettopic)?>;
var last_date=new Date();

function ch_top()
{
	var z=prompt('Топик',parent.topic);
	if(z==null) return false;
	window.top.buttons.document.sf.cmd.value='topic';
	window.top.buttons.document.sf.msg.value=z;
	window.top.buttons.document.sf.submit();
	return false;
}

function ch_voice()
{
	var z=prompt('Кому дать/забрать голос? Введите ник..','');
	if(z==null) return false;
	window.top.buttons.document.sf.cmd.value='vmode';
	window.top.buttons.document.sf.msg.value=z;
	window.top.buttons.document.sf.submit();
	return false;
}

function ch_mode()
{
	window.top.buttons.document.sf.cmd.value='cmode';
	window.top.buttons.document.sf.submit();
	return false;
}



msgs = new Array();
max_m  = 0;
curr_m = 0;

function XMM2RUS (obj) {
	chrs=" !Э№;%?э()*+б-ю.0123456789ЖжБ=Ю,\"ФИСВУАПРШОЛДЬТЩЗЙКЫЕГМЦЧНЯх/ъ:_ёфисвуапршолдьтщзйкыегмцчняХ\\ЪЁ"
	so=document.sendform.msgbox.value;
	s=""
	for (i=0;i<so.length;i++){
		ch = so.charAt(i).charCodeAt();
		s+=ch<0x80 ? chrs.charAt(ch-0x20) : so.charAt(i);
	}
	document.sendform.msgbox.value=s;
	document.sendform.msgbox.focus();
}

function on_key(code)
{
	if(code==113){XMM2RUS(); return false;}
	if(code==118){document.tmpform.privbox.checked=!document.tmpform.privbox.checked; return false;}
	if(code==119){document.tmpform.makeitbox.checked=!document.tmpform.makeitbox.checked; return false;}
	if(code==27) {document.sendform.msgbox.value=''; return false;}
	if(code!=38 && code!=40) return true;
	if(max_m<=0) return true;
	if(code==38 && curr_m>0) curr_m--;
	if(code==40 && curr_m<max_m) curr_m++; 
	s = "";
	if(curr_m<max_m) s=msgs[curr_m];
	document.sendform.msgbox.value=s;
	return false;
}

function DoSend()
{
    parent.mm(0);
	var d=document.sendform;
	var d1=document.tmpform;
	if (d.msgbox.value=='')
	{
		d.msgbox.focus();
		return false;
	}
        d.msg.value=d.msgbox.value;
        if(d1.makeitbox.checked)
        {
        	d.makeit.value="on";
	}else{d.makeit.value="";}
        if(d1.privbox.checked)
        {
        	d.priv.value="on";
	}else{d.priv.value="";}
	msgs[max_m]=d.msgbox.value;
	max_m++;
	curr_m=max_m;
	d.msgbox.focus();
	d.msgbox.value="";
	d1.makeitbox.checked=false;
	d.fornick.value=d1.fornick.value;
	<?
	if($level>899)
	{
	?>
	if(d1.sysbox.checked){
		d.sys.value='on';
	}else{
		d.sys.value='';
	}
	d1.sysbox.checked=false;
	<?
	}
	?>

	d.submit();

	secs=last_date.getSeconds();
	dt2=new Date();
	secs2=dt2.getSeconds();
	var psec;
	if(secs>secs2){
		psec=(60-secs)+secs2;
	}else{
		psec=secs2-secs;
	}
	if(psec>=30){
		last_date=new Date();
//		parent.buttons.adv.document.location.reload();
	}
	return true;
}

function ChSt()
{
    parent.mm(0);
    parent.cstatus=document.StatusForm.status.selectedIndex;
	document.sendform.msgbox.focus();
	document.StatusForm.submit();
}

function set_status(n)
{
	parent.lstatus=parent.cstatus;
	document.StatusForm.status.selectedIndex=n;
	parent.cstatus=n;
	document.StatusForm.submit();
}

function DoAll()
{
	document.forms[1].fornick.value='Всем';
	document.sendform.msgbox.focus();
	document.tmpform.privbox.checked=false;
	document.tmpform.makeitbox.checked=false;
	return false;
}

function ch_scroll()
{
	if(document.StatusForm.scr.checked)
	{
		parent.scr=1;
	}
	else
	{
		parent.scr=0;
        }
        document.sendform.msgbox.focus();
}
//-->


</script>

<BODY OnMouseMove="parent.mm(0);" topmargin=3 onclick="window.top.messages.do_hide_menu()">

<TABLE vspace=0 border=0 cellspacing=0 cellpadding=0 height="100%">
<FORM method="POST" action="/chat.tse/sendmessage.tse" name="sendform" target="hidden" onSubmit="DoSend(); return false;">
<TR valign=top>
<TD align=center nowrap>
<input type="hidden" name="msg" value="">
<input type="hidden" name="priv" value="">
<input type="hidden" name="makeit" value="">
<input type="hidden" name="fornick" value="">
    <?
	if($level>899)
	{
    ?>
<input type=hidden name=sys>
    <?
	}
    ?>
<script>
<!--
z=screen.width;
s=37;
if(z<800){s=20;}
if(z==800){s=30;}
if(z==1024){s=60;}
if(z==1152){s=70;}
if(z>=1280){s=100;}

document.write('<input style="height: 20px" type="text" size="'+s+'" maxlength=<?=$msglen?> name="msgbox" value="" onKeyDown="return on_key(event.keyCode);">');
//-->
</script>
<input type="submit" style="height: 20px; border: solid 1px #004590;" value="OK">
</TD>
</form>
<form name="tmpform" onSubmit="DoSend(); return false;">
<TD width=5>&nbsp;</TD>
<TD nowrap>
<script>
s=12;
if(z==800) s=8;

document.write('<input style="height: 20px" type=text size='+s+' maxlength=16 name="fornick" value="Всем">');
</script>
<a title="Отправлять сообщения для всех" href="/chat/emptyframe.php" target="hidden" onMouseOver="window.status=''; return true;" onClick="return DoAll();"><B><small>Всем</small></b></a>
</TD>
<TD nowrap>
<small><input type="checkbox" class=c_b name="privbox" onClick="document.forms[0].msgbox.focus(); return true;">Личное&nbsp;</small>
<small><input type="checkbox" class=c_b name="makeitbox" onClick="document.forms[0].msgbox.focus(); return true;">Действие&nbsp;</small>

<?
	if($level>899)
	{
?>

<small><input type="checkbox" class=c_b name="sysbox" onclick="document.forms[0].msgbox.focus(); return true;">Системное</small>
<?
	}
?>
</td>
</FORM>
<FORM method="POST" action="/chat.tse/setstatus.tse" name="StatusForm" target="hidden">
<td align=center nowrap>
&nbsp;
<select name="status" OnChange="ChSt();">
<?

	$sm=array(2=>"Невидимка",3=>"Свободен",4=>"Хочу поговорить",5=>"Отошел",6=>"Занят",7=>"Не мешайте!",8=>"Отсутствую");
	$sf=array(2=>"Невидимка",3=>"Свободна",4=>"Хочу поговорить",5=>"Отошла",6=>"Занята",7=>"Не мешайте!",8=>"Отсутствую");


	if($_SESSION['gender']==1)
	{
		foreach($sm as $key=>$val)
		{
			echo "<OPTION value=$key";
			if($last_status_id==$key) echo " selected";
			echo "> $val\n";
		}
	}
	else
	{
		foreach($sf as $key=>$val)
		{
			echo "<OPTION value=$key";
			if($last_status_id==$key) echo " selected";
			echo "> $val\n";
		}
	
	}

		$sql="select id,name from user_status where uid='$uid' order by 1";
		$result=mysql_query($sql) or die(mysql_error());
    		while ($row=mysql_fetch_row($result)){
		    if(count($row)==2)
		    {
			$stid=$row[0];
			$nm=$row[1];
			echo "<OPTION value=$stid";
			if($last_status_id==$stid) echo " selected";
			echo "> $nm\n";
		    }
		}	
        
?>

</select>
<script>
	parent.cstatus=document.StatusForm.status.selectedIndex;
</script>
<small><input type="checkbox" class=c_b name="scr" OnClick="ch_scroll(); return true;" checked title="Скроллировать страничку">Скроллинг</small>
</TD>
</TR>
<tr>
<td colspan=5 align=left>
<div id="addpanel1">
<input type=button value="XMM2RUS" onclick="XMM2RUS(this)" title="Перекодировать">
<!--input type=button value="Скрыть общ. сообщ." onclick="parent.messages.hide_msgs(this,7)" title="Скрыть сообщения, написанные не для Вас" style="width: 125">
<input type=button value="Скрыть систем. сообщ." onclick="parent.messages.hide_msgs(this,8)" title="Скрыть системные сообщения" style="width: 125">-->
<script>
if(can_set_topic) document.write('<input type=button value="Сменить топик" onclick="return ch_top()" title="Сменить топик комнаты"  style="width: 125">&nbsp;');
if(parent.level>=9){
	document.write('<input type=button value="Дать голос (+v)" onclick="return ch_voice()" title="Дать/забрать пользователю возможность писать. (+v)"  style="width: 125">&nbsp;');
	document.write('<small><input type=checkbox name=moderated onclick="return ch_mode();" class=c_b <?if($moderated){echo "CHECKED";}?>> Модерируемый (+m)</small>');
}
</script>
</div>
</td>
</tr>
</FORM>
</TABLE>
</BODY>
</HTML>
<?
    }  //if
?>