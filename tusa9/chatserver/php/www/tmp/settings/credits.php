<?
	session_start();
        import_request_variables("gp", "arg_");
	
	include "inc/db_conn.php";
	include "inc/conf.php";
	check_conn();
     if(isset($_SESSION['login']))
     {
     	$login=$_SESSION['login'];
	$uid=$_SESSION['uid'];
     }
     if(!isset($login))
     {
     	header("Location: /");
     }
function checked($c)
{
	if($c>0) return "CHECKED";
	return "";
}

  ?>
<html>
<head>
  <meta http-equiv="PRAGMA" content="no-cache">
  <meta http-equiv="Content-Type" content="text/html; charset=windows-1251">

  <title>��� "�������"</title>
  <link rel="stylesheet" type="text/css" href="/css/main.css">
  <script language="javascript" src="/css/mmove.js" type="text/javascript"></script>
	<script type="text/javascript" src="/js/jquery.pack.js"></script>
</head>
<script  language="javascript"></script>

<script>
<!--

function swap_div(name)
{
	if(document.getElementById(name).style.display=='none')
	{
		document.getElementById(name).style.display='';
	}
	else
	{
		document.getElementById(name).style.display='none';
	}
	
}

function swap_div_url(name,url)
{
	if(document.getElementById(name).style.display=='none')
	{
		$("#"+name).load(url);
		document.getElementById(name).style.display='';
	}
	else
	{
		document.getElementById(name).style.display='none';
	}
	
}


//-->
</script>


<?

	$credits=mysql_select1("select credit_summa from tbl_users where id=$uid");
?>
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
<tr><td class=border align=center><b>��������� - �������</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>


<FIELDSET>
<LEGEND class=leg><big><b>�������� ���������</b></big></LEGEND>
<br>
<input type=button value="�������" style="font-size: 10pt" onclick="location='/settings/status.php'">
<input type=button value="���" style="font-size: 10pt" onclick="location='/settings/chat.php'">
<input type=button value="�����" style="font-size: 10pt" onclick="location='/settings/colors.php'">
<input class=bp type=button value="�������" style="font-size: 10pt">
<input type=button value="����������" style="font-size: 10pt" onclick="location='/settings/privs.php'">
<br><br>
</fieldset>
<br>


<FIELDSET>
<LEGEND class=leg><big><b>�������</b></big></LEGEND>
<?
	if(isset($error))
		echo "<br><center><font class=yelmsg>$error</font></center>";
?>
<TABLE width="100%" border=0 cellspacing=0 cellpadding=3>
<tr><td colspan=2>

<br>
��� ����� �����: <b><?=$uid?></b> <br>
<div style="float: left">��������:&nbsp; </div> <div id="credits" style="float: left"><b><?=sprintf("%2.2f",$credits)?></b></div>&nbsp;<p>

<hr>



<a name='cassa'><b>���������� ��� ������ SMS </b></a><p>
���������  �����<br>
<b>devtusa <?=$uid?></b><p>
�� ������ 1121, 1131, 1141, 1151, 1161, 1171, 1899, 3649, 4460, 5537. ��� �������� ��������. 
��� ������ ����� ���, ��� ������ ����� ��������� 1�� �������.<br>
������� ��������� ������� ���������� 5 000 000 000 �������� �� 1 �����.
���� ��� ������� �� ������ � ����������. <a href="#" onclick="swap_div_url('sms','_sms.php'); return false;">���� ��� ������ ������� ���</a><br>

<div id='sms' style="display: none">
</div>

<p>
<a href="#" onclick="swap_div_url('pin','_pincode.php'); return false;"><b>���������� ��� ������ ��������:</b></a><p>
<div id='pin' style="display: none">
</div>

<o>
<a href="#" onclick="swap_div_url('mcassa','_mcassa.php');return false;"><b>���������� ��� ������ ����������</b></a><br>
<div id='mcassa' style="display: none">
</div>


<p>
<form method=post name=transfer>
<a href="#" onclick="swap_div_url('trans','_transfer.php'); return false;"><b>�������</b></a><p>
<div id='trans' style="display: none">
</div>
</form>

<!------------>
<p>






</td>
</tr>
</TABLE>

</FIELDSET>

<br>



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
