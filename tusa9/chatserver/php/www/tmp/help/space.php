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
<tr><td class=border align=center><b>Какому уровню сколько места на сервере даётся</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>
Имейте ввиду, что Вы не можете хранить записки, фотки, и пр. в неограниченном количестве. Нами введено определённое ограничение
на размер ваших данных. Это ограничение зависит от Вашего уровня и распределяется таким образом:<P>
<table border=0 align=center cellspacing=1 cellpadding=2 class=border>
<tr><td class=trdd>Уровень</td><td class=trdd>Место</td></tr>
<tr><td class=trd>Новый Пользователь</td><td align=center class=trd>0,5 Мб</td></tr>
<tr><td class=trd>Пользователь</td><td align=center class=trd>1 Мб</td></tr>
<tr><td class=trd>Чаттер</td><td align=center class=trd>6 Мб</td></tr>
<tr><td class=trd>Тусовщик</td><td align=center class=trd>12 Мб</td></tr>
<tr><td class=trd>VIP</td><td align=center class=trd>&nbsp;24 <span lang="ru">Мб</span></td></tr>
<tr><td class=trd>Киллер</td><td align=center class=trd>30 Мб</td></tr>
<tr><td class=trd>Страж</td><td align=center class=trd>40 Мб</td></tr>
<tr><td class=trd>Шпион</td><td align=center class=trd>50 Мб</td></tr>
<tr><td class=trd>Админ</td><td align=center class=trd>60 Мб</td></tr>
</table>
<P>
Если у Вас будет недостаток места на сервере, то Вы не сможете получать новые записки, поэтому, своевременно удаляйте ненужные записки
(особенно те, что содержат большие файлы), а так же не вставляйте много и/или большие по объему фотки.
<BR><BR><BR>
Если Вам всё ещё что-то не ясно, то напишите нам <a class="nou2" href="mailto:support@tusovka.tomsk.ru">письмо</a> и мы постараемся Вам помочь.
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
