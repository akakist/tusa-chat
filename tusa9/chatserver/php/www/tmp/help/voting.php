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
<tr><td class=border align=center><b>О голосовании...</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>

Голосовать могут только избранные, т.е. только те, кому Высшее Админство дало такую привилегию. Причём эта привилегия
никак не зависит от уровня. В любом случае голосование является анонимным.<br>
<P>
О том как поднять себе уровень Вы можете почитать <a href=/help/levelup.php>здесь</a>.
<p>
В самой таблице голосования отмечается ник кандидатуры, его текущий уровень, рассматриваемый уровень (который не обязательно выше
текущего - речь может идти и о понижении), дата вынесения на голосование и самая важная информация - текущий результат голосования.
Если голосование ещё не завершилось - то показывается общий процент проголосовавших, иначе Зелёным цветом отмечен общий процент всех тех, кто проголосовал "<font class=vyes><b>ЗА</b></font>", а красным - кто "<font class=vno><b>против</b></font>". Голосование завершится,
когда будет отдано не менее 95% всех голосов, однако, для того, чтобы уровень был подтверждён, Вам достаточно набрать <font class=vyes>70%</font> голосов.
Таким образом, если против Вас проголосовало уже более <font class=vno>30%</font>, то далее голосование бесперспективно, т.к. необходимых <font class=vyes>70%</font> Вы уже не наберёте.
<P>Расшифровка знаков в голосовании:
<table border=0>
<tr><td><img src="/pics/processing.gif"></td><td> - </td><td><div align=justify>Данная кандидатура находится на стадии голосования...</div></td></tr>
<tr><td><img src="/pics/granted.gif"></td><td> - </td><td><div align=justify>Голосование по данной кандидатуре завершено и рассматриваемый уровень подтверждён.</div></td></tr>
<tr><td><img src="/pics/del.gif"></td><td> - </td><td><div align=justify>Голосование по данной кандидатуре завершено и рассматриваемый уровень <b>НЕ</b> подтверждён. Уровень остался прежним.</div></td></tr>
</table>

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
