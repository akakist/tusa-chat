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
<tr><td class=border align=center><b>Как изменить информацию о себе</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>
Первое впечатление о Вас человек будет составлять по информации, которую Вы указали при регистрации. Вообще,
отнеситесь серьёзно к составлению инфы о себе. Следите, чтобы она была заполнена (достаточно полно) и своевременно
обновляйте её!<BR><BR>
Поменять свою инфу можно в специальном разделе чата. Для этого, на странице, которая открывается после того,
как Вы введёте свой логин и пароль (но ещё не зайдёте в сам чат) существует пункт "<b>Сменить Инфо</b>".
Если Вы внутри чата, то нажмите на ссылку "<b>Настройки</b>" (которая находится вверху слева) для того,
чтобы открылась страница с настройками, а там уже нажмите на пункт "<b>Сменить Инфо</b>" в меню.<BR><BR>
Там будет анкета, подобная той, что Вы заполняли при регистрации. Только здесь уже заполнены те поля, которые Вы заполняли
при регистрации. Здесь Вы и можете изменить старые данные, либо заполнить пустые поля.<br><br>
Также там можно добавить себе фотографию (до 10 штук) и написать или изменить к ним описания.
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
