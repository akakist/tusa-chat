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
<tr><td class=border align=center><b>����� ������������ ������� � IRC</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>


<b>/nick &lt;newnickname&gt;</b> - ��������� ������� ���, ��� ������� ����� ��� ��������� ��������� ������.<br><br>

<b>/list</b> - ������� ������ ������������� �������, �� ���� (���� �������) � ������� ����� �� �������������. ������� � ��������� ������ �� ������������. <br><br>

<b>/join #channelname</b> - ������� ����� ����� ��� ����������� �� ��� ������������.<br><br>

<b>/part #channelname</b> - ����� �� ������� ������.<br><br>

<b>/quit</b> [�������_������] - ����� �� IRC.<br><br>

<b>/exit</b> - ����� �� ���� ���������.<br><br>

<b>/topic #channelname ���_�����</b> - ������������� ����� ����� �� ������ (����� ����� ������ ����� ������������ ������ �������������).<br><br>

<b>/msg &lt;nickname&gt;</b> - �������� ������� ������������ ��������� ���������.<br><br>

<b>/me &lt;message&gt;</b> - �������� ��������� � ��������.<br><br>

<b>/clear</b> [&lt;windowname&gt;] - ������� ����������� ���� (���� ����� ������� ������� �������� ����, �������� ��� �� ���, ���� �� �������������� � �������, �� � ���� ���� ��� ��������� ����� �������).<br><br>

<b>/query &lt;nickname&gt;</b> - ������������� ����� ���������� ��������� ����� ���� � ������ �������������.<br><br>

<b>/whois &lt;nickname&gt;</b> - ��������� ���������� � ���������� ������������.<br><br>

<b>/help</b> - ���������� ���� � ���������.
<br><br><br>
* ��, ��� ��������� � ���������� ������� [], ��������� �������������.
<p><div align=right>&copy; TANKIST</div>
<BR><BR><BR>
<a href="/help/irc"><IMG src="/pics/back.gif" alt="��������� �����" border="0"></a>
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
