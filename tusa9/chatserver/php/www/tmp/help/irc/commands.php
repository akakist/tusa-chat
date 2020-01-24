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
<tr><td class=border align=center><b>Часто используемые команды в IRC</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>


<b>/nick &lt;newnickname&gt;</b> - позволяет сменить имя, под которым видят вас остальные участники беседы.<br><br>

<b>/list</b> - выводит список общедоступных каналов, их темы (если указаны) и текущее число их пользователей. Скрытые и приватные каналы не показываются. <br><br>

<b>/join #channelname</b> - создает новый канал или переключает на уже существующий.<br><br>

<b>/part #channelname</b> - выход из данного канала.<br><br>

<b>/quit</b> [причина_выхода] - выход из IRC.<br><br>

<b>/exit</b> - выход из всей программы.<br><br>

<b>/topic #channelname ваш_текст</b> - устанавливает новый топик на канале (право смены топика имеет определенная группа пользователей).<br><br>

<b>/msg &lt;nickname&gt;</b> - отослать данному пользователю приватное сообщение.<br><br>

<b>/me &lt;message&gt;</b> - написать сообщение в действие.<br><br>

<b>/clear</b> [&lt;windowname&gt;] - очистка содержимого окна (если после команды указать название окна, например чей то ник, скем Вы разговариваете в привате, то в этом окне все сообщения будут удалены).<br><br>

<b>/query &lt;nickname&gt;</b> - устанавливает режим приватного разговора между вами и другим пользователем.<br><br>

<b>/whois &lt;nickname&gt;</b> - получение информации о конкретном пользователе.<br><br>

<b>/help</b> - посмотреть инфо к программе.
<br><br><br>
* то, что находится в квадратных скобках [], указывать необязательно.
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
