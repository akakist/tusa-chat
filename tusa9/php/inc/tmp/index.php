<?
    	session_start();
?>
<html>
<head>
  <meta http-equiv="PRAGMA" content="no-cache">
  <meta http-equiv="Content-Type" content="text/html; charset=windows-1251">

  <title>Чат "Тусовка" - Регистрация</title>
  <link href="/css/main.css" rel="stylesheet" type="text/css">
  <!--script language="javascript" src="index.js"> </script--> 

  <script language="javascript" src="/css/mmove.js" type="text/javascript">
</script>
</head>
<?
    include 'head.php';
?>

<body>
  <table border="0" width="100%" cellspacing="0" cellpadding="0">
    <tr>
      <td width="120"><a href="/"><img border="0" src="/pics/logo.gif"></a></td>

      <td class="top_line" width="5"> </td>

      <td class="top_line" width="100%" align="center">
        <?
	include 'inc/banner_top.php';
	?>
	</td>

      <td class="top_line" width="5"> </td>
    </tr>

    <tr height="5">
      <td colspan="5"></td>
    </tr>

    <tr valign="top">
      <td>

        <table class="borderm" border="0" width="120" valign="top" cellspacing="0" cellpadding="0">
          <tr height="16">
            <td class="blr" align="center"><b>Навигация:</b></td>
    <?
	include "inc/menu.php";
	/*
        if(isset($login))
        {
          include "inc/menu_logged.php";
        }
	*/
    ?>
          </tr>
        </table>
      </td>

      <td>
	<?
	    include 'body.php';
	?>
    </td>

      <td>
        <?
            include 'inc/user_list.php';
        ?>

      </td>
    </tr>
  </table>
  <hr>

  <table cellspacing="0" cellpadding="0" border="0" width="100%">
<tr align=center>
    <td>
    <? 
    include 'inc/bb1.php';
    ?>
    </td>
    <td>
    <?
    include 'inc/bb2.php';
    ?>
    </td>
    <td>
    <?
    include 'inc/bb3.php';
    ?>
    </td>
    <td>
    <?
    include 'inc/bb4.php';
    ?>
    </td>
    </tr>
  </table>
</body>
</html>
