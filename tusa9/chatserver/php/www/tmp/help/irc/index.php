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
<tr><td class=border align=center><b>�� IRC</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>

� ������� ���� ����������� ����������� ��� ��������� IRC. ��� ����� ��������� ����� IRC ������ (�������� mIRC).
<p>
<center><big><b>������� ����������� ���������� ��� �������</b></big>
<p>
<table cellspacing=1 class=border>
<tr>
<td class=trdd>���</td><td class=trdd>������</td><td class=trdd>�������</td>
</tr>
<tr>
<td class=trd>� �������� ������ �������</td><td class=trd>989 Kb</td><td class=trd><a href="/help/irc/mirc.zip">mIRC.zip</td>
</tr>
<tr>
<td class=trd>�� ����������� �������� ������</td><td class=trd>989 Kb</td><td class=trd><a href="/help/irc/mirc_std.zip">mIRC_std.zip</td>
</tr>
</table>
</center>
<p>
������ ���� � ��� ��� ���� IRC ������ � �� �� ������ ��������� ����������� ������, �� ���
���������� � ����� ������� ��� ������ <b>tusovka.tomsk.ru</b> � ���� <b>6669</b>. (� mIRC �������� ���
�������� �������� <i>/server tusovka.tomsk.ru 6669</i>).<p>
�����, ����� ���������� � ��������, ������� ���� ��� � ���� � ����� �� �������� ���������
�� �������, ��� "<b>Authorization requried to use Registered nick</b>" (� �������� - "<b>��������� ����������� ��� ������������� ����� ����</b>").
�� ��������� <i>/pass <������></i> ���������������.

<p>
��� �� �������:<br>
<a href=/help/irc/about_irc.php>��� ����� IRC ?</a><br>
<a href=/help/irc/commands.php>������� � IRC.</a><br>
<a href=/help/irc/abrid.php>��������� ���������� �������� � IRC.</a><br>


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
