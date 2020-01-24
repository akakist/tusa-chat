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
<tr><td class=border align=center><b>Об IRC</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>

К тусовке есть возможность коннектится про протоколу IRC. Для этого требуется любой IRC клиент (например mIRC).
<p>
<center><big><b>Скачать настроенный специально для тусовки</b></big>
<p>
<table cellspacing=1 class=border>
<tr>
<td class=trdd>Тип</td><td class=trdd>Размер</td><td class=trdd>Скачать</td>
</tr>
<tr>
<td class=trd>С цветовой гаммой тусовки</td><td class=trd>989 Kb</td><td class=trd><a href="/help/irc/mirc.zip">mIRC.zip</td>
</tr>
<tr>
<td class=trd>Со стандартной цветовой гаммой</td><td class=trd>989 Kb</td><td class=trd><a href="/help/irc/mirc_std.zip">mIRC_std.zip</td>
</tr>
</table>
</center>
<p>
Однако если у Вас уже есть IRC клиент и Вы не хотите скачивать настроенный клиент, то для
соединения с чатом укажите что сервер <b>tusovka.tomsk.ru</b> а порт <b>6669</b>. (В mIRC например это
делается командой <i>/server tusovka.tomsk.ru 6669</i>).<p>
Далее, после соединения с сервером, укажите свой ник и если в ответ Вы получили сообщение
от системы, что "<b>Authorization requried to use Registered nick</b>" (в переводе - "<b>Требуется авторизация для использования этого ника</b>").
то коммандой <i>/pass <пароль></i> авторизируйтесь.

<p>
Так же читайте:<br>
<a href=/help/irc/about_irc.php>Что такое IRC ?</a><br>
<a href=/help/irc/commands.php>Команды в IRC.</a><br>
<a href=/help/irc/abrid.php>Некоторые сокращения принятые в IRC.</a><br>


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
