<?
	include "inc/db_conn.php";
	include "inc/db_func.php";
	include "inc/func.php";
	
	if(($uid=check_session())) {
		header("Location: /my");
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

<script language="javascript" src="/js/ajax.js"> </script>
<script language="javascript" src="/js/reg.js"> </script>


<body>


<table cellspacing=0 cellpadding=0 height=105 width=100% style="z-index: -1; position: absolute; top: 0px; left: 0px"><tr><td style="background-color: #efeff7">&nbsp;</td></tr></table>


<center>
<table width=1000 cellspacing=0 cellpadding=0 border=0>
<tr>
<td>

<!--begin page, logo -->
<?
	include "inc/buttons_unlogin.php";
?>
<!-- columns -->

<table cellpadding=0 cellspacing=0 border=0 width=100%>
    <tr valign=top>
	<td width=200 align=left>

	<!-- login form -->
	<table cellspacing=0 cellpadding=0 border=0 width=180>
	<tr><td>
	<form method=post action="/login.php" name=login_form onsubmit="do_login(); return false;">
	<div id=login_info>
		<br><b>������� ����:</b><br>
	</div>
	<br>

	<label for=nick>���:</label><br>
	<input type=text id=nick name=nick class=login><br>
	<label for=passwd>������:</label><br>
	<input type=password id=passwd name=passwd class=login><br>
	<input type=checkbox id=save name=save><label for=save> ���������</label><br><br>
	<input type=submit value="����" name=subm class=enter>
	</form>
	</td></tr>
	</table>
	
	<!-- adv form -->
	

	</td>
	<td width=10>
	    <img src=/images/pix.gif>
	</td>
	<td width=650 valign=top align=left id=index_info>
	    <p class=index_text>
	    �� ������ ��������� � ��������������� �������? ����� ���� �� ������ �� ����� ���� ����� ������?<br>
	    ��, ��, ����� ��� � ����� ������ �������� :-)<br><br>
	    ����, ����� ����������� �� �������:
	    </p>
	    <ul class=index_text>
        	<li>����� ����� ������;
		<li>������ � ����� ������� ����� ������;
		<li>��������� ���������� �� ����� � ������ ��������;
		<li>� � ����� ������, ������ ������� �������� �����.
	    </ul>
	    <p class=index_text2>
	    ����������������? ���������� � <a href=# onclick="show_reg(); return false;">�����������</a>.
	    </p>
	</td>

	<td width=20>
	    <img src=/images/pix.gif>
	</td>

	<td width=150>

	</td>
    </tr>
</table>


<!-- end columns -->

<!-- end of page -->
</td>
</tr>
</table>
