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
<tr><td class=border align=center><b>������ ������ ������� ����� �� ������� �����</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>
������ �����, ��� �� �� ������ ������� �������, �����, � ��. � �������������� ����������. ���� ������� ����������� �����������
�� ������ ����� ������. ��� ����������� ������� �� ������ ������ � �������������� ����� �������:<P>
<table border=0 align=center cellspacing=1 cellpadding=2 class=border>
<tr><td class=trdd>�������</td><td class=trdd>�����</td></tr>
<tr><td class=trd>����� ������������</td><td align=center class=trd>0,5 ��</td></tr>
<tr><td class=trd>������������</td><td align=center class=trd>1 ��</td></tr>
<tr><td class=trd>������</td><td align=center class=trd>6 ��</td></tr>
<tr><td class=trd>��������</td><td align=center class=trd>12 ��</td></tr>
<tr><td class=trd>VIP</td><td align=center class=trd>&nbsp;24 <span lang="ru">��</span></td></tr>
<tr><td class=trd>������</td><td align=center class=trd>30 ��</td></tr>
<tr><td class=trd>�����</td><td align=center class=trd>40 ��</td></tr>
<tr><td class=trd>�����</td><td align=center class=trd>50 ��</td></tr>
<tr><td class=trd>�����</td><td align=center class=trd>60 ��</td></tr>
</table>
<P>
���� � ��� ����� ���������� ����� �� �������, �� �� �� ������� �������� ����� �������, �������, ������������ �������� �������� �������
(�������� ��, ��� �������� ������� �����), � ��� �� �� ���������� ����� �/��� ������� �� ������ �����.
<BR><BR><BR>
���� ��� �� ��� ���-�� �� ����, �� �������� ��� <a class="nou2" href="mailto:support@tusovka.tomsk.ru">������</a> � �� ����������� ��� ������.
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
