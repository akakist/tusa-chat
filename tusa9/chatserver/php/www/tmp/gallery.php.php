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
	if(isset($_SESSION['privs']['user_info']))
	{
		$adm=1;
	}
	else $adm=0;

?>
<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1251">
<TITLE>Чат "Тусовка" - Галерея</TITLE>
</head>

<LINK href="/css/main.css" rel=stylesheet type=text/css>
<script language="javascript" src="/css/mmove.js"> </script> 
<script type="text/javascript" src="/js/jquery.pack.js"></script>

<script>
<!--
var uf=0;
var ow=0;
function do_f(id)
{
	var r=Math.random();
	locat='/userphotos/'+id;
	sx=screen.width/3*2;
	sy=screen.height/5*4;
	if(!uf || uf.closed){
		uf=open(locat,'uf','toolbar=0,status=0,resizable=1,scrollbars=1,width='+sx+',height='+sy);
		uf.focus();
	}
	else{
		uf.focus();
		uf.location=locat;
	}	
//	return true;
}
function opwin(l,w,h)
{
	if(!ow || ow.closed){
		ow=open(l,'owusr','toolbar=0,status=0,resizable=1,scrollbars=1,width='+w+',height='+h);
		ow.focus();
	}
	else{
		ow.focus();
		ow.location=locat;
	}	
}

//-->
</script>
<body>
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
        /*if(isset($login))
	{
	    include "inc/menu_logged.php";
	}*/
      ?>

</table>
</TD>
<TD></TD>
<TD>
<table width=100% border=0 cellspacing=0 cellpadding=0>
<tr><td class=border align=center><b>Галерея</b></td></tr>
<tr height=5><td></td></tr>
<tr><td>
<div align=justify valign=top>

<TABLE border=0 width=100%>
<TR><td align=left><form method=POST  action="/gallery.php" name=f>

<tr valign=middle><td><br>Поиск по нику: (введите весь или несколько букв от требуемого ника, ищется максимум 100 ников)</td></tr>
<tr valign=middle><td><input type=textfield name="s" maxlength=16 size=16 value="<?
			if(isset($arg_s)) echo $arg_s;
			else if(isset($arg_n)) echo mysql_select1("select nick from nicks where id=$arg_n");
		?>">  &nbsp;<input type=submit value="Искать"></td></tr> <!--"<??> " -->
</form></TABLE>
<br>
<div>
<?
        include "inc/date.php";
	include "inc/make_user_info.php";
	require_once('inc/str_nick.php');
	$data="";
	$d="";
	if(isset($arg_s))
	{
//#		echo "ARG_S";
//	    $n=str_nick($arg_s);
	    $l=0;
	    if(isset($arg_l))$l=$arg_l;
	    $sql="select id,uid,nick,ready_to_sale from nicks where nick like '$arg_s%' and banned=0 and uid<>0  order by str_nick limit 100";
	    $res=mysql_query($sql);
	    if(!$res){  echo mysql_error();}
	    $nrows=mysql_num_rows($res);
	    echo "Найдено: $nrows";
	    if($nrows>0)
	    {
	            $r=false;
        	    while($row=mysql_fetch_row($res))
	            {
        	            if (!$r){
	                        $d.="<tr>";
        	            }
                	    $id=$row[0];
	                    $nick=$row[2];
                	    $d.="<td width=200 align=center><a href='/gallery.php?n=$id'>$nick</a>";
        	            $d."</td>";
	                    if ($r){
        	                $d."</tr>";
	                    }   	
                	    $r=!$r;
        	    
	            }
	    }

	    
	    
	}
	if(isset($arg_n))
	{

$nout="";
		$d=make_user_info($arg_n,$adm);
		$zid=mysql_select1("select uid from nicks where id=$arg_n");
	}
?>
</div>
<div align=center>
<table border=0>
<?=$d?>

</table>

<?
if(isset($arg_n))
{
	echo "<div id='phot'><a href=\"#\" onclick=\"$('#phot').load('_fotolist.php?id=$zid')\">Фотки</a> </div>\n";
}

?>
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
