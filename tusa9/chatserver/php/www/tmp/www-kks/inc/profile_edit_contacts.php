<?
	$changed=false;
	$error=false;
	if($_SERVER['REQUEST_METHOD']=="POST"){
		if($arg_email_changed=="1"){
			$sid=mysql_select1("select pass from tbl_users where id=$uid");
			if(strtoupper(md5($arg_passwd))==$sid){
				mysql_query("update tbl_users set email='$arg_email' where id=$uid");
			}else{
				$error=true;
			}
		}
		if(!$error){
			$r=mysql_query(
				"update tbl_users set tel='$arg_tel', ".
				"icq='$arg_icq', homepage='$arg_homepage', contacts_show='$arg_contacts_show', ".
				"moderated=0 where id=$uid"
			) or die(mysql_error());
			$changed=true;
		}
	
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
	$r=mysql_query("select email,tel,icq,homepage,contacts_show from tbl_users where id=$uid");
	$params=mysql_fetch_array($r);
?>
	<td width=650 valign=top align=left>
		<div id=profile class=profile_edit>
			<div class=profile_top>Моя анкета &raquo; Контакты</div>
<?
	if($changed){
?>
				<br><font color=darkblue>&nbsp;&nbsp;Изменения сохранены!</font><br><br>
<?
	}
	if($error){
?>
				<br><font color=darkred>&nbsp;&nbsp;Пароль введен неверно!</font><br><br>
<?
	}
?>
				<div style="border-bottom: 1px solid #d8dfea; margin-left: 5px; margin-right: 5px; margin-top: 10px; width: 627px; height: 25px;">
					<div class=main_menu_unsel id=pb0><a href="?page=1">Основное</a></div>
					<div class=main_menu_sel id=pb1><a href="?page=2">Контакты</a></div>
					<div class=main_menu_unsel id=pb2><a href="?page=3">Образование</a></div>
					<div class=main_menu_unsel id=pb3><a href="?page=4">Работа</a></div>
					<div class=main_menu_unsel id=pb3><a href="?page=5">Интересы</a></div>
				</div>

				<div class=profile_main_content id=profile_main_content style="width: 625px">
				<br>
				<hr>

				<form class=profile_edit_form style="border: 0px solid black" method=post name=f onsubmit="return submit_page2();">
				<div>
					<p><label for=email>E-Mail:</label> <input type=text id=email name=email maxlength=32 onchange="show_pwd_line(); " value="<?=$params['email']?>"><small style="font-size: 8pt">ТОЛЬКО для восстановления пароля</small></p>
					<input type=hidden name=email_changed value=0>
					<p id=passwd_div style="display: none"><label for=passwd>Текущий пароль:</label> <input type=password id=passwd name=passwd maxlength=16><small>Требуется для безопасности</small></p> <!-- " -->
					<p><label for=tel>Телефон:</label> <input type=text id=tel name=tel maxlength=32 value="<?=$params['tel']?>"><small>Мобильный или домашний</small></p> 
					<p><label for=icq>ICQ:</label> <input type=text id=icq name=icq maxlength=32 value="<?=$params['icq']?>"></p> 
					<p><label for=homepage>Личный сайт:</label> <input type=text id=homepage name=homepage maxlength=32 value="<?=$params['homepage']?>"><small>Реклама здесь недопустима</small></p> 

					<p><label>Мои контакты:</label>
						<select name=contacts_show id=contacts_show style="width: 220px">
						<option value="0" <?=selected2($params['contacts_show'],0)?>>видят все зарегистрированные
						<option value="1" <?=selected2($params['contacts_show'],1)?>>видят только друзья
						<option value="2" <?=selected2($params['contacts_show'],2)?>>никто не видит
						</select>
					</p>

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
