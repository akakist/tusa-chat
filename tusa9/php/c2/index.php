<?
	session_start();
        import_request_variables("gp", "arg_");

	
	include "$BASE_DIR/inc/db_conn.php";
	include "$BASE_DIR/c2/inc/conf.php";
	check_conn();

	if(isset($_SESSION['uid']))
	$uid=intval($_SESSION['uid']);
/*
<link href="/c2/css/reset.css" type="text/css" rel="stylesheet">
<link href="/c2/css/main2.css" type="text/css" rel="stylesheet">
*/

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset='UTF-8'">
<meta http-equiv="Cache-Control" content="no-cache">
<meta http-equiv="Pragma" content="no-cache">
<link rel="icon" href="/favicon.ico" type="image/x-icon">
<link rel="shortcut icon" href="/favicon.ico" type="image/x-icon">
<link href="/c2/css/reset.css" type="text/css" rel="stylesheet">
<link href="/c2/css/main2.css" type="text/css" rel="stylesheet">
<title>Чат "Тусовка"</title>
<script src="/c2/js/jquery.min.js" type="text/javascript"></script>
<script src="/c2/js/main.js" type="text/javascript"></script>
<script type="text/javascript" src="/js/md5.js"></script>

</head>
<script>
$(document).ready(function(){
	$('#login').focus();
});
	
</script>
<body onload='$("#online").load("/c2/online.php");'>

<div id="wrapper">
<div id="head">
<a href="#"><img src="/img/logo.gif" alt=""></a>
<!--banner-->
<script type='text/javascript'><!--//<![CDATA[
   var m3_u = (location.protocol=='https:'?'https://germes.tomtel.ru/www/delivery/ajs.php':'http://germes.tomtel.ru/www/delivery/ajs.php');
      var m3_r = Math.floor(Math.random()*99999999999);
         if (!document.MAX_used) document.MAX_used = ',';
            document.write ("<scr"+"ipt type='text/javascript' src='"+m3_u);
               document.write ("?zoneid=35");
                  document.write ('&amp;cb=' + m3_r);
                     if (document.MAX_used != ',') document.write ("&amp;exclude=" + document.MAX_used);
                        document.write (document.charset ? '&amp;charset='+document.charset : (document.characterSet ? '&amp;charset='+document.characterSet : ''));
                           document.write ("&amp;loc=" + escape(window.location));
                              if (document.referrer) document.write ("&amp;referer=" + escape(document.referrer));
                                 if (document.context) document.write ("&context=" + escape(document.context));
                                    if (document.mmm_fo) document.write ("&amp;mmm_fo=1");
                                       document.write ("'><\/scr"+"ipt>");
                                       //]]>--></script><noscript><a href='http://germes.tomtel.ru/www/delivery/ck.php?n=a88e1460&amp;cb=INSERT_RANDOM_NUMBER_HERE' target='_blank'><img src='http://germes.tomtel.ru/www/delivery/avw.php?zoneid=35&amp;cb=INSERT_RANDOM_NUMBER_HERE&amp;n=a88e1460' border='0' alt='' /></a></noscript>
                                        


<!--object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab##version=9,0,0,0" width="468" height="60" id="bn101" border="0">
<param name="AllowScriptAccess" value="always" /> <param name="movie" value="http://abc.russpartner.com/image?p=992&b=101&r=545" /> <param name="FlashVars" value="link=http://www.russiancasino.ru/p/992/b/101/r/545.html"/><param name="menu" value="false" /><param name="quality" value="high" /><param name="scale" value="exactfit" />
<embed src="http://abc.russpartner.com/image?p=992&b=101&r=545" menu="false" quality="high" width="468" height="60" name="bn101" FlashVars="link=http://www.russiancasino.ru/p/992/b/101/r/545.html" type="application/x-shockwave-flash" pluginspace="http://www.macromedia.com/go/getflashplayer" AllowScriptAccess="always"></embed></object>
-->
<!--~banner-->
</div>

<div id="content">

	<div id="left">
	<?

	include "menu.php";
	?>
	</div>
	
	<div id="center">
		<div class="first-line">Добро пожаловать в наш чат! :)</div>
		<div class="text">

		Вы хотели непринужденного общения, и поэтому заглянули к нам? Мы с радостью приветствуем Вас в нашем чате :) Пройдите несложную <a href="/c2/registration.php">регистрацию</a>, и чувствуйте себя как дома. Если Вы впервые у нас, рекомендуем заглянуть в раздел <a href="/c2/help/">помощь</a>, там мы постарались рассмотреть основные моменты. Также все вопросы, пожелания и жалобы принимаются запиской на ник Support. Приятного общения :)
		<p>
		Для того, чтобы чаттиться в вебе рекомендуем использовать браузер <b>CHROME</b>.
		Скачать его можно с <a href=http://google.com/chrome> http://google.com/chrome</a>. <p>
		Для уменьшения времени отклика браузера рекомендуется добавить в исключения антивируса строку http:/tusovka.tomsk.ru/*
		<br><b>ВНИМАНИЕ</b> ЧАТ НЕ РАБОТАЕТ В БРАУЗЕРЕ ОПЕРА, просьба отнестись к данному факту с пониманием, поскольку чат не является простой страницей.
		</div>
		<form method=post name='start'>
	            <input type=hidden name="scr" value="">
		<div class="second-line">Авторизация</div>
		<center>
		<div class="auth" id="auth">

			<div class="login-text">
				Логин: 
				<div style="padding-bottom: 7px;"></div>
				Пароль:
			</div>
			<div class="login-input">
				<input type="text" name="login" style="width: 130px;" value=''>
				<div style="padding: 2px 0;"></div>
				<input type="password" name="pass" style="width: 130px;">
			</div>
			<div class="login-button">
				<input type="submit" value="Войти" style="width: 50px;" onclick=' 
//				document.start.pass.value=md5(document.start.pass.value);
					$.post("index_auth.php",{ 
						login: escape(document.start.login.value),
						pass: escape(document.start.pass.value), 
						r: Math.random(),
						scr: screen.width+"x"+screen.height+"x"+screen.colorDepth},function(data){$("#auth").html(data); });
						
						return false;
						'>

			</div>
		
		</div>
		</center>
		</form>
	
		<div class="second-line">Новости</div>
		<div id="news">
		<?
		$res=mysql_query("select id,DATE_FORMAT(add_date,'%d.%m.%Y'),txt,add_by from news order by add_date desc limit 5") or die(mysql_error().__FILE__.__LINE__);
		while(list($id,$add_date,$txt,$add_by)=mysql_fetch_row($res))
		{
			$txt=preg_replace("[\r\n]","<br>",$txt);
		?>
			<div style="clear: both;">
				<span class="date"><?=$add_date?></span>
				<span class="new"><?=$txt?></span>
				<div class="author">@<a class="nick" href="#"><?=$add_by?></a></div>
			</div>

		<?
		}
		?>
		</div>
		<div style="float: right; clear: both;"><a href="">Более старые новости</a></div>

	</div>

</div>

<div id="right">
<ul id="online">
</ul>

</div>


<div id="left">

  <!--embed  width="310" height="70" src="snegbox1.swf" flashvars="l" allowscriptaccess="always"
      wmode="transparent" quality="high" type="application/x-shockwave-flash"/>

  <embed  width="310" height="70" src="Banner310x70.swf" flashvars="l" allowscriptaccess="always"
      wmode="transparent" quality="high" type="application/x-shockwave-flash"/-->

      
</div>


</div>
<div id="foot">
<!--a href="http://sibterm.tomsk.ru" target=_blank><img src=/img/p.gif border=0></a-->
<?

include "$BASE_DIR/banners/tbe.php";
include "$BASE_DIR/banners/metka_catalog.php";
?>

</div>
</body>
</html>