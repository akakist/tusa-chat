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
<tr><td class=border align=center><b>�������</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>

��� ����� �������? - ��� ������ ���� - ����������� ������,
�� ������� ����� ��������� �������� �������/�������/������ � ����.
<p>

��� ���� ��� �����? - �������� ������ ������ ������ - �������������� ����� � �������� � ������,
������, �����������, ��������, �������� �����. ��� �� ������ � ����� �������� - ��� �������� SMS ���������. <a href="/settings/credits.php">���������</a>.<br>
�� �������� ���������� �������� ����� �����, ����� ���������� ����������� ��������, � �.�.<br>
��� �� ������� �������� ��������� ��� ������ �������� ������������� �������� ����. �������� ��������, ���������� �� �� �������,
 ���� �� ����������� ������������� �������� ���� � ������� �����, ������ ���������� ����� ��������� � ����.
<p>

��� ����� �������? - �� ������ ������ ���� 3 ������� ��������� ��������:
<ul>
<li>���������� � ����� (��������� � �����)
<li>��������� �� ������� ��������
<li>������ �� ������ � �������������� �������������. 
</ul>

��� ������ �������, ��������� �� ��������� ��������?
<ul>
<li><b>SMS</b> - ��� ������������ �������� ��������� �� ������� �������. ��� �������� ��������� ������� �������������� � � ����������� ����.
<li><b>����������</b> ����� ������ �� ����������� ������.
</ul>

������� �������� ���� � �����?
<ul>
<li><b>���������</b> - �� ���������� ����� �� ������ ������ 0,01 �������
<li><b>�����</b> - ������� ������ �� ��������� ���� � ����� ����, �� ������� 0,05 ������� �� 100 �����
</ul>

��� �� ������� ����� �������� ������, ���������, �������� � ������ � ���� ��� ��� ���������� :)

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
