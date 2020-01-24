<?
	session_start();
        import_request_variables("gp", "arg_");
	
	include "inc/db_conn.php";
	check_conn();
//	include "inc/check_login.php";
     if(isset($_SESSION['login']))
     {
     	$login=$_SESSION['login'];
	$uid=$_SESSION['uid'];
     }
     if(isset($login))
     {
     	header("Location: /");
     	die();
     }
	include "inc/str_nick.php";
	include "inc/check_nick.php";
	include "inc/check_login.php";
			$login="";
			$pass="";
			$nick="";
	$done=false;
		if(isset($arg_DATA1))
		{
			$login=$arg_login;
			$pass=$arg_pass;
			$nick=$arg_nick;

			if(!isset($error) && !check_login($login))
			{
				$error="email задан неверно, можно только латинские буквы и символы '.-_@'";
			}
			if(!isset($error) && !check_nick($nick))
			{
				$error="Nick задан неверно, можно только русские и латинские буквы '.-_@'";
			}
			
			$rs=mysql_select1("select id from tbl_users where login='$login'");
			if(isset($rs))
			{
				$error="Такой email уже зарегистрирован";
			}
			$strnick=str_nick($nick);
			$_rn=mysql_select1("select uid from nicks where str_nick='$strnick'");
			if(isset($_rn))
			{
			
				$error="Такой nick уже зарегистрирован  ".$_rn[0];
			}
			
			if(!isset($error) && $arg_pass!=$arg_pass2)
			{
				$error="Пароли не совпадают";
			}
			$key='';
			if(isset($_SESSION['key'])) $key=$_SESSION['key'];
			$ekey='-fgjusdlfgkj3941';
			if(isset($arg_key)) $ekey=$arg_key;
			if($key!=$ekey)
			{
				$error="Код на картинке введен неверно";
			}
			
			if(!isset($error))
			{
				$thumb_big="";
				$thumb_small="";

				if($arg_gender==1)
				{
					$thumb_big="/pics/noimage-male-big.jpg";
					$thumb_small="/pics/noimage-male-small.jpg";
				}
				else if($arg_gender==2)
				{
					$thumb_big="/pics/noimage-female-big.jpg";
					$thumb_small="/pics/noimage-female-small.jpg";
				}
				mysql_query("insert into tbl_users (login,pass,level,gender,foto_big,foto_thumb_small,reg_date) values ('$login',md5('pass'),'200','$arg_gender','$thumb_big','$thumb_small',NOW())") or die(mysql_error());
				$uid=mysql_select1("select LAST_INSERT_ID()");
				//echo "uid $iuid<br>";
				mysql_query("insert into nicks (nick,str_nick,uid,banned,bby,last_usage_date,ready_to_sale) values ('$nick','$strnick','$uid','0','0',NOW(),'0')") or  die(mysql_error());;


				$_SESSION['uid']=$uid;
				$_SESSION['login']=$login;
				$_SESSION['level']=200;
				$_SESSION['cnick']=$nick;
				header("Location: /registration/2.php?r=".rand());
//				echo '<script>window.top.location="/registration/2.php"</script>';
				$done=true;
				die();
			}
		}
	?>

<html>
<head>
  <meta http-equiv="PRAGMA" content="no-cache">
  <meta http-equiv="Content-Type" content="text/html; charset=windows-1251">

  <title>Чат "Тусовка"</title>
  <link rel="stylesheet" type="text/css" href="/css/main.css">
  <script language="javascript" src="/css/mmove.js" type="text/javascript"></script>
	<script>
	function checkform()
	{
	if(document.form1.pass.value=="")
	{
		alert("Вы забыли ввести Ваш пароль...");
		document.form1.pass.focus();
		return false;
	}
	if(document.form1.pass.value.length<3)
	{
		alert("Пароль должен быть не короче 3 символов...");
		document.form1.pass.focus();
		return false;
	}
	if(document.form1.pass2.value!=document.form1.pass.value)
	{
		alert("Ваш пароль не совпадает с подтверждением...");
		document.form1.pass.focus();
		return false;
	}
	if(document.form1.nick.value=="")
	{
		alert("Вы забыли ввести свой ник...");
		document.form1.nick.focus();
		return false;
	}
	if(document.form1.login.value=="")
	{
		alert("Вы забыли ввести свой логин...");
		document.form1.login.focus();
		return false;
	}

	document.form1.reg.disabled=true;
		return true;
	}
	</script>

</head>


<?
if(!$done)
{
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
	
	<div align=center class=border style='margin-bottom: 20px'><b>Регистрация</b></div>
	<?
		if(isset($error))
		{
			?>
			<div align=center class=yelmsg style='margin-bottom: 20px'><b> <?=$error?></b></div>
			<?
		}
	?>
	<form method="post"  name="form1" onsubmit="return checkform();">

               <fieldset>
                        <legend class="leg"><big><b>Страница 1 из 2</b></big></legend> 
			<script type="text/javascript">
//				document.form1.login.focus();
                        </script>
			<?
				$gender=1;
				if(isset($arg_gender)) $gender=$arg_gender;
			?>	


                        <table border="0" cellspacing="0" cellpadding="5" width="100%">
                          <tr valign="top">
                            <td align="right" width="125">Вы:</td>
                            <td><select name='gender' style="width: 120px">
			    <option value=1 <?if($gender==1)echo "SELECTED";?> >Парень
			    <option value=1 <?if($gender==2)echo "SELECTED";?> >Девушка
			    </select></td>
                            <td>
                          </tr>
			
                          <tr valign="top">
                            <td align="right" width="125">Email:</td>
                            <td><input type="text" maxlength="50" size="20" name="login" value='<?=$login?>'></td>
                            <td>Ваш E-mail. Это поле используется для того, чтобы войти в систему не используя ник. 
			    	Если у Вас нет своего e-mail, то введите любой текст латинскими буквами, содержащий символ '@'
                          </tr>

                          <tr valign="top">
                            <td align="right">Ник:</td>
                            <td><input type="text"  maxlength="16" size="20" name="nick" value='<?=$nick?>'></td>
			    <!--'<??> '-->
                            <td>Ваше имя в чате. Можно использовать английские и русские буквы, а также символы "_", "=", "-" и цифры. Пробелы в нике не допустимы.</td>
                          </tr>


                          <tr valign="top">
                            <td align="right">Пароль:</td>
                            <td><input type="password" maxlength="16" size="20" name="pass" value=""></td>
                            <td>Пароль для входа в систему.</td>
                          </tr>
                          <tr valign="top">
                            <td align="right">Подтвердите пароль:</td>
                            <td><input type="password" maxlength="16" size="20" name="pass2" value=""></td>
                            <td>Повторите пароль введенный выше, для проверки.</td>
                          </tr>

                          <tr valign="top">
                            <td align="right"><img src="_keycode_image.php"></td>
                            <td><input type="text" maxlength="16" size="20" name="key" value=""></td>
                            <td>Введи цифры с картинки справа</td>
                          </tr>
                        </table>
			
		</fieldset>
		<p>
                      <center>
                        <input type="hidden" name="stage" value="1"> 
                        <input type="hidden" name="DATA1" value="yes"> 
			<input type="submit" value="Зарегистрироваться" name="reg"><br>
                      </center>
	</form>
		


      <?
      //END
      ?>
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
<?
	} // $!done
?>
</html>
