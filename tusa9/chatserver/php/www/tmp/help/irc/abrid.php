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
<tr><td class=border align=center><b>����������, �������� �� IRC.</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>

<b>re</b> <i>"regards"</i> - ����������� ����������� �� IRC.<br><br>

<b>wb</b> <i>"welcome back"</i> - � ������������.<br><br>

<b>brb</b> <i>"be right back"</i> - ������ �������.<br><br>

<b>bbl</b> <i>"be back later"</i> - ���� �����.<br><br>

<b>c u</b> <i>"see you"</i> - ��������.<br><br>

<b>l8r</b> <i>"later"</i> - �����.<br><br>

<b>IMO</b> <i>"in my opinion"</i> - �� ����� ������.<br><br>

<b>IMHO</b> <i>"in my humble opinion"</i> - �� ����� ��������� ������.<br><br>

<b>IMNSHO</b> <i>"in my not so humble o�inion"</i> - �� ����� ����������� ������. <br><br>

<b>IRL</b> <i>"in real life"</i> - � ��������� �����.<br><br>

<b>AFAIK</b> <i>"as far as I know"</i> - �� ������� � ����.<br><br>

<b>AKA</b> <i>"also known as"</i> - ��� �������� ���.<br><br>

<b>away</b> - (������/��������� � nickname) ��������, ��� ������������ ������ ��� �� ������� �������� ������������� �� ������.<br><br>

<b>btw</b> <i>"by the way"</i> - ����� ������, ������.<br><br>

<b>gn</b> <i>"good night"</i> - ������ ����.<br><br>

<b>ppl</b> <i>"people"</i> - ��������� �� ����, ����������� �� ������.<br><br>

<b>tnx, 10x</b> <i>"thanks"</i> - ��������� �����.<br><br>

<b>U R welcome</b> <i>"you are welcome"</i> - ������ ���������� / ����� ����������<br><br>

<b>plz</b> <i>"please"</i> - ��� ���� ��������� �����.<br><br>

<b>lol</b> <i>"loughing out loud"</i> - ����� �����.<br><br>

<b>lag</b> - �����, ���������� � ������� ����������� ������ ��������� �� �������, ����� ��� ������ ������ ��������� ������.<br><br>

<b>op</b> - ���������� �� ����� ��������. ������ ���������� ����� ������ �� ������ �������� - ������ �������� � �� ���� �������� @. �������� - �������, � ����������� ������� ������ ����������� ������� �� ������. � �����, ������� ���� :)<br><br>

<b>kick</b> - ��������� �������� ������������ � ������, ������������ ����������� ��� ����������� �������.<br><br>

<b>ban</b> - �������� ������������ � ������ �� ���������� ���� (�� ���������� ����� �� ��������������� �������), ������������ ����������� ��� ����������� �������. ����. �������� ����� ��������� ;)<br><br>

<b>bot</b> - (����� ������) ���������, ���������� �� ��������� ����������. ��� ����� ������������� ����������� �� ��������� ��������, ����� � �.�. �� ������ (��������, �� ����������� ��������� ;)) � ��� ������� ������ ������������� �������������, ������������� ������ � �.�.<br><br>

<b>privat</b> - ������� ������ ����� ����� ��������������.<br><br>

<b>FAQ</b> <i>"Frequently Asked Questions"</i> - ������ �� ����� ���������� �������.<br><br>

<b>RTFM</b> <i>"read the fucking manual"</i> - ����� ����� "���������" ������������.<br><br>

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
