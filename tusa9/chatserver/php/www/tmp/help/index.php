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

  <title>��� "�������"</title>
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
            <td class="border" align="center"><b>������</b></td>
          </tr>

          <tr height="5">
            <td></td>
          </tr>

          <tr>
            <td>
              <div align="justify" valign="top">
                ��� ������ ������� �� ���� ��� ��������� �������. �������� �� ������ ������ � �������� �� ����. �� ��������, ��� ����� �� ������ ��� ������ �� ���� �������. ���� ��� ���-�� ���������
                � ����� �� ����� �� �����, �� ������ �� <span lang="en-us">Support</span> .<br>
                <br>
                <a href="/help/rules.php"><b>������� ����������� �����.</b></a>


                <p><a href="/help/mafia.php">������� ���� � <b>�����</b>.</a><br>
                <br>
                <a href="/help/quiz.php">������� ���� � <b>���������</b>.</a><br>
                <br>
                <a href="/help/roulette.php">������� ���� � <b>������</b>.</a><br>
                <br>
                <a href="/help/arena.php">������� ���� � <b>�����</b>.</a></p>

                <p><a href="/help/top.php">��� ������ ������� ��������� � �����.</a></p>

                <p><a href="/help/features.php">����������� ����.</a></p>

                <p><a href="/help/kanal.php">����������� �������.</a></p>

                <p><a href="/help/credits.php">��� ����� <b>�������</b> � ����� ��� �����?</a>�<br>
                <a href="/help/frame.php">������ � �� ���� ������ � ����� �����?</a><br>
                <a href="/help/pass.php">��� ������, ���� � ����� ���� ������?</a><br>
                <a href="/help/chat.php">��� ������������ �����?</a><br>
                <a href="/help/userlist.php">��� ������ ��� � ����?</a><br>
                <a href="/help/notes.php">��� ������������ ���������?</a><br>
                <a href="/help/nick.php">��� ������� ���� ��� ���� ���?</a><br>
                <a href="/help/level.php">��� ����� "�������"?</a><br>
                <a href="/help/levelup.php">��� ������� ���� �������?</a><br>
                <a href="/help/info.php">��� �������� ���������� � ����?</a><br>
                <a href="/help/status.php">��� ����� ������� � ����� �� ��������?</a><br>
                <a href="/help/yell.php">��� ����� "�������" ������������?</a><br>
                <a href="/help/voting.php">��� ����� ����������� � ��� �� ������������?</a><br>
                <a href="/help/space.php">������ ������ ������� ����� �� ������� �����?</a><br>
                <a href="/help/irc">��� ����� � ��� ������������ IRC?</a></p>

                <!--p><a href="/help/smiles.php">��������</a><br></p-->
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

  <p align="left">�</p>
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
