<?
if ($_SESSION['ip']!=$_SERVER["REMOTE_ADDR"] || !isset($_SESSION['login']) ) //|| $_SESSION['level'])!=1000
    {
    $name = $_SERVER["SCRIPT_FILENAME"];
    $ip = $_SERVER["REMOTE_ADDR"];    $d = date('Y.m.d H:i:s');
    if (!isset($_SESSION['login'])) { $login = "ПУСТОЙ"; }    else { $login = $_SESSION['login']; }
    if (!isset($_SESSION['ip'])) { $ip1 = "ПУСТОЙ"; }    else { $ip1 = $_SESSION['ip']; }
    $tmp = "$name С IP $ip попытка войти в сессию логина $login (старый IP $ip1)";
    mysql_query("insert into adm_events (login,date_events,type_events,events) values('$login','$d','CRACK','$tmp')") or die(mysql_error());
    header("Location: /");
    }
                                    




	if(isset($arg_oldpass))
	{
		if($arg_pass1!=$arg_pass2)
		{
			$error="Несовпадение пароля с подтверждением";
		}
		
		if(md5($arg_oldpass)!=mysql_select1("select lower(pass) from tbl_users where id='$uid'")) $error="Неверный пароль";
		
		if(!isset($error))
			mysql_query("update tbl_users set pass=md5('$arg_pass1') where id='$uid'") or die(mysql_error());
		if(!isset($error))	
			$error='Пароль успешно изменен'	;
	}
	

?>

<div class='first-line'>Смена пароля</div>

<?
	if(isset($error)) echo "<div class='error'>$error</div>";
?>



<div style='text-align:center; margin-top:10px;padding-bottom:10px;line-height:20px'>
<style>
<br>
br{padding-bottom: 5px;}
td{
	text-align:right;
	margin:1px;
	padding: 1px;
}

</style>
<form method=post name='f'>
<center>
<table >
	<tr><td>Введите старый пароль</td><td><input type=password name=oldpass></td></tr>
	<tr><td>Новый пароль</td><td><input type=password name=pass1></td></tr>
	<tr><td>Подтверждение</td><td><input type=password name=pass2></td></tr>
	</tr>
</table>
	<input type='submit' value='Изменить'
	onclick='
		if(document.f.pass1.value!=document.f.pass2.value)
		{
			alert("Недовпадение паролей");
			return false;
		}
		return true;
		
	'>
	<input type=button onclick='window.location="/c2/url_login.php"' value="Назад" class=b_l>
	
</form>	
</div>