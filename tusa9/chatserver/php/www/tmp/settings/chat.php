<?
	session_start();
        import_request_variables("gp", "arg_");

	
	include "c2/inc/db_conn.php";
	include "c2/inc/conf.php";
	check_conn();

	if(isset($_SESSION['uid']))
	$uid=$_SESSION['uid'];
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset='windows-1215'">
<meta http-equiv="Cache-Control" content="no-cache">
<meta http-equiv="Pragma" content="no-cache">
<link rel="icon" href="/favicon.ico" type="image/x-icon">
<link rel="shortcut icon" href="/favicon.ico" type="image/x-icon">
<link href="/c2/css/reset.css" type="text/css" rel="stylesheet">
<link href="/c2/css/main2.css" type="text/css" rel="stylesheet">
<title>��� "�������"</title>
<script src="/c2/js/jquery.min.js" type="text/javascript"></script>
<script src="/c2/js/main.js" type="text/javascript"></script>
<script type="text/javascript" src="/js/md5.js"></script>

</head>
<script>
	
</script>
<body onload='$("#online").load("/c2/online.php");'>

<div id="wrapper">
<div id="head">
<a href="#"><img src="logo.gif" alt=""></a>
</div>

<div id="content">

	<div id="left">
	<?
	include "menu.php";
	?>
	</div>
	
	<div id="center">
	<div class='first-line'>��������� - ���</div>
<table width=100% border=0 cellspacing=0 cellpadding=0>
<tr><td class=border align=center><b>��������� - ���</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>

<FORM method="POST" name="form1">
<input type=hidden name="DATA" value="YES">

<FIELDSET>
<LEGEND class=leg><big><b>�������� ���������</b></big></LEGEND>
<br>
<input type=button value="�������" style="font-size: 10pt" onclick="location='/settings/status.php'">
<input class=bp type=button value="���" style="font-size: 10pt">
<input type=button value="�����" style="font-size: 10pt" onclick="location='/settings/colors.php'">
<input type=button value="�������" style="font-size: 10pt" onclick="location='/settings/credits.php'">
<input type=button value="����������" style="font-size: 10pt" onclick="location='/settings/privs.php'">
<br><br>
</fieldset>
<br>


<?
function checked($c)
{
	if($c>0) return "CHECKED";
	return "";
}
function ison($c)
{
	
	if(isset($c) && $c=='on') return 1;
	return 0;
}
	if(isset($arg_DATA1))
	{
		mysql_query(sprintf("update tbl_users set 
			setting_lpp='%d',
			setting_autochange='%d',
			setting_show_level='%d',
			setting_show_credits='%d',
			setting_show_nicks='%d',
			hide_family_status='%d',
			setting_invite_sound='%d',
			setting_full_buttons='%d',
			contact_mode='%d'
			where id=$uid",
			$arg_setting_lpp,
			isset($arg_setting_autochange),
			isset($arg_setting_show_level),
			isset($arg_setting_show_credits),
			isset($arg_setting_show_nicks),
			isset($arg_hide_family_status),
			isset($arg_setting_invite_sound),
			isset($arg_setting_full_buttons),isset($arg_in_contact)+2*isset($arg_out_contact))) or die(mysql_error());
//			echo mysql_error();
			mysql_query("insert into ext_events (event) values ('cmd=flush obj=tbl_users uid=$uid')") or die(mysql_error().__FILE__.__LINE__);
	}

	$r=mysql_select1row("select setting_lpp,setting_autochange,setting_show_level,setting_show_credits,setting_show_nicks,hide_family_status,setting_invite_sound,setting_full_buttons,contact_mode from tbl_users where id=$uid");
	$setting_lpp=		$r[0];
	$setting_autochange=	$r[1];
	$setting_show_level=	$r[2];
	$setting_show_credits=	$r[3];
	$setting_show_nicks=	$r[4];
	$hide_family_status=	$r[5];
	$setting_invite_sound=	$r[6];
	$setting_full_buttons=	$r[7];
	$contact_mode=		$r[8];
?>
<FIELDSET>
<LEGEND class=leg><big><b>��������� ����</b></big></LEGEND>
<TABLE width="100%" border=0 cellspacing=0 cellpadding=3>
	<TR valign=middle><TD align="right" width=125>���������:</TD><TD><INPUT TYPE="TEXT" MAXLENGTH=20 SIZE=10 NAME="setting_lpp" VALUE="<?=$setting_lpp?>"><!--"<??> "--></TD><TD>���������� ���������� ��������� ������� ����� �������� ��� ����� � ���. ����� �� 1 �� 100.</TD></TR>
	<TR valign=middle><TD align="right" colspan=2>���� ����� ������� <INPUT TYPE=checkbox name="setting_autochange" <?=checked($setting_autochange)?> class=c_b></TD><TD>���� ����� ��������, �� ����� �� �� ����������� ��� � ������� 5 �����, �� ��� ������ ������������� ����� ������ �� <img src="/pics/s/sp3.gif" alt="������">.</TD></TR>
	<TR valign=middle><TD align="right" colspan=2>���������� �������<INPUT TYPE=checkbox name="setting_show_level" <?=checked($setting_show_level)?> class=c_b></TD><TD>���� ������� �� ����� �� ��� ������� � ���� ������ �� ����� ������������, ������ ����������� ������ ������� � ��� ���������.</TD></TR>
	<TR valign=middle><TD align="right" colspan=2>���������� �������<INPUT TYPE=checkbox name="setting_show_credits" <?=checked($setting_show_credits)?> class=c_b></TD><TD>���� ������� ����� �� ��� ���� �������� ����� ��������� � ����� ����.</TD></TR>
	<TR valign=middle><TD align="right" colspan=2>���������� ��� ����<INPUT TYPE=checkbox name="setting_show_nicks" <?=checked($setting_show_nicks)?> class=c_b></TD><TD>� ��� � ���� ����� ��������� ��� ���� ����.</TD></TR>
	<TR valign=middle><TD align="right" colspan=2>�������� �������� ���������<INPUT TYPE=checkbox name="hide_family_status" <?=checked($hide_family_status)?>  class=c_b></TD><TD>&nbsp;</TD></TR>
	<TR valign=middle><TD align="right" colspan=2>���� ��� "�������"<INPUT TYPE=checkbox name="setting_invite_sound" <?=checked($setting_invite_sound)?> class=c_b></TD><TD>���� ����� ������� - �� ����� ��� "�����", ����� ���������� �������� ������.</TD></TR>
	<TR valign=middle><TD align="right" colspan=2>���������� ��� ������<INPUT TYPE=checkbox name="setting_full_buttons" <?=checked($setting_full_buttons)?> class=c_b></TD><TD>��� ������� ������� � ������ ������������� ���� ����� ������������ ��� ������, ����� ��� "�����" � ��� ������� "�������", ��� ����������� ����� ��� ����� �������� �������.</TD></TR>
	<tr><td colspan=3 align=left> ������� ����:</td></tr>
	<TR valign=middle><TD align="right" colspan=2>�� �������� ��������<input type=checkbox name="in_contact" class=c_b <?=checked($contact_mode==3 || $contact_mode==1)?> ></TD><TD>������� ��� �������� ������������� ����������� � ��� �������-����</TD></TR>
	<TR valign=middle><TD align="right" colspan=2>�� ��������� ��������<input type=checkbox name="out_contact" class=c_b <?=checked($contact_mode==2 || $contact_mode==3 )?> ></TD><TD>��� ���� �� ������ �������� ������������� ����������� � ��� �������-����</TD></TR>
</TABLE>
</FIELDSET>
<br>

<!--/table-->
<center>
                        <input type="hidden" name="DATA1" value="yes"> 
<input type=submit value="��������" class=b_l>
</center>

</form>


</div>
</td></tr>
</table>
		

	</div>

</div>

<div id="right">
<ul id="online">
</ul>

</div>

</div>

<div id="foot">

</div>
</body>
</html>