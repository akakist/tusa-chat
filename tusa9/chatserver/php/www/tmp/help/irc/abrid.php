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
<tr><td class=border align=center><b>Сокращения, принятые на IRC.</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>

<b>re</b> <i>"regards"</i> - стандартное приветствие на IRC.<br><br>

<b>wb</b> <i>"welcome back"</i> - с возвращением.<br><br>

<b>brb</b> <i>"be right back"</i> - сейчас вернусь.<br><br>

<b>bbl</b> <i>"be back later"</i> - буду позже.<br><br>

<b>c u</b> <i>"see you"</i> - увидимся.<br><br>

<b>l8r</b> <i>"later"</i> - позже.<br><br>

<b>IMO</b> <i>"in my opinion"</i> - по моему мнению.<br><br>

<b>IMHO</b> <i>"in my humble opinion"</i> - по моему скромному мнению.<br><br>

<b>IMNSHO</b> <i>"in my not so humble oрinion"</i> - по моему нескромному мнению. <br><br>

<b>IRL</b> <i>"in real life"</i> - в настоящей жизни.<br><br>

<b>AFAIK</b> <i>"as far as I know"</i> - на сколько я знаю.<br><br>

<b>AKA</b> <i>"also known as"</i> - еще известен как.<br><br>

<b>away</b> - (статус/приставка к nickname) означает, что пользователь отошел или не уделяет внимание происходящему на канале.<br><br>

<b>btw</b> <i>"by the way"</i> - между прочим, кстати.<br><br>

<b>gn</b> <i>"good night"</i> - доброй ночи.<br><br>

<b>ppl</b> <i>"people"</i> - обращение ко всем, находящимся на канале.<br><br>

<b>tnx, 10x</b> <i>"thanks"</i> - волшебное слово.<br><br>

<b>U R welcome</b> <i>"you are welcome"</i> - всегда пожалуйста / добро пожаловать<br><br>

<b>plz</b> <i>"please"</i> - еще одно волшебное слово.<br><br>

<b>lol</b> <i>"loughing out loud"</i> - взрыв смеха.<br><br>

<b>lag</b> - время, проходящее с момента отправления вашего сообщения до момента, когда его увидят другие участники беседы.<br><br>

<b>op</b> - сокращение от слова оператор. Обычно операторов можно узнать по одному признаку - первым символом в их нике является @. Оператор - человек, в обязанности котрого входит поддержание порядка на канале. В общем, хорошие люди :)<br><br>

<b>kick</b> - временное удаление пользователя с канала, используется операторами для поддержания порядка.<br><br>

<b>ban</b> - удаление пользователя с канала на длительный срок (от нескольких часов до неопределенного времени), используется операторами для поддержания порядка. Прим. Подобное нужно заслужить ;)<br><br>

<b>bot</b> - (робот канала) программа, запущенная на удаленном компьютере. Бот может автоматически реагировать на различные действия, фразы и т.п. на канале (например, на нецензурные выражения ;)) В его функции входит идентификация пользователей, модерирование канала и т.д.<br><br>

<b>privat</b> - частная беседа между двумя пользователями.<br><br>

<b>FAQ</b> <i>"Frequently Asked Questions"</i> - ответы на часто задаваемые вопросы.<br><br>

<b>RTFM</b> <i>"read the fucking manual"</i> - читай лучше "долбанную" документацию.<br><br>

<p><div align=right>&copy; TANKIST</div>
<BR><BR><BR>
<a href="/help/irc"><IMG src="/pics/back.gif" alt="Вернуться назад" border="0"></a>
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
