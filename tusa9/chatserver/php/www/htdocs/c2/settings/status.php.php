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
	$('#status_select').load('st_pic.php?n='+z);
}

</script>
<?
//print_r($_REQUEST);
function checked($c)
{
	if($c>0) return "CHECKED";
	return "";
}


	if(isset($arg_todo))
	{
	if($arg_todo=="add")
	{
			mysql_query("set charset cp1251");

		mysql_query("insert into user_status(uid,name,disable_invite,pic) values ('$uid','Без имени','0','1')")  or die(mysql_error().__FILE__.__LINE__);;
			mysql_query("insert into ext_events (event) values ('cmd=flush obj=tbl_users uid=$uid')") or die(mysql_error().__FILE__.__LINE__);
	}
	else if($arg_todo=="update")
	{
		
		$result=mysql_query("select id,pic from user_status where uid='$uid' order by id") or die(mysql_error().__FILE__.__LINE__);
    		while (list($id,$pic)=mysql_fetch_row($result)){
		    {
			$s=$_REQUEST["st$id"];
			if(strlen($s)>35) $s=substr($s,0,35);
			$s=preg_replace("/\&/","&amp;",$s);
			$s=preg_replace("/\</","&lt;",$s);
			$s=preg_replace("/\>/","&gt;",$s);
			$s=preg_replace("/\"\\\\/","",$s);
			$pic=$_REQUEST["spi$id"];
			$disable_invite=false;
			if(isset($_REQUEST["sc$id"]))$disable_invite=$_REQUEST["sc$id"]=="on";
			//echo $s;
			mysql_query("set charset cp1251");
			$sql="update user_status set name='$s', pic='$pic', 
			disable_invite='$disable_invite' where id='$id' and uid='$uid'";

			mysql_query($sql) or die(mysql_error().__FILE__.__LINE__);

			mysql_query("insert into ext_events (event) values ('cmd=flush obj=tbl_users uid=$uid')") or die(mysql_error().__FILE__.__LINE__);
			
		    }
		}	
		
	}
	else
	if($arg_todo=="remove")
	{

		mysql_query("delete from user_status where id='$arg_sel' and uid='$uid'") or die(mysql_error().__FILE__.__LINE__);
			mysql_query("insert into ext_events (event) values ('cmd=flush obj=tbl_users uid=$uid')") or die(mysql_error().__FILE__.__LINE__);
	}
	}
?>
 
<div class='first-line'>Настройки - статусы</div>
<FORM method="POST" name="form1" onSubmit="return checkform();">
<input type=hidden name=todo value="update">
<input type=hidden name="DATA" value="YES">

    


<FIELDSET>
<LEGEND class=leg><big><b>Статусы</b></big></LEGEND>

<p>
<TABLE border=0 cellspacing=3 cellpadding=3>
    <TR valign=top><TD>Описание&nbsp;</TD><TD colspan=2>Картинка<br><br></TD><td align=center>Отключить функцию "позвать"<br> для этого статуса?</td></TR>
<?

			    
		$result=mysql_query("select id,name,pic,disable_invite from user_status where uid='$uid' order by id") or die(mysql_error().__FILE__.__LINE__);
    		while ($row=mysql_fetch_row($result)){
		    {
		    	$id=$row[0];
			$name=$row[1];
			$pic=$row[2];
			$disable_invite=$row[3];
			?>

    <tr>
	<td><input type=text name=st<?=$id?> maxlength=35 size=30 value="<?=$name?>"></td>
	<td width=20><img name='sp<?=$id?>' id='sp<?=$id?>' src="/pics/s/sp<?=$pic?>.gif" width=16 height=16></td>
	<td><input type=button class=b_l value="Выбрать" onclick="do_select(<?=$id?>)"> <!--"<??>"--> &nbsp;&nbsp;
	    <a href="#" onclick="return do_remove('<?=$id?>')"><img border=0 src="/pics/del.gif" width=16 alt="Удалить статус"></a><input type=hidden name="spi<?=$id?>" value="<?=$pic?>">
	</td>
	<td align=center><div id=d<?=$id?> ><input class=c_b type=checkbox name="sc<?=$id?>" <?=checked($disable_invite)?> ></div></td>
    </tr> 

<!--"<??> " -->

			<?
			
		    }
		}	


?>

</TABLE>
<br>

<center><input type=button onclick="
	document.form1.todo.value='add';
	document.form1.DATA.value='';
	document.form1.submit();
	return true;
	" value="Добавить статус"><br>

<input type=hidden name="sel" value=""><br>

Если Вы сделали здесь изменения, то не забудьте нажать на кнопку <b>"Изменить"</b><br>
<br>
<input type=submit value="Изменить" class=b_l>
<input type=button onclick='window.location="/c2/url_login.php"' value="Назад" class=b_l>

</center>

</FIELDSET>



</form>

<div id='status_select' style='padding-top:10px'>
</div>

