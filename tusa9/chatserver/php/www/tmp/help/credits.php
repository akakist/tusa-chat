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
<tr><td class=border align=center><b>Кредиты</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>

Что такое кредиты? - Это своего рода - виртуальные деньги,
на которые можно совершать операции покупки/продажи/обмена в чате.
<p>

Для чего они нужны? - покупать всякие разные штучки - дополнительное место в записках и фотках,
уровни, невидимость, смайлики, цветовые схемы. Так же доступ к таким сервисам - как отправка SMS сообщений. <a href="/settings/credits.php">Подробнее</a>.<br>
Со временем количество сервисов будет расти, будут пополнятся виртуальные магазины, и т.д.<br>
Так же кредиты являются средством при помощи которого финансируется развитие чата. Денежные средства, полученные от их продажи,
 идут на обеспечение качественного хостинга чата и каналов связи, оплату разработки новых наворотов в чате.
<p>

Где взять кредиты? - На данный момент есть 3 способа получения кредитов:
<ul>
<li>Заработать в играх (Викторине и Мафии)
<li>Переводом от другого человека
<li>Купить за деньги у представителей администрации. 
</ul>

Чем хороши сервисы, доступные по средствам кредитов?
<ul>
<li><b>SMS</b> - это качественная отправка сообщения на сотовый телефон. При отправке сообщения доходят гарантированно и в минимальный срок.
<li><b>Мгновенная</b> смена уровня на равноценный Вашему.
</ul>

Сколько кредитов дают в играх?
<ul>
<li><b>Викторина</b> - за правильный ответ на вопрос дается 0,01 кредита
<li><b>Мафия</b> - кредиты даются за набранные очки в конце игры, из расчета 0,05 кредита за 100 очков
</ul>

Так же кредиты можно свободно менять, продавать, покупать и делать с ними все что вздумается :)

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
