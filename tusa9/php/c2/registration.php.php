	<div class='first-line'>Регистрация</div>
	<?

$ip=$_SERVER["REMOTE_ADDR"];
list($time_cnt,$time_free,$descr)=mysql_select1row("select time_cnt,time_free,za from banned_ip where ip='".mysql_escape_string($ip)."' and time_free>NOW()");
  echo "IP $ip $time_cnt";
//  $errscr= "<script> document.start.login.focus();</script>";

if(isset($time_cnt))
    {
//  echo "IP $ip $time_cnt";
    echo "Ваш IP адрес забанен за $descr на $time_cnt, дата окончания $time_free";
//    $errscr= "<script> document.start.login.focus();</script>";
    }
    else
       {    

		if(isset($error))
		{
			?>
			<div class=error><?=$error?></div>
			<?
		}
	?>
	<form method="post"  name="form1" onsubmit="return checkform();">

               <fieldset>
                        <legend class="leg"><big><b>Регистрация</b></big></legend> 
			<script type="text/javascript">
//				document.form1.login.focus();
                        </script>
			<?
				$gender=1;
				if(isset($arg_gender)) $gender=$arg_gender;
			?>	

                        <table border="0" cellspacing="0" cellpadding="5" width="100%">
                          <tr valign="top">
                            <td width="125">Вы:</td>
                            <td><select name='gender' style="width: 130px">
			    <option value=1 <?if($gender==1)echo "SELECTED";?> >Парень
			    <option value=1 <?if($gender==2)echo "SELECTED";?> >Девушка
			    </select></td>
                            <td>
			    </td>
                          </tr>
			
                          <tr>
                            <td width="125">Email:</td>
                            <td><input type="text" maxlength="50" size="18" name="login" value='<?=$login?>' onchange='
			    	$("#emailinfo").html("Проверка email...");
			    	$("#emailinfo").load("registration_check.php?email="+escape(this.value));
			    ' ></td>
                            <td class=r><div id='emailinfo'>Ваш E-mail. Это поле используется для того, чтобы войти в систему не используя ник. 
			    	Если у Вас нет своего e-mail, то введите любой текст латинскими буквами, содержащий символ '@'
				</div>
                          </tr>

                          <tr valign="top">
                            <td>Ник:</td>
                            <td><input type="text"  maxlength="16" size="20" name="nick" value='<?=$nick?>' onchange='
			    	$("#nickinfo").html("Проверка ника...");
			    	$("#nickinfo").load("registration_check.php?nick="+escape(this.value));
				'></td>
			    <!--'<??> '-->
                            <td class=r><div id='nickinfo'>Ваше имя в чате. Можно использовать английские и русские буквы, а также символы "_", "=", "-" и цифры. Пробелы в нике не допустимы.</td>
                          </tr>


                          <tr>
                            <td>Пароль:</td>
                            <td><input type="password" maxlength="16" size="20" name="pass" value=""></td>
                            <td class=r>Пароль для входа в систему.</td>
                          </tr>
                          <tr valign="top">
                            <td>Подтвердите пароль:</td>
                            <td><input type="password" maxlength="16" size="20" name="pass2" value=""></td>
                            <td class=r>Повторите пароль введенный выше, для проверки.</td>
                          </tr>

                          <tr>
                            <td><img  src="/c2/aj/keycode_image.php"></td>
                            <td><input type="text" maxlength="16" size="20" name="key" value=""></td>
                            <td class=r>Введи цифры с картинки</td>
                          </tr>
                        </table>
	
		<p style='height:10'></p>
                      <center>
                        <input type="hidden" name="stage" value="1"> 
                        <input type="hidden" name="DATA1" value="yes"> 
			<input type="submit" value="Зарегистрироваться" name="reg"><br>
                      </center>
		</fieldset>
	</form>
		
<?
    }
?>

