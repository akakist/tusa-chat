<?
	session_start();
	header("Content-Type: text/html; charset=\"windows-1251\"");
	include "../inc/db_conn.php";
	include "../inc/func.php";
?>

	<p class=reg_header>�����������</p>
	<form method=post action="/registration.php" class=reg_form name=reg_form onsubmit="submit_reg(); return false;">
	<b>����������, �������������:</b>
	<hr size=1>
	
	<p><label for=rnick>Nickname:</label> <input type=text id=rnick name=rnick maxlength=16 onchange="check_nick();"><small id=nickhelp>��� ��� ��� ���������.</small></p>
	<p><label for=fname>���:</label> <input type=text id=fname name=fname maxlength=32><small id=fnamehelp>������� ���� ��������� ���.</small></p>
	<p><label for=rpasswd>������:</label> <input type=password id=rpasswd name=rpasswd maxlength=16><small id=rpasswdhelp>�� ����� 3� ��������...</small></p>
	<p><label for=rpasswd2>��� ���:</label> <input type=password id=rpasswd2 name=rpasswd2 maxlength=16></p>

	<b>������� � ���:</b>
	<hr size=1>
	<p><label>�</label>
	<input type=radio checked name=gender id=male style="width: 20px; margin-left: 45px; float: left"> <label for=male style="margin-left: 0px; float: left;">������</label>
	<input type=radio name=gender id=female style="width: 20px; margin-left: 45px; float: left"> <label for=female style="margin-left: 0px; float: left;">�������</label>
	</p><br><br>
	<p><label>���� �:</label>
	    <select name=city id=city onchange="return check_city();">
<?
	$r=mysql_query("select * from cities order by name") or die(mysql_error());
	while($row=mysql_fetch_array($r)){
		echo "<option ",selected2('�����',$row['name'])," value=",$row['ID'],">",$row['name'];
	}
?>
		<option value=0>������...
	    </select>
	    <small>��� ������ �����</small></p>
	<p id=other_city_div style="display: none"><label for=other_city>�����:</label> <input type=text maxlength=32 id=other_city name=other_city></p>
	
	<br>
	<b>�� ����� ���� �������� ��� �� - �������:</b>
	<hr size=1>
	<p><img src=/_keycode_image.php?<? echo session_name()?>=<? echo session_id()?>> <input type=text id=key name=key style="margin-left: 19px" maxlength=5><small id=keyhelp>������� ����� �� ��������.</small></p>
	<br>
	<center><input type=submit value="������������������" name=sub></center>
	<input type=hidden name=<? echo session_name()?> value=<? echo session_id()?> id=session>
	</form>
