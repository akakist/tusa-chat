<?
	$changed=false;
	if($_SERVER['REQUEST_METHOD']=="POST"){
	
		if($arg_fname==""){
			echo "Ошибка в имени";
			exit();
		}
//		if(!isset($arg_b_day)) $arg_b_day=0;
		if($arg_gender!="1" && $arg_gender!="2"){
			echo "Ошибка в поле";
			exit();
		}
		if($arg_b_day<1 || $arg_b_day>31){
			echo "Ошиюка в дате";
			exit();
		}
		if($arg_b_mon<1 || $arg_b_mon>12){
			echo "Ошибка в месяце";
			exit();
		}
		if($arg_b_day_show<0 || $arg_b_day_show>2){
			echo "Ошибка в дате показа";
			exit();
		}
		if($arg_city==0){
			if($arg_other_city==""){
				echo "Ошибка в городе";
				exit();
			}
		}
		if($arg_city==0){
			mysql_query("insert into cities (name) values ('$arg_other_city')");
		}

		$r=mysql_query(
			"update tbl_users set fname='$arg_fname', lname='$arg_lname', ".
			"gender='$arg_gender', b_day='$arg_b_day', b_mon='$arg_b_mon', ".
			"b_year='$arg_b_year', b_day_show_mode='$arg_b_day_show', city='$arg_other_city', moderated=0 where id=$uid"
		) or die(mysql_error());
		$changed=true;
	
	}
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"> 
<html> 
<head> 
    <title>ТУСОВКА</title>
    <META http-equiv=Content-Type content="text/html; charset=windows-1251"> 
    <link rel="stylesheet" href="/styles/main.css" type="text/css">
    <link rel="icon" href="/images/favicon.gif" type="image/gif">
</head>

<script language="javascript" src="/js/ajax.js"></script>
<script language="javascript" src="/js/profile_edit.js"></script>

<body>


<table cellspacing=0 cellpadding=0 height=105 width=100% style="z-index: -1; position: absolute; top: 0px; left: 0px"><tr><td style="background-color: #efeff7">&nbsp;</td></tr></table>


<center>
<table width=1000 cellspacing=0 cellpadding=0 border=0>
<tr>
<td>

<!--begin page, logo -->
<?
	include "inc/buttons_logged.php";
?>
<!-- columns -->

<table cellpadding=0 cellspacing=0 border=0 width=100%>
    <tr>
<?
	include "inc/menu.php";
?>
	<td width=10>
	    <img src=/images/pix.gif>
	</td>

<?
	$r=mysql_query("select city,b_day,b_mon,b_year,b_day_show_mode,fname,lname,gender from tbl_users where id=$uid");
	$params=mysql_fetch_array($r);
?>
	<td width=650 valign=top align=left>
		<div id=profile class=profile_edit>
			<div class=profile_top>Моя анкета &raquo; Основное</div>
<?
	if($changed){
?>
				<br><font color=darkblue>&nbsp;&nbsp;Изменения сохранены!</font><br><br>
<?
	}
?>
				<div style="border-bottom: 1px solid #d8dfea; margin-left: 5px; margin-right: 5px; margin-top: 10px; width: 627px; height: 25px;">
					<div class=main_menu_sel id=pb0><a href="?page=1">Основное</a></div>
					<div class=main_menu_unsel id=pb1><a href="?page=2">Контакты</a></div>
					<div class=main_menu_unsel id=pb2><a href="?page=3">Образование</a></div>
					<div class=main_menu_unsel id=pb3><a href="?page=4">Работа</a></div>
					<div class=main_menu_unsel id=pb3><a href="?page=5">Интересы</a></div>
				</div>

				<div class=profile_main_content id=profile_main_content style="width: 625px">
				<br>
				<hr>

				<form class=profile_edit_form style="border: 0px solid black" method=post name=f onsubmit="return submit_page1();">
				<div>
					<p><label for=fname>Имя:</label> <input type=text id=fname name=fname maxlength=32 value="<?=$params['fname']?>"><small>Мы удаляем тех, кто пишет</small></p>
					<p><label for=lname>Фамилия:</label> <input type=text id=lname name=lname maxlength=32 value="<?=$params['lname']?>"><small>ерунду вместо имени и фамилии.</small></p> <!--"-->
					<p><label>Пол:</label>
						<select name=gender id=gender>
						<option <? if($params['gender']=='1') echo 'checked'; ?> value=1>мужской
						<option <? if($params['gender']=='2') echo 'checked'; ?> value=2>женский
						</select>
					</p>
					<p><label>День рождения:</label>
						<select name=b_day style="width: 60px">
						<option value=0>день:
<?
	for($i=1; $i<=31; $i++){
//		echo $params["b_day"],"-",$params["b_day"]==$i,"\n";
		echo "<option ",selected2($params["b_day"],$i)," value=$i>$i";
	}
?>						
						</select>
						
						<select name=b_mon style="width: 80px; margin-left: 10px">
						<option value=0>месяц:
<?
	for($i=1; $i<=12; $i++){
		echo "<option ",selected2($params["b_mon"],$i)," value=$i>",rus_months($i);
	}
?>
						</select>
						
						<select name=b_year style="width: 100px; margin-left: 10px">
						<option value=0>год:
<?
	$lt=localtime(time());
	$y=$lt[5]+1900;
	for($i=$y-80; $i<$y-10; $i++){
		echo "<option ",selected2($params["b_year"],$i),"value=$i>$i";
	}
?>
						</select>
					</p>
					<p><label>Я хочу чтобы:</label>
						<select name=b_day_show id=b_day_show style="width: 268px">
						<option value="0" <?=selected2($params['b_day_show_mode'],0)?>>все видели мою дату рождения
						<option value="1" <?=selected2($params['b_day_show_mode'],1)?>>все видели только месяц и день
						<option value="2" <?=selected2($params['b_day_show_mode'],2)?>>никто не видел мою дату рождения
						</select>
					</p>
					<p><label>Я живу в городе:</label>
						<select name=city id=city onchange="check_city();">
<?
	$r=mysql_query("select * from cities order by name");
	while($row=mysql_fetch_array($r)){
		echo "<option ",selected2($params['city'],$row['name'])," value=",$row['ID'],">",$row['name'];
	}
?>
						<option value=0>Другой...
						</select>
					</p>
					<p id=other_city_div style="display: none"><label>&nbsp;</label> <input type=text maxlength=32 id=other_city name=other_city></p>

				</div>
			</div>

			<br>
			<center><input type=submit value="Сохранить" name=sub></center>
			</form>
			<br><br>
		
		</div>	<!-- end profile -->
				<br><center>(C) 1999-2008г.</center>
	</td>

	<td width=20>
	    <img src=/images/pix.gif>
	</td>
	<td width=150 valign=top>
	    Реклама
	</td>
    </tr>
</table>


<!-- end columns -->

<!-- end of page -->
</td>
</tr>
</table>
