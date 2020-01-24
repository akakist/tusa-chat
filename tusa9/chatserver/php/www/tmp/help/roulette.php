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
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td class="border" align="center"><b>Правила игры в Рулетку</b></td>
          </tr>

          <tr height="5">
            <td></td>
          </tr>

          <tr>
            <td>
              <div align="justify" valign="top">
                <br>
                Игра начинается по команде <b>!старт</b>, после чего Крупье (бот комнаты "Казино") начинает вести игру.

                <p>Цель игры - угадать номер который выиграет и получить выиграть кредиты.<br></p>

                <p><b>Ставки</b><br></p>

                <p>Ставки бывают на число, а также чет и нечет. Ставка на число включая зеро выигрывает в 36 раз больше поставленной суммы. Ставить можно с цифр 0 (зеро) до 36.<br>
                Ставка на чет выигрывает в 2 раза больше поставленной суммы если выпавшая цифра - четная, зеро не играет в ставке на чет.<br>
                Ставка на нечет выигрывает в 2 раза больше поставленной суммы если выпавшая цифра нечетная, зеро не играет в ставке на нечет.<br>
                Ставка на половину выигрывает в 2 раза больше поставленной суммы если выпавшая цифра от 1 до 18 либо от 19 до 36.<br>
                Ставка на дюжину выигрывает в 3 раза больше поставленной суммы если выпавшая цифра от 1-12, 13-24, 25-36.<br></p>

                <p><b>Формат команд:</b></p>

                <ul>
                  <li>!10-20,33,1,2,3 10 - поставить на диапазон чисел от 10 до 20 и на 1,2,3 в сумме 10 кредитов. На каждое число поставится сумма равная указанной сумме делить на количествео
                  чисел.<br></li>

                  <li>!чет 1, !even 2 - поставить на четное.<br></li>

                  <li>!нечет 1, !odd 2 - поставить на нечетное.<br></li>

                  <li>!п1 !p1 !п2 !p2 - поставить на первую или вторую половину.<br></li>

                  <li>!д1 !д2 !д3 !d1 !d2 !d3 - ставки на дюжину.<br></li>

                  <li>!ставки !stakes - посмотреть заказанные ставки.<br></li>
                </ul><br>
                <br>
                <br>
                <a href="/help"><img src="/pics/back.gif" alt="Вернуться назад" border="0"></a>
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
    
</body>
</html>
