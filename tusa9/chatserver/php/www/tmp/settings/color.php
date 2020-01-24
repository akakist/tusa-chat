<?
	session_start();
        import_request_variables("gp", "arg_");
	
	include "inc/conf.php";
	include "inc/db_conn.php";
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
  ?>
<html>
<head>
  <meta http-equiv="PRAGMA" content="no-cache">
  <meta http-equiv="Content-Type" content="text/html; charset=windows-1251">

  <title>Чат "Тусовка"</title>
  <link rel="stylesheet" type="text/css" href="/css/main.css">
  <script language="javascript" src="/css/mmove.js" type="text/javascript">
</script>
</head>

<script  language="javascript">
<!--

var imgnames=new Array();
<?
	if(isset($arg_DATA))
	{
		mysql_query("update tbl_users set setting_n_color_pack=$arg_ncolor where id=$uid") or die(mysql_error());
		mysql_query("insert into ext_events (event) values ('flush tbl_users $uid')") or die(mysql_error());

	}
		$result=mysql_query("select id,imagefname from chat_colors order by id") or die(mysql_error());
    		while ($row=mysql_fetch_row($result)){
		    if(count($row)==2)
		    {
		    	$cid=$row[0];
			$cname=$row[1];
        		echo "imgnames[$cid]='$cname';\n";
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
<table width=100% border=0 cellspacing=0 cellpadding=0>
<tr><td class=border align=center><b>Настройки - цвета</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>

<FORM method="POST" name="form1" onSubmit="return checkform();">
<input type=hidden name="DATA" value="YES">
<?
	$ncolor=mysql_select1("select setting_n_color_pack from tbl_users where id=$uid");
?>

<FIELDSET>
<LEGEND class=leg><big><b>Выберите категорию</b></big></LEGEND>
<br>
<input type=button value="Статусы" style="font-size: 10pt" onclick="location='/settings/status.php'">
<input type=button value="Чат" style="font-size: 10pt" onclick="location='/settings/chat.php'">
<input class=bp type=button value="Цвета" style="font-size: 10pt">
<input type=button value="Кредиты" style="font-size: 10pt" onclick="location='/settings/credits.php'">
<input type=button value="Привилегии" style="font-size: 10pt" onclick="location='/settings/privs.php'">
<br><br>
</fieldset>
<br>


<FIELDSET>
<LEGEND class=leg><big><b>Цвета</b></big></LEGEND>

<TABLE width="100%" border=0 cellspacing=0 cellpadding=3>
<tr><td colspan=2>

Здесь Вы можете выбрать цветовую схему Ваших сообщений.<br>
При выборе цветой схемы - обратите внимание на рисунок справа - вот так будут выглядеть Ваши сообщения.<br><br>
Вам доступны следующие цветовые схемы:
</td></tr>
<tr><td align=center width=50%>
<select name=ncolor onchange="return on_ch()">
<?
	sel_options("select id,name from chat_colors",$ncolor);
?>

</select>
</td>
<td align=right><img src="" name=im></td>
</tr>
</TABLE>

<script>
	on_ch();
</script>

</FIELDSET>

<br><center>
<input type=submit value="Изменить" class=b_l>
</center>

</form>


</div>
</td></tr>
</table>
      
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
