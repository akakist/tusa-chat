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
<tr><td class=border align=center><b>Как узнать кто в чате?</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>

Если Вы внутри чата, то список пользователей отражён в правой части экрана. Но можно узнать кто в чате и не заходя в него.
На главной странице, а также на любых других (кроме раздела записок), в правой части страницы есть небольшое
окошечко. В нём перечислены каналы и количество присутствующих людей на каждом канале. Но если кликнуть мышкой на какой-либо
канал, то развернётся полный перечень его участников.<BR><BR>
Вы это можете проверить прямо на этой странице (справа от этого текста и есть то окошечко). Но учтите, что список гостей
можно увидеть <b>только</b> если Вы используете броузер <b>Microsoft Internet Explorer</b>, иначе Вам будет видно только количество человек в каждой комнате...!!!

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
