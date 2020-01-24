<?
	session_start();
        import_request_variables("gp", "arg_");
	include "inc/db_conn.php";
	check_conn();
     if(isset($_SESSION['login']))
     {
     	$login=$_SESSION['login'];
	$uid=$_SESSION['uid'];
	
     }
     if(!isset($login) || !isset($_SESSION["privs"]["news"]))
     {
     	header("Location: /");
	die;
     }
     if(isset($arg_delete))
     {
     	mysql_query("delete from news where id='$arg_delete'");
     }
     if(isset($arg_new))
     {
     	mysql_query("insert into news (add_date,txt,add_by) values (NOW(),'$arg_new','$arg_selectnick')") or die(mysql_error());
     }
?>

<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1251">
<TITLE>Чат "Тусовка" - Консоль админа -> Новости</TITLE>
</head>

<LINK rel="stylesheet" type="text/css" href="/css/main.css">
<script>
<!--

//-->
</script>
<body>

<big><big><center><b>Новости</b></center></big></big><br>
<center>
<form name="f" method="POST">
<input type=hidden name="cmd" value="">
<textarea name=new rows=10 cols=100></textarea>
<p>
Добавлено
	  <SELECT name="selectnick">
	  <?
		$last_nick=mysql_select1("select last_nick from tbl_users where id='$uid'");
		$result=mysql_query("select id,nick from nicks where uid='$uid' order by nick") or die(mysql_error());
    		while (list($id,$nick)=mysql_fetch_row($result)){
			echo "<OPTION VALUE='$nick'";
			if($nick==$last_nick){ echo " SELECTED";}
			echo ">$nick\n";
		}	
	  ?>
	  </SELECT>
	  <p>
<input type=submit value='Добавить'>	


<?
	$res=mysql_query("select id,CHAR_LENGTH(txt), substring(txt, -char_length(txt),40),DATE_FORMAT(add_date,'%d.%m.%Y'),add_by from news order by add_date desc limit 20") or die(mysql_error());
	echo "<table>";
	while(list($id,$len,$txt,$add_date,$add_by)=mysql_fetch_row($res))
	{
//		if(strlen($txt)!=$len)$txt.="...";
		?>
		<tr>
			<td><?=$add_date?></td>
			<td>@<?=$add_by?></td>
			<td><?=$txt?></td>
			
			<td><a href="news.php?delete=<?=$id?>"><img src='/pics/del.gif' border=0></a></td>
		</tr>
		<?
	}
	echo "</table>"
?>
<center>
<input type=button value="Обновить" onclick="document.location.reload();">
<input type=button value="Закрыть" onclick="window.close();">
</center>
</form>
<p>

