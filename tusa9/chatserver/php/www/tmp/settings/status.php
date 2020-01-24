<?
	session_start();
        import_request_variables("gp", "arg_");
	
	include "inc/db_conn.php";
	include "inc/conf.php";
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
function checked($c)
{
	if($c>0) return "CHECKED";
	return "";
}

  ?>
<html>
<head>
  <meta http-equiv="PRAGMA" content="no-cache">
  <meta http-equiv="Content-Type" content="text/html; charset=windows-1251">

  <title>Чат "Тусовка"</title>
  <link rel="stylesheet" type="text/css" href="/css/main.css">
  <script language="javascript" src="/css/mmove.js" type="text/javascript"></script>
	<script type="text/javascript" src="/js/jquery.pack.js"></script>
</head>
<script  language="javascript">

function checkform()
{
	return true;
}

function do_add()
{
	document.form1.todo.value='add';
	document.form1.DATA.value='';
	document.form1.submit();
	return true;
}
function do_remove(n)
{
	document.form1.todo.value='remove';
	document.form1.sel.value=n;
	document.form1.DATA.value='';
	document.form1.submit();
	return true;
}

var selwin=0;

function do_select(z)
{
	url=unescape('/settings/st_pic.php?n='+z);
	if(!selwin || selwin.closed)
	{
//		selwin=open(url, 'SelPic', 'toolbar=0,status=0,resizable=0,scrollbars=0,width=600,height=300');
		selwin=open(url, 'SelPic', 'toolbar=1,status=1,menubar=1,resizable=1,scrollbars=1,width=600,height=300');
	}
	else
	{
		selwin.focus();
		selwin.location=url;
	}
}


</script>

<script  language="javascript">
<!--


//-->
</script>

<?

	if(isset($arg_todo))
	{
	if($arg_todo=="add")
	{

		mysql_query("insert into user_status(uid,name,disable_invite,pic) values ('$uid','Без имени','0','1')")  or die(mysql_error());;
		mysql_query("insert into ext_events (event) values ('flush tbl_users $uid')")  or die(mysql_error());;
	}
	else if($arg_todo=="update")
	{
		
		$result=mysql_query("select id,pic from user_status where uid=$uid order by id") or die(mysql_error());
    		while ($row=mysql_fetch_row($result)){
		    {
		    	$id=$row[0];
			$pic=$row[1];
			$s=$_REQUEST["st$id"];
			if(strlen($s)>35) $s=substr($s,0,35);
			$s=preg_replace("/\&/","&amp;",$s);
			$s=preg_replace("/\</","&lt;",$s);
			$s=preg_replace("/\>/","&gt;",$s);
			$s=preg_replace("/\"\\\\/","",$s);
			$pic=$_REQUEST["spi$id"];
			/*$pn=$STATUS_DIR."/sp$pic.gif";
			if(!stat($pn))
			{
				$pic=1;
			}*/
			$disable_invite=false;
			if(isset($_REQUEST["sc$id"]))$disable_invite=$_REQUEST["sc$id"]=="on";
			$sql="update user_status set name='".mysql_escape_string($s)."', pic='$pic', 
			disable_invite='$disable_invite' where id=$id and uid=$uid";

			mysql_query($sql) or die(mysql_error());
			mysql_query("insert into ext_events (event) values ('flush tbl_users $uid')") or die(mysql_error());;
			
		    }
		}	
		
	}
	else
	if($arg_todo=="remove")
	{

		mysql_query("delete from user_status where id=$arg_sel and uid=$uid") or die(mysql_error());
		mysql_query("insert into ext_events (event) values ('flush tbl_users $uid')")  or die(mysql_error());;
	}
	}
?>
<body>

  <table border="0" width="100%" cellspacing="0" cellpadding="0">
  <?
    include 'diz/head_row.php';
  ?>

    <tr height="5">
      <td colspan="5"></td>
    </tr>

    <tr valign="top">
	<?
	    include 'diz/left_col.php';
    	?>

      <td></td>

      <td>
      <!--START-->
 
<FORM method="POST" name="form1" onSubmit="return checkform();">
<table width=100% border=0 cellspacing=0 cellpadding=0>
<tr><td class=border align=center><b>Настройки - статусы</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>

<input type=hidden name="DATA" value="YES">

<FIELDSET>
<LEGEND class=leg><big><b>Выберите категорию</b></big></LEGEND>
<br>
<input class=bp type=button value="Статусы" style="font-size: 10pt">
<input type=button value="Чат" style="font-size: 10pt" onclick="location='/settings/chat.php'">
<input type=button value="Цвета" style="font-size: 10pt" onclick="location='/settings/colors.php'">
<input type=button value="Кредиты" style="font-size: 10pt" onclick="location='/settings/credits.php'">
<input type=button value="Привилегии" style="font-size: 10pt" onclick="location='/settings/privs.php'">
<br><br>
</fieldset>
<br>

<FIELDSET>
<LEGEND class=leg><big><b>Статусы</b></big></LEGEND>


<TABLE border=0 cellspacing=3 cellpadding=3>
<TR valign=top>
<TD>Описание&nbsp;</TD><TD colspan=2>Картинка<br><br></TD><td align=center>Отключить функцию "позвать"<br> для этого статуса?</td>
</TR>
<!--tr><td>~st3~</td><td><img src="/pics/s/sp1.gif" width=16 height=16></td><td></td><td align=center><input type=checkbox class=c_b disabled></td></tr>
<tr><td nowrap>~st4~</td><td><img src="/pics/s/sp2.gif" width=16 height=16></td><td></td><td align=center><input type=checkbox class=c_b disabled></td></tr>
<tr><td nowrap>~st5~</td><td><img src="/pics/s/sp3.gif" width=16 height=16></td><td></td><td align=center><input type=checkbox class=c_b disabled></td></tr>
<tr><td>~st6~</td><td><img src="/pics/s/sp4.gif" width=16 height=16></td><td></td><td align=center><input type=checkbox class=c_b disabled></td></tr>
<tr><td>~st7~</td><td><img src="/pics/s/sp5.gif" width=16 height=16></td><td></td><td align=center><input type=checkbox class=c_b disabled checked></td></tr>
<tr><td>~st8~</td><td><img src="/pics/s/sp6.gif" width=16 height=16></td><td></td><td align=center><input type=checkbox class=c_b disabled></td></tr>
-->
<?

			    
		$result=mysql_query("select id,name,pic,disable_invite from user_status where uid=$uid order by id") or die(mysql_error());
    		while ($row=mysql_fetch_row($result)){
		    {
		    	$id=$row[0];
			$name=$row[1];
			$pic=$row[2];
			$disable_invite=$row[3];
			?>

<tr>
<td><input type=textfield name=st<?=$id?> maxlength=35 size=30 value="<?=$name?>"></td>
<td width=20><img name=sp<?=$id?> src="/pics/s/sp<?=$pic?>.gif" width=16 height=16></td>
<td><input type=button class=b_l value="Выбрать" 
onclick="do_select(<?=$id?>)"
>&nbsp;&nbsp;
<!--//alert('gfhdg'); 
$('#d<?=$id?>').load('choose_pic.php?n=<?=$id?>');-->
<!---->
	<a href="#" onclick="return do_remove('<?=$id?>')"><img border=0 src="/pics/del.gif" width=16 alt="Удалить статус"></a><input type=hidden name="spi<?=$id?>" value="<?=$pic?>"></td>
<td align=center><div id=d<?=$id?> >
<input class=c_b type=checkbox name="sc<?=$id?>" <?=checked($disable_invite)?> >
</div>
</td>
</tr> 

<!--"<??> " -->

			<?
			
		    }
		}	


?>

</TABLE>

<br>

<center><input type=button onclick="do_add();" value="Добавить статус" class=b_l><br>

<input type=hidden name="todo" value="update"><br>
<input type=hidden name="sel" value=""><br>

Если Вы сделали здесь изменения, то не забудьте нажать на кнопку <b>"Изменить"</b><br>
<br>
<input type=submit value="Изменить" class=b_l>
</center>

</FIELDSET>


</div>
</td></tr>
</table>
</form>
<div id=dialog>
</div>
 
      <!--END-->
      </td>

      <td></td>

      <td>
        <?
            include 'inc/user_list.php';
        ?>
      </td><!-- up to 22 may-->
    </tr>
  </table>

  <p align="left"> </p>
  <hr>

    <?
    include 'diz/bottom_table.php';
    ?>

    
</body>
</html>
