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
<table width=100% border=0 cellspacing=0 cellpadding=0>
<tr><td class=border align=center><b>� �����������...</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>

���������� ����� ������ ���������, �.�. ������ ��, ���� ������ ��������� ���� ����� ����������. ������ ��� ����������
����� �� ������� �� ������. � ����� ������ ����������� �������� ���������.<br>
<P>
� ��� ��� ������� ���� ������� �� ������ �������� <a href=/help/levelup.php>�����</a>.
<p>
� ����� ������� ����������� ���������� ��� �����������, ��� ������� �������, ��������������� ������� (������� �� ����������� ����
�������� - ���� ����� ���� � � ���������), ���� ��������� �� ����������� � ����� ������ ���������� - ������� ��������� �����������.
���� ����������� ��� �� ����������� - �� ������������ ����� ������� ���������������, ����� ������ ������ ������� ����� ������� ���� ���, ��� ������������ "<font class=vyes><b>��</b></font>", � ������� - ��� "<font class=vno><b>������</b></font>". ����������� ����������,
����� ����� ������ �� ����� 95% ���� �������, ������, ��� ����, ����� ������� ��� ����������, ��� ���������� ������� <font class=vyes>70%</font> �������.
����� �������, ���� ������ ��� ������������� ��� ����� <font class=vno>30%</font>, �� ����� ����������� ���������������, �.�. ����������� <font class=vyes>70%</font> �� ��� �� �������.
<P>����������� ������ � �����������:
<table border=0>
<tr><td><img src="/pics/processing.gif"></td><td> - </td><td><div align=justify>������ ����������� ��������� �� ������ �����������...</div></td></tr>
<tr><td><img src="/pics/granted.gif"></td><td> - </td><td><div align=justify>����������� �� ������ ����������� ��������� � ��������������� ������� ����������.</div></td></tr>
<tr><td><img src="/pics/del.gif"></td><td> - </td><td><div align=justify>����������� �� ������ ����������� ��������� � ��������������� ������� <b>��</b> ����������. ������� ������� �������.</div></td></tr>
</table>

<BR><BR><BR>
���� ��� �� ��� ���-�� �� ����, �� �������� ��� <a href="mailto:support@tusovka.tomsk.ru">������</a> � �� ����������� ��� ������.
<BR><BR><BR>
<a href="/help"><IMG src="/pics/back.gif" alt="��������� �����" border="0"></a>

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

  <p align="left">�</p>
  <hr>

    <?
    include 'diz/bottom_table.php';
    ?>
    
</body>
</html>
