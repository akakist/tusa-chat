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
<tr><td class=border align=center><b>Зачем нужна кнопка позвать</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>

Эта кнопка находится рядом с Ником любого присутствующего (первая слева по счёту). Использовать её нужно для того, чтобы
привлечь внимание какого-то человека. Если Вы нажмёте на эту кнопку, у Вас появится окошко в котором Вам нужно будет
ввести краткое сообщение, которое человек увидит при вызове. Нажав на кнопку "<b>ОК</b>", у Вас с экрана это окошко исчезнет,
а у того человека появится! Причём оно у него появится на экране независимо от того в каком он окне сейчас! Поэтому, эту
функцию особенно полезно использовать, если человек свернул окно чата и забыл про него. Кроме того, когда ему прийдёт
это сообщение о вызове, там будет кнопка "<b>ответить</b>" и он сможет не возвращаясь в чат ответить Вам кратким сообщением.
Для Вас этот ответ прийдёт аналогичным вызовом.<br><br>
Если Вам не нравится, когда Вас "дёргают" этой функцией, Вы можете отключить её в настройках чата. Тогда все вызовы будут приходить
Вам ввиде обычного приватного сообщения, а тот, кто отправил Вам это сообщение получит уведомление о том, что у Вас отключена данная функция.
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
