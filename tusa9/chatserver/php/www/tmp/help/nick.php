<?
	session_start();
	include "inc/db_conn.php";
     if(isset($_SESSION['login']))
     {
     	$login=$_SESSION['login'];
	$uid=$_SESSION['uid'];
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
<tr><td class=border align=center><b>Как сделать еще один ник</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>

Зарегестрированный пользователь может завести себе несколько Ников на один логин. Сделать это очень просто.
После того, как Вы введёте логин и пароль, Вы попадаете на страницу, где для окончательного входа в чат
Вам предлагается выбрать Ник и комнату, в которую Вы хотите зайти. А рядом с полем Ника есть кнопка "<b>Добавить Ник</b>".
Для того, чтобы зарегистрировать себе ещё один Ник, нужно нажать на неё - появится маленькое окошечко.
Введите туда свой Ник и там же нажмите кнопку "<b>Забить</b>". Всё! Если этот Ник ещё не занят, то в дальнейшем
он будет числиться за Вами. И тогда, при входе в чат, Вы можете выбирать из списка один из своих Ников.<br><br>
Если же Вам надоел какой-либо ник, либо у Вас кончилось свободное место под ники, то удалить один из них Вы можете
нажав на <img src="/pics/del.gif" border=0 width=16 height=16 alt="Удалить ник"> рядом с выбранным в списке ником. Т.е. после нажатия на крестик удалится тот ник, который сейчас выбран в списке.
<BR><BR><BR>
Если Вам всё ещё что-то не ясно, то напишите нам <a href="mailto:support@tusovka.tomsk.ru">письмо</a> и мы постараемся Вам помочь.
<BR><BR><BR>
<a href="/help"><IMG src="/pics/back.gif" alt="Вернуться назад" border="0"></a>

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
