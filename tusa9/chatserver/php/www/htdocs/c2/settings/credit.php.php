<?
if ( !isset($_SESSION['ip']) || $_SESSION['ip']!=$_SERVER["REMOTE_ADDR"] || !isset($_SESSION['login']) ) //|| $_SESSION['level'])!=1000
    {
    $name = $_SERVER["SCRIPT_FILENAME"];
    $ip = $_SERVER["REMOTE_ADDR"];    $d = date('Y.m.d H:i:s');
    if (!isset($_SESSION['login'])) { $login = "������"; }    else { $login = $_SESSION['login']; }
    if (!isset($_SESSION['ip'])) { $ip1 = "������"; }    else { $ip1 = $_SESSION['ip']; }
    $tmp = "$name � IP $ip ������� ����� � ������ ������ $login (������ IP $ip1)";
    mysql_query("insert into adm_events (login,date_events,type_events,events) values('$login','$d','CRACK','$tmp')") or die(mysql_error());
    session_destroy();  header("Location: /");
    }
?>                                    
<div class='first-line'>��������� - �������</div>

<FIELDSET>

<LEGEND class=leg>�������</LEGEND>
<?
	$credits=mysql_select1("select credit_summa from tbl_users where id='$uid'");
	if(isset($error))
		echo "<div class=error>$error</div>";
?>

<br>
��� ����� �����: <b><?=$uid?></b> <br>
<div style="float: left">��������:&nbsp; </div> <div id="credits" style="float: left"><b><?=sprintf("%2.2f",$credits)?></b></div>&nbsp;<p>

<hr>

<!--script src="/c2/js/main.js" type="text/javascript"></script-->


<!--a name='cassa'><b>���������� ��� ������ SMS </b></a><p>
���������  �����<br>
<b>devtusa <?=$uid?></b><p>
�� ������ 1121, 1131, 1141, 1151, 1161, 1171, 1899, 3649, 4460, 5537. ��� �������� ��������. 
��� ������ ����� ���, ��� ������ ����� ��������� 1�� �������.<br>
������� ��������� ������� ���������� 50 �������� �� 1 �����.
���� ��� ������� �� ������ � ����������. <a href="#" onclick="swap_div_url('sms','_sms.php'); return false;">���� ��� ������ ������� ���</a><br-->

<div id='sms' style="display: none">
</div>

<p>
<a href="#" onclick="swap_div_url('pin','_pincode.php'); return false;"><b>���������� ��� ������ ��������:</b></a><p>
<div id='pin' style="display: none"></div>
<?
/*
<o>
<a href="#" onclick="swap_div_url('mcassa','_mcassa.php');return false;"><b>���������� ��� ������ ����������</b></a><br>
<div id='mcassa' style="display: none">
</div>
<?
*/
//if ($credits < 200000 || $uid==60610 || $uid==203509 || $uid==26 || $uid==449687 )
//  {
?>
<p>
<form method=post name=transfer>
<a href="#" onclick="swap_div_url('trans','__transfer.php'); return false;"><b>�������</b></a><p>
<div id='trans' style="display: none">
</div>
</form>
<?
//  }
?>
<p>

</FIELDSET>
<p>&nbsp;</p>
<input type=button onclick='window.location="/c2/url_login.php"' value="�����" class=b_l>
