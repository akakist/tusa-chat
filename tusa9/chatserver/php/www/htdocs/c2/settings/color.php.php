<script  language="javascript">
<!--

var imgnames=new Array();
<?
	if(isset($arg_DATA))
	{
		mysql_query("update tbl_users set setting_n_color_pack=$arg_ncolor where id=$uid") or die(mysql_error().__FILE__.__LINE__);
			mysql_query("insert into ext_events (event) values ('cmd=flush obj=tbl_users uid=$uid')") or die(mysql_error().__FILE__.__LINE__);


	}
		$result=mysql_query("select id,imagefname from chat_colors order by id") or die(mysql_error().__FILE__.__LINE__);
    		while ($row=mysql_fetch_row($result)){
		    if(count($row)==2)
		    {
		    	$cid=$row[0];
			$cname=$row[1];
        		echo "imgnames[$cid]"."='$cname';\n";
		    }
		}	


?>


function on_ch()
{
	var z=document.form1.ncolor.options[document.form1.ncolor.selectedIndex].value;
	document.im.src=imgnames[z];
	return true;
}

function checkform()
{
	return true;
}

//-->

</script>
<div class='first-line'>Настройки - цвета</div>
<FORM method="POST" name="form1" onSubmit="return checkform();">
<input type=hidden name="DATA" value="YES">
<?
	$ncolor=mysql_select1("select setting_n_color_pack from tbl_users where id=$uid");
?>

<FIELDSET>
<LEGEND class=leg>Цвета</LEGEND>


Здесь Вы можете выбрать цветовую схему Ваших сообщений.<br>
При выборе цветой схемы - обратите внимание на рисунок справа - вот так будут выглядеть Ваши сообщения.<br><br>
Вам доступны следующие цветовые схемы:
</td></tr>
<tr><td align=center width='50%'>
<select name=ncolor onchange="return on_ch();">
<?
	sel_options("select id,name from chat_colors",$ncolor);
?>

</select>
</td>
<!--td align=right><img src="" name='im'></td-->
</tr>
</TABLE>

<script>
	on_ch();
</script>

</FIELDSET>

<br><center>
<input type=submit value="Изменить" class=b_l>
<input type=button onclick='window.location="/c2/url_login.php"' value="Назад" class=b_l>
</center>

</form>
