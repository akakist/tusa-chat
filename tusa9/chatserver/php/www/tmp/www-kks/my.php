<?
	include "inc/db_conn.php";
	include "inc/db_func.php";
	include "inc/func.php";
	
	if(!($uid=check_session())) {
		header("Location: /");
		exit();
	}else{
		header("Location: /profile.php?id=$uid");
		exit();
	}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"> 
<html> 
<head> 
    <title>�������</title>
    <META http-equiv=Content-Type content="text/html; charset=windows-1251"> 
    <link rel="stylesheet" href="/styles/main.css" type="text/css">
    <link rel="icon" href="/images/favicon.gif" type="image/gif">
</head>

<script language="javascript" src="/js/ajax.js"></script>
<script language="javascript" src="/js/profile.js"></script>

<body>


<table cellspacing=0 cellpadding=0 height=105 width=100% style="z-index: -1; position: absolute; top: 0px; left: 0px"><tr><td style="background-color: #efeff7">&nbsp;</td></tr></table>


<center>
<table width=1000 cellspacing=0 cellpadding=0 border=0>
<tr>
<td>

<!--begin page, logo -->
<?
	include "inc/buttons_logged.php";
?>
<!-- columns -->

<table cellpadding=0 cellspacing=0 border=0 width=100%>
    <tr>
	<td width=185 valign=top>
	<div id=main_menu class=main_menu>
		<p><a href=#>��� ��������</a></p>
		<p><a href=#>��� ����</a></p>
		<p><a href=#>��� ������</a></p>
		<p><a href=#>��� ����������</a></p>
		<p><a href=#>��� ���������</a></p>
		<p><a href=#>��� ���������</a></p>
	</div>
	</td>
	<td width=10>
	    <img src=/images/pix.gif>
	</td>
	<td width=650 valign=top align=left>
		<div id=profile class=profile>
			<div class=profile_top>&nbsp;��� ������</div>
			<table cellpadding=0 cellspacing=0 style="margin-left: 5px; margin-top: 5px" border=0>
			<tr><td valign=top width=220>
				<img src=/images/ars.jpg border=0>
			</td>
			<td valign=top>
	    		<p class=fio_header>���������� �������</p>
			<br>
			<p><span>���:</span>�������</p>
			<p><span>���� ��������:</span>20 ��� 1982�.</p>
			<p><span>������ �����:</span>�����</p>
			<p><span>�������� ���������:</span>�� �����</p>
			<p><span>������:</span>�������</p>
			</td></tr>
			</table>

			<hr>

			<table cellpadding=0 cellspacing=0 style="margin-left: 5px; margin-top: 5px" border=0>
			<tr><td valign=top width=220>

				<div style="width: 200px; height: 20px; border: 1px solid #dae1e8; margin-top: 10px">
					<div style="width: 30%; height: 20px; background-color: #d8dfea"></div>
					<div class=rate_gauge>
						<a href=#>30</a>
					</div>
							<!-- red ffe0e0, yel fff8a9 grn dfffe3-->
				</div>
				
				<div class=profile_buttons>
					<div><a href=#><img src=/images/she_user_add.png alt="�������� � ������"><br>�������</a></div>
					<div><a href=#><img src=/images/mail.png><br>��������</a></div>
					<div><a href=#><img src=/images/gift.png><br>��������</a></div>
				</div>
				<font color=#808080>
				���...<br><br>
				</font>
				�������<br>
				������ :)
				
			</td>
			<td valign=top>
				<div style="border-bottom: 1px solid #d8dfea; margin-left: 5px; margin-right: 5px; margin-top: 10px; width: 421px; height: 25px;">
					<div class=main_menu_sel id=pb0><a href=# onclick="toggle_profile_tab(0)">�����</a></div>
					<div class=main_menu_unsel id=pb1><a href=# onclick="toggle_profile_tab(1)">����������</a></div>
					<div class=main_menu_unsel id=pb2><a href=# onclick="toggle_profile_tab(2)">����������</a></div>
					<div class=main_menu_unsel id=pb3><a href=# onclick="toggle_profile_tab(3)">������</a></div>
				</div>

				<div class=profile_main_content id=profile_main_content>
					<br>
					������ ����� ������ �� ������ ���� ������� ����� ����� �������� :)
				</div>
			</td></tr>
			</table>
		
		</div>	<!-- end profile -->
	</td>
	<td width=20>
	    <img src=/images/pix.gif>
	</td>
	<td width=150 valign=top>
	    �������
	</td>
    </tr>
</table>


<!-- end columns -->

<!-- end of page -->
</td>
</tr>
</table>
