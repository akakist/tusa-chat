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
            <td class="border" align="center"><b>������� ���� � �������</b></td>
          </tr>

          <tr height="5">
            <td></td>
          </tr>

          <tr>
            <td>
              <div align="justify" valign="top">
                <br>
                ���� ���������� �� ������� <b>!�����</b>, ����� ���� ������ (��� ������� "������") �������� ����� ����.

                <p>���� ���� - ������� ����� ������� �������� � �������� �������� �������.<br></p>

                <p><b>������</b><br></p>

                <p>������ ������ �� �����, � ����� ��� � �����. ������ �� ����� ������� ���� ���������� � 36 ��� ������ ������������ �����. ������� ����� � ���� 0 (����) �� 36.<br>
                ������ �� ��� ���������� � 2 ���� ������ ������������ ����� ���� �������� ����� - ������, ���� �� ������ � ������ �� ���.<br>
                ������ �� ����� ���������� � 2 ���� ������ ������������ ����� ���� �������� ����� ��������, ���� �� ������ � ������ �� �����.<br>
                ������ �� �������� ���������� � 2 ���� ������ ������������ ����� ���� �������� ����� �� 1 �� 18 ���� �� 19 �� 36.<br>
                ������ �� ������ ���������� � 3 ���� ������ ������������ ����� ���� �������� ����� �� 1-12, 13-24, 25-36.<br></p>

                <p><b>������ ������:</b></p>

                <ul>
                  <li>!10-20,33,1,2,3 10 - ��������� �� �������� ����� �� 10 �� 20 � �� 1,2,3 � ����� 10 ��������. �� ������ ����� ���������� ����� ������ ��������� ����� ������ �� �����������
                  �����.<br></li>

                  <li>!��� 1, !even 2 - ��������� �� ������.<br></li>

                  <li>!����� 1, !odd 2 - ��������� �� ��������.<br></li>

                  <li>!�1 !p1 !�2 !p2 - ��������� �� ������ ��� ������ ��������.<br></li>

                  <li>!�1 !�2 !�3 !d1 !d2 !d3 - ������ �� ������.<br></li>

                  <li>!������ !stakes - ���������� ���������� ������.<br></li>
                </ul><br>
                <br>
                <br>
                <a href="/help"><img src="/pics/back.gif" alt="��������� �����" border="0"></a>
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
    
</body>
</html>
