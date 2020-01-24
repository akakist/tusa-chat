<?

	session_start();
        import_request_variables("gp", "arg_");

	
	include "inc/db_conn.php";
	include "inc/conf.php";
	include "inc/calc_age.php";
	include "inc/unescape_rus.php";
	check_conn();
     if(isset($_SESSION['login']))
     {
     	$login=$_SESSION['login'];
	$uid=$_SESSION['uid'];
	
     }
     	if(!isset($login))
	{
//		header("Location: /"); exit();
	}
	if(isset($_SESSION['privs']['user_info']))
	{
		$adm=1;
	}
     
     	if(isset($arg_ni))
	{
		//echo $arg_ni;
		$arg_ni=unescape_rus($arg_ni);
		$arg_id=mysql_select1("select uid from nicks where nick='$arg_ni'");
	}
	$arg_id=intval($arg_id);
	list($info,$foto_count,$stat_last_date,$screen_resolution,$user_agent,$stat_last_ip,$credit_summa,$setting_show_credits,$level,$setting_show_level,$city,$gender,$hide_fname,$last_nick,$foto_big,$foto_thumb_big, $fname,$lname,$hide_bdate,$birth_date_year,$birth_date_day)=
	mysql_select1row("select info,foto_count,stat_last_date,screen_resolution,user_agent,stat_last_ip,credit_summa,setting_show_credits,level,setting_show_level,city,gender,hide_fname,last_nick,foto_big,foto_thumb_big,name,hide_bdate,year(birth_date),dayofyear(birth_date) from tbl_users where id=$arg_id");
?>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=windows-1251">
<title>Инфа <?=$last_nick?></title>

    <link rel="stylesheet" href="/css/fancy.css" type="text/css">
<!--[if lte IE 6]><style type="text/css" media="screen">/* <![CDATA[ */ @import url(/css/fancy.ie.css); /* ]]> */</style><![endif]-->

	<script type="text/javascript" src="/js/jquery.pack.js"></script>
   <script language="javascript" src="/js/fancybox.js"></script>

<style>

body,td,  p, pre,div {
	font-family: Verdana, Arial; font-size: 10pt; color: #dcdcdc; background-color: #003570;
}

.ph { border: 2px darkgray solid;}
#photo {top-margin:40px;position: relative; top: 40px; 
	clear:both; z-order: 1
	left:10px;}

a:link, a:visited {color: #eecc30; text-decoration: none;}
a:hover {text-decoration: underline;}

#info {position: absolute; top: 100px;left: 430px; float:right}

.infoleft{
background: #003060;
font-size: 12px;
color: #dcdcdc;
font-family: Tahoma;
border: 1px black solid;
padding: 5px;
}
.inforight{
background: #003570;
font-size: 12px;
color: #80A0F0;
font-family: Tahoma;
border: 1px black solid;
padding: 5px;
font-weight: bold;
}

</style>
<script>
function opwin(l,w,h)
{
	var ow=open(l,'owusr','toolbar=0,status=0,resizable=1,scrollbars=1,width='+w+',height='+h);
	ow.focus();
}

</script>
</head>
<body>

<div style='margin-left: 400px;text-align: center; float:left; font-weight: bold'><?=$last_nick?>&nbsp;</div>
<div id='main'>
<?
	if(isset($_SESSION['level']) && $_SESSION['level']>=900)
	echo "<div style='margin-left: 5px; float:left'><a href=\"javascript: opwin('/admin/logininfo.php?id=$arg_id',550,500)\"><img src=\"/pics/quest.gif\" width=24 height=24 border=0 alt='Login info'></a></div>";
	if(isset($_SESSION['level']) && $_SESSION['level']>=600)
	echo "<div style='float: left'>&nbsp;<a href=\"javascript: opwin('/admin.tse/ban_uid.tse?id=$arg_id',550,500)\">Ban</a></div>";
?>

<p></p>
	<div id='photo'>

				
			    <a  href=<?=$foto_big?> tb=1>
			    <img  class='ph' src=<?=$foto_thumb_big?>></a>
			    <?
		if($foto_count>0)
		{
			echo "<p style='text-align: left; margin-left: 170px'><a href='#' onclick=\"javascript:$('#photo').load('chat_userinfo2_fotki.php?id=$arg_id');\">Другие фотки</a></p>";
//			echo "<tr><td class=infoleft colspan=2><a href='#' onclick=\"javascript:$('#photo').load('chat_userinfo2_fotki.php?id=$arg_id');\">Другие фотки</a></td></tr>\n";
			
		}
			    
			    ?>
			    
			    <!--class='mainphoto'-->
			    

	</div>
	<div id='info'>

	<table cellpadding=4 cellspacing=4 border=0 align=center width=500>
	<?
		if(isset($adm)||!$hide_fname)
		{
			$add="";
			if($hide_fname) $add="(скрыто)";
			echo "<tr><td class=infoleft>В реале</td><td class=inforight>$fname $lname $add</td></tr>\n";
		}
		$g="Оно";
		if($gender=='1')$g="Мужской";
		if($gender=='2')$g="Женский";
		
		echo "<tr><td class=infoleft>Пол</td><td class=inforight>$g</td></tr>\n";
		echo "<tr><td class=infoleft>Живет в городе</td><td class=inforight>$city</td></tr>\n";

		if(isset($adm)||!$hide_bdate)
		{
			$add="";
			if($hide_bdate) $add="(скрыто)";
			$age=calc_age($birth_date_year,$birth_date_day);
//			$level_name=mysql_select1("select name from level_names where id='$level' and gender='$gender'");
			echo "<tr><td class=infoleft>Возраст</td><td class=inforight>$age ";
			switch(intval($age%10))
			{
				case 1:   echo "год"; break;
				case 2: case 3: case 4: echo "года";break;
				default: echo "лет";break;
			}
			echo "</td></tr>\n";
		}

		if(isset($adm)||$setting_show_level)
		{
			$add="";
			if(!$setting_show_level) $add="(скрыто)";
			$level_name=mysql_select1("select name from level_names where id='$level' and gender='$gender'");
			echo "<tr><td class=infoleft>Уровень</td><td class=inforight>$level_name</td></tr>\n";
		}
		if(isset($adm)||$setting_show_credits)
		{
			$add="";
			if(!$setting_show_credits) $add="(скрыто)";
			$credit_summa=sprintf("%2.2f",$credit_summa);
			echo "<tr><td class=infoleft>Кредиты</td><td class=inforight>$credit_summa</td></tr>\n";
		}
		
		if(isset($_SESSION['privs']['show_ip']) || (isset($_SESSION['level']) && $_SESSION['level']>=800))
		{
			echo "<tr><td class=infoleft>User Agent</td><td class=inforight>$user_agent</td></tr>\n";
			
		}
		if(isset($_SESSION['privs']['show_ip']) || (isset($_SESSION['level']) && $_SESSION['level']>=800))
		{
			echo "<tr><td class=infoleft>Screen Resolution</td><td class=inforight>$screen_resolution</td></tr>\n";
			
		}
		if(strlen($info))
		{
			echo "<tr><td class=infoleft colspan=2>$info</td></tr>\n";
			
		}
		
		
	?>
	</table>
	</div>
</div>



</body>
			 <script>
			 	$("a[tb=1]").fancybox();
			 </script>

</html>
