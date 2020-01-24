<?
	session_start();	
		
    include 'inc/db_conn.php';
    check_conn();
    global $name;
    if(isset($_SESSION['login']))
    {
    	$uid=$_SESSION['uid'];
	$sql="select fname,lname from tbl_users where id=$uid";
    	$res=mysql_query($sql);
    
	if(!$res){  echo mysql_error();}
    	while ($r=mysql_fetch_row($res)){
		$name="$r[0] $r[1]";
	}	
//	$_SESSION=array();
	
        session_destroy();
    
    }
    else
    {
    	?>
	<script>window.top.location='/';</script>
    	<?
    }

?>
<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset='windows-1251'">
<TITLE>Чат "Тусовка" - Выход</TITLE>
</head>

<LINK href="/css/main.css" rel=stylesheet type=text/css>


<script>
<!--
function go_home()
{
	window.top.location='/';
}
//-->
</script>
<script language="javascript" src="/css/mmove.js"> </script> 

<body OnLoad="setTimeout('go_home();',120000);">
<TABLE border=0 width=100% cellspacing=0 cellpadding=0>
<TR>
<TD width=120><a href="/"><img border=0 src="/pics/logo.gif"></a></TD>
<TD class=top_line width=5>&nbsp;</TD>
<TD class=top_line width=100% align=center>

    <?
	include 'inc/banner_top.php';
    ?>

</TD>
<TD class=top_line width=5>&nbsp;</TD>
<TD class=top_line width=140 align=center>
    <?
	include 'inc/banner_120.php';
    ?>

</TD>
</TR>
<TR height=5><TD colspan=5></TD></TR>
<TR valign=top>
<TD>
<table class=borderm border=0 width=120 valign=top cellspacing=0 cellpadding=0>
<tr height=16><td class=blr align=center><b>Навигация:</b></td></tr>
    <?
        include "inc/menu.php";
    ?>
</table>
</TD>
<TD></TD>
<TD>
<table width=100% border=0 cellspacing=0 cellpadding=0>
<tr><td class=border align=center><b>До свидания, 
    <? echo $name;

    ?>!</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>
Мы надеемся, что Вам у нас понравилось и Вы еще не раз к нам вернётесь, а также
можете позвать своих друзей, чтоб веселее было :)<br>
До скорых встреч в <b>Тусовке</b> :-)
</div>
</td></tr>
</table>

</TD>
<TD></TD>
<TD>
<?
    include 'inc/user_list.php';
?>
</center></TD>
</TR>
</TABLE>

<hr>
<table cellspacing=0 cellpadding=0 border=0 width=100%>
<tr align=center>
    <td>
    <? 
    include 'inc/bb1.php';
    ?>
    </td>
    <td>
    <?
    include 'inc/bb2.php';
    ?>
    </td>
    <td>
    <?
    include 'inc/bb3.php';
    ?>
    </td>
    <td>
    <?
    include 'inc/bb4.php';
    ?>
    </td>
    </tr>
</table>
</body>


</html>
