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
<script>

</script>
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
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td class="border" align="center"><b>Помощь</b></td>
          </tr>

          <tr height="5">
            <td></td>
          </tr>

          <tr>
            <td>
              <div align="justify" valign="top">
                Вся помощь разбита на темы или отдельные вопросы. Выберите из списка нужный и кликните на него. Мы надеемся, что здесь Вы найдёте все ответы на свои вопросы. Если Вам что-то непонятно
                и здесь Вы этого не нашли, то пишите на <span lang="en-us">Support</span> .<br>
                <br>
                <a href="/help/rules.php"><b>Правила пользования чатом.</b></a>


                <p><a href="/help/mafia.php">Правила игры в <b>Мафию</b>.</a><br>
                <br>
                <a href="/help/quiz.php">Правила игры в <b>Викторину</b>.</a><br>
                <br>
                <a href="/help/roulette.php">Правила игры в <b>Казино</b>.</a><br>
                <br>
                <a href="/help/arena.php">Правила игры в <b>Арену</b>.</a></p>

                <p><a href="/help/top.php">Топ лучших игроков Викторины и Мафии.</a></p>

                <p><a href="/help/features.php">Особенности чата.</a></p>

                <p><a href="/help/kanal.php">Особенности каналов.</a></p>

                <p><a href="/help/credits.php">Что такое <b>кредиты</b> и зачем они нужны?</a> <br>
                <a href="/help/frame.php">Почему я не могу писать в общий фрейм?</a><br>
                <a href="/help/pass.php">Что делать, если я забыл свой пароль?</a><br>
                <a href="/help/chat.php">Как пользоваться чатом?</a><br>
                <a href="/help/userlist.php">Как узнать кто в чате?</a><br>
                <a href="/help/notes.php">Как пользоваться записками?</a><br>
                <a href="/help/nick.php">Как сделать себе ещё один Ник?</a><br>
                <a href="/help/level.php">Что такое "уровень"?</a><br>
                <a href="/help/levelup.php">Как поднять свой уровень?</a><br>
                <a href="/help/info.php">Как изменить информацию о себе?</a><br>
                <a href="/help/status.php">Что такое статусы и каких их изменить?</a><br>
                <a href="/help/yell.php">Что такое "Позвать" пользователя?</a><br>
                <a href="/help/voting.php">Что такое голосование и как им пользоваться?</a><br>
                <a href="/help/space.php">Какому уровню сколько места на сервере даётся?</a><br>
                <a href="/help/irc">Что такое и как пользоваться IRC?</a></p>

                <!--p><a href="/help/smiles.php">Смайлики</a><br></p-->
              </div>
            </td>
          </tr>
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
    <?
/*
	include 'inc/http_request.php';
	$res=http_get("/?kallobong");
	echo $res;
	*/
    ?>
    
</body>
</html>
