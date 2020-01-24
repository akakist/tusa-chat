<?
	session_start();
	header("Content-Type: text/html; charset=\"windows-1251\"");
	include "../inc/db_conn.php";
	include "../inc/func.php";
?>

	<p class=reg_header>Регистрация</p>
	<form method=post action="/registration.php" class=reg_form name=reg_form onsubmit="submit_reg(); return false;">
	<b>Пожалуйста, представьтесь:</b>
	<hr size=1>
	
	<p><label for=rnick>Nickname:</label> <input type=text id=rnick name=rnick maxlength=16 onchange="check_nick();"><small id=nickhelp>Ваш ник или псевдоним.</small></p>
	<p><label for=fname>Имя:</label> <input type=text id=fname name=fname maxlength=32><small id=fnamehelp>Введите Ваше настоящие имя.</small></p>
	<p><label for=rpasswd>Пароль:</label> <input type=password id=rpasswd name=rpasswd maxlength=16><small id=rpasswdhelp>Не менее 3х символов...</small></p>
	<p><label for=rpasswd2>Еще раз:</label> <input type=password id=rpasswd2 name=rpasswd2 maxlength=16></p>

	<b>Немного о Вас:</b>
	<hr size=1>
	<p><label>Я</label>
	<input type=radio checked name=gender id=male style="width: 20px; margin-left: 45px; float: left"> <label for=male style="margin-left: 0px; float: left;">парень</label>
	<input type=radio name=gender id=female style="width: 20px; margin-left: 45px; float: left"> <label for=female style="margin-left: 0px; float: left;">девушка</label>
	</p><br><br>
	<p><label>Живу в:</label>
	    <select name=city id=city onchange="return check_city();">
<?
	$r=mysql_query("select * from cities order by name") or die(mysql_error());
	while($row=mysql_fetch_array($r)){
		echo "<option ",selected2('Томск',$row['name'])," value=",$row['ID'],">",$row['name'];
	}
?>
		<option value=0>Другой...
	    </select>
	    <small>Ваш родной город</small></p>
	<p id=other_city_div style="display: none"><label for=other_city>Город:</label> <input type=text maxlength=32 id=other_city name=other_city></p>
	
	<br>
	<b>Мы хотим быть уверенны что Вы - человек:</b>
	<hr size=1>
	<p><img src=/_keycode_image.php?<? echo session_name()?>=<? echo session_id()?>> <input type=text id=key name=key style="margin-left: 19px" maxlength=5><small id=keyhelp>Введите число на картинке.</small></p>
	<br>
	<center><input type=submit value="Зарегистрироваться" name=sub></center>
	<input type=hidden name=<? echo session_name()?> value=<? echo session_id()?> id=session>
	</form>
