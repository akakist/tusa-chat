<?

	session_start();
        import_request_variables("gp", "arg_");

	
	include "$BASE_DIR/inc/db_conn.php";
	include "$BASE_DIR/inc/conf.php";
	include "$BASE_DIR/inc/calc_age.php";
	include "$BASE_DIR/inc/unescape_rus.php";
	check_conn();
     if(isset($_SESSION['uid']))
     {
	$uid=intval($_SESSION['uid']);
	
     }
	if(isset($_SESSION['privs']['photo']))
	{
		$foto_adm=1;
	}
	if( isset($_SESSION['level']) && $_SESSION['level']>799 )	{	$adm=1;		}
	else {	$adm=0;	}
     
     	if(isset($arg_ni))
	{
		$arg_ni=unescape_rus($arg_ni);
		$arg_id=mysql_select1("select uid from nicks where nick='".mysql_escape_string($arg_ni)."'");
	}
	list($info,$foto_count,$stat_last_date,$screen_resolution,$user_agent,$stat_last_ip,$credit_summa,$setting_show_credits,$level,$setting_show_level,$city,$gender,$hide_name,$last_nick,$foto_thumb_big,$name,$hide_bdate,$birth_date_year,$birth_date_day)=
	mysql_select1row("select info, foto_count, stat_last_date, screen_resolution, user_agent, stat_last_ip, credit_summa, setting_show_credits, level, setting_show_level, city, gender, hide_name, last_nick, foto_thumb_big, name, hide_bdate, year(birth_date),dayofyear(birth_date) from tbl_users where id=".intval($arg_id)."");
	      
	$aid=intval($arg_id);
?>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Инфа <?=$last_nick?></title>


	<script type="text/javascript" src="/js/jquery.pack.js"></script>

<script type="text/javascript" src="/highslide/highslide-with-gallery.js"></script>
<link rel="stylesheet" type="text/css" href="/highslide/highslide.css" />

<script type="text/javascript"> 
	hs.graphicsDir = '/highslide/graphics/';
	hs.align = 'center';
	hs.transitions = ['expand', 'crossfade'];
	hs.outlineType = 'glossy-dark';
	hs.wrapperClassName = 'dark';
	hs.fadeInOut = true;
	hs.showCredits=false;
	//hs.dimmingOpacity = 0.75;
 
	// Add the controlbar
	if (hs.addSlideshow) hs.addSlideshow({
		//slideshowGroup: 'group1',
		interval: 5000,
		repeat: false,
		useControls: true,
		fixedControls: 'fit',
		overlayOptions: {
			opacity: .6,
			position: 'bottom center',
			hideOnMouseOut: true
		}
	});
</script>


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

#info {position: absolute; top: 240px;left: 430px; float:right}

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
<!---banner-->
<center>

<table cellpadding=4 cellspacing=4 border=0 align=center width=100%>
<tr><td>

<!--object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab##version=9,0,0,0" width="200" height="200" id="bn83" border="0">
<param name="AllowScriptAccess" value="always" /> <param name="movie" value="http://abc.russpartner.com/image?p=992&b=83" /> <param name="FlashVars" value="link=http://www.russiancasino.ru/p/992/b/83.html"/><param name="menu" value="false" /><param name="quality" value="high" /><param name="scale" value="exactfit" />
<embed src="http://abc.russpartner.com/image?p=992&b=83" menu="false" quality="high" width="200" height="200" name="bn83" FlashVars="link=http://www.russiancasino.ru/p/992/b/83.html" type="application/x-shockwave-flash" pluginspace="http://www.macromedia.com/go/getflashplayer" AllowScriptAccess="always"></embed></object-->

</td><td>

<script type="text/javascript">//<![CDATA[
var tbpd=document.getElementsByTagName("script");tbpd=tbpd[tbpd.length-1];function t_tbpd(){var s=document.createElement("SCRIPT");s.type="text/javascript";s.src="http://tbe.tom.ru/?jg=x&s=46860&a=tusovka.tomsk.ru&id=tbpd&rnd="+(new Date().getTime());document.documentElement.firstChild.appendChild(s);}setTimeout("t_tbpd()",1)
//]]></script><noscript><p style="display:inline"><a href="http://tbe.tom.ru/?gl=x&s=46860&amp;a=tusovka.tomsk.ru"><img src="http://tbe.tom.ru/?gi=x&amp;a=tusovka.tomsk.ru" alt="TBE" style="border:0" /></a></p></noscript>

</td><td>

<!--a href="http://www.russiancasino.ru/p/992/b/23.html"><img src="http://abc.russpartner.com/image?p=992&b=23" width="100" height="100" border="0"></a-->
<!--script language="javascript">
var ui_windows = new Object();var createGameWindow = function(url, windowName, params){var w = ui_windows[windowName];if(w != null && w.closed == false){w.close();}ui_windows[windowName] = window.open(url, windowName, params);}
</script><object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab##version=9,0,0,0" width="180" height="135" id="bn236" border="0">
<param name="AllowScriptAccess" value="always" /> <param name="movie" value="http://abc.russpartner.com/image?p=992&b=236&r=545" /> <param name="FlashVars" value="link=http://demo.russiancasino.com/game/launcher&p=992&b=236&r=545"/><param name="menu" value="false" /><param name="quality" value="high" /><param name="scale" value="exactfit" />
<embed src="http://abc.russpartner.com/image?p=992&b=236&r=545" menu="false" quality="high" width="180" height="135" name="bn236" FlashVars="link=http://demo.russiancasino.com/game/launcher&p=992&b=236&r=545" type="application/x-shockwave-flash" pluginspace="http://www.macromedia.com/go/getflashplayer" AllowScriptAccess="always"></embed></object-->

</td><td>
</table>
</center>
<!---banner-->


<div style='padding-top:20px;margin-left: 400px;text-align: center; float:left; font-weight: bold'><?=$last_nick?>&nbsp;</div>

<div id='main'>
<?
	if(isset($_SESSION['level']) && $_SESSION['level']>=800)
	echo "<div style='margin-left: 5px; float:left'><a href=\"javascript: opwin('/c2/admin/logininfo.php?id=$aid',550,500)\"><img src=\"/pics/quest.gif\" width=24 height=24 border=0 alt='Login info'></a></div>";
	if(isset($_SESSION['level']) && $_SESSION['level']>=600)
	echo "<div style='float: left'>&nbsp;<a href=\"javascript: opwin('/admin.tse/ban_uid.tse?id=$aid',550,500)\">Ban</a></div>";
?>

<p></p>
	<div id='photo'>

				
			    <?
		if($foto_count>0)
		{
			?>
			    <a  href='#' title='Нажмите для просмотра других фоток' onclick="javascript:$('#photo').load('chat_userinfo2_fotki.php?id=<?=$aid?>');"> <!--'<??> '-->
			    	<img  class='ph' src=<?=$foto_thumb_big?>>
			    </a>
			
			<?
		
		}
			    
			    ?>
			    
			    <!--class='mainphoto'-->
			    

	</div>
	

	<div id='info'>

	<table cellpadding=4 cellspacing=4 border=0 align=center width=500>
	<?
		if( $adm>0 ||!$hide_name)
		{
			$add="";
			if($hide_name) $add="(скрыто)";
			echo "<tr><td class=infoleft>В реале</td><td class=inforight>$name $add</td></tr>\n";
		}
		$g="Оно";
		if($gender=='1')$g="Мужской";
		if($gender=='2')$g="Женский";
		
		echo "<tr><td class=infoleft>Пол</td><td class=inforight>$g</td></tr>\n";
		echo "<tr><td class=infoleft>Живет в городе</td><td class=inforight>$city</td></tr>\n";

		if( $adm>0 || !$hide_bdate )
		{
			$add="";
			$age=calc_age($birth_date_year,$birth_date_day);
			echo "<tr><td class=infoleft>Возраст</td><td class=inforight>$age ";
			if($age>3&&$age<21) echo "лет";
			else
			{
				switch(intval($age%10))
				{
					case 1:   echo "год"; break;
					case 2: case 3: case 4: echo "года";break;
					default: echo "лет";break;
				}
			}
			if($hide_bdate) echo "(скрыто)";
			echo "</td></tr>\n";
		}

		if( $adm>0 || $setting_show_level )
		{
			$level_name=mysql_select1("select name from level_names where id='".intval($level)."' and gender='".intval($gender)."'");
			if(!$setting_show_level) $level_name .="(скрыто)";
			echo "<tr><td class=infoleft>Уровень</td><td class=inforight>$level_name</td></tr>\n";
		}
		if( $adm>0 || $setting_show_credits )
		{
			$credit_summa=sprintf("%2.2f",$credit_summa);
			if(!$setting_show_credits) $credit_summa .="(скрыто)";
			echo "<tr><td class=infoleft>Кредиты</td><td class=inforight>$credit_summa</td></tr>\n";
		}
		
		if( $adm>0 )
		{
			echo "<tr><td class=infoleft>User Agent</td><td class=inforight>$user_agent</td></tr>\n";
			
		}
		if( $adm>0 )
		{
			echo "<tr><td class=infoleft>Screen Resolution</td><td class=inforight>$screen_resolution</td></tr>\n";
			
		}
		if(strlen($info))
		{
			echo "<tr><td class=infoleft colspan=2>$info</td></tr>\n";
			
		}
		
		
	?>
	
	<!--tr><td align=center class=infoleft>
	
	<!--a href="http://www.russiancasino.ru/p/992/b/163/r/545.html">Казино</a><br><br-->
	</td><td>
	<!--script language="javascript">
	var ui_windows = new Object();var createGameWindow = function(url, windowName, params){var w = ui_windows[windowName];if(w != null && w.closed == false){w.close();}ui_windows[windowName] = window.open(url, windowName, params);}
	</script><object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab##version=9,0,0,0" width="180" height="135" id="bn225" border="0">
	<param name="AllowScriptAccess" value="always" /> <param name="movie" value="http://abc.russpartner.com/image?p=992&b=225&r=545" /> <param name="FlashVars" value="link=http://demo.russiancasino.com/game/launcher&p=992&b=225&r=545"/><param name="menu" value="false" /><param name="quality" value="high" /><param name="scale" value="exactfit" />
	<embed src="http://abc.russpartner.com/image?p=992&b=225&r=545" menu="false" quality="high" width="180" height="135" name="bn225" FlashVars="link=http://demo.russiancasino.com/game/launcher&p=992&b=225&r=545" type="application/x-shockwave-flash" pluginspace="http://www.macromedia.com/go/getflashplayer" AllowScriptAccess="always"></embed></object-->	

	</td><tr/-->
	
	</table>
	<!---wowa--->
<!--table cellpadding=4 cellspacing=4 border=0 align=center width=100%>
<tr><td>
<a href=http://www.re-flex.su target=_blank><img border=0 src=/c2/re.gif alt='Re-Flex'></a>
</td></table-->
<!---wowa--->

	</div>

</div>


</body>

</html>
