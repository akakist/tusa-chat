<?
	session_start();
	header("Content-Type: text/html; charset=\"UTF-8\"");
        import_request_variables("gp", "arg_");
	
	include "$BASE_DIR/inc/db_conn.php";
	include "$BASE_DIR/inc/str_nick.php";
	include "$BASE_DIR/inc/unescape_rus.php";
	check_conn();
     if(isset($_SESSION['uid']))
     {
	$uid=intval($_SESSION['uid']);
     }
     
     if(!isset($uid))
     {
     	header("Location: /");die;
     }
     
     list($nick,$login)=mysql_select1row("select last_nick,login from tbl_users where id='".mysql_escape_string($arg_zid)."'");
     if($_SESSION['level']>=600)
     {
     	$chname=mysql_select1("select name from channels where id='".mysql_escape_string($arg_channel)."'");
     	
     }
//     echo "nick".$nick;
?>
	<!--script>
uinfo=0;
locat="";
function UserinfoID(uid)
{
	
	r=Math.round(Math.random(123)*1000);
	locat='/c2/chat_userinfo2.php?id='+uid;
	
	open(locat,'uinfo'+r,'toolbar=0,status=0,resizable=1,scrollbars=1,width=1000,height=800');
	return false;
}
	
	</script-->
	<script>
function __kick()
{
	$("#umenu").html("<div id=kickmenu>За что<br><input type=text id=kickmsg name=kickmsg><br><input type=button onclick='$(\"#umenu\").toggle();return KickUserZa(<?=$arg_zid?>, document.getElementById(\"kickmsg\").value);' value='Кикнуть'></div>");
	return false;
}

function nickban(zuid)
{

	$.get("/nick_ban.tse",{zid:zuid, r:Math.random()}, 
		function(data){
			append_messages(data);
			document.sendform.msgbox.focus();
		} );	
	return false;
}
	
	</script>
	
	<ul>
	<li class=title> <?=$nick?></li>
	<li ><a href="#" onclick='$("#umenu").toggle();return UserinfoID(<?=$arg_zid?>);'>Инфо</a>
	<li><a href='#' onclick='$("#umenu").toggle();return IgnoreUser(<?=$arg_zid?>);'>Игнор</a>
	<?
	if($_SESSION['level']>=600)
	{
	?>
	<li><a href='#' onclick='$("#umenu").toggle();return KickUserZa(<?=$arg_zid?>,"мат");'>Кик/мат</a>
	<li><a href='#' onclick='$("#umenu").toggle();return KickUserZa(<?=$arg_zid?>,"флуд");'>Кик/флуд</a>
	<li><a href='#' onclick='return __kick()'>Кик</a>
	<?
	}
	if($_SESSION['level']>=700)
	{
	?>
	<li><a href='#' onclick='$("#umenu").toggle();return nickban(<?=$arg_zid?>);'>Никбан <?=$nick?></a>
	<li><a href='#' onclick='$("#bldiv").show();'>Логинбан <?=$login?></a>
		<div id=bldiv style='display:none; width:168px'>
			
			<select style='width:168px' id=blt>
				<option value=0>Выберите время
				<option value=300>5 мин
				<option value=1200>20 мин
				<option value=3600>1 час
				<option value=10800>3 часа
				<option value=86400>1 сутки
			</select><br>
			За <input type=text id='blza'><br>
			<input type=button value='Убанить' onclick='
				$.get("/login_ban.tse",{zid:<?=$arg_zid?>,za:$("#blza").val(),time: $("#blt").val(), r:Math.random()}, 
					function(data){
					append_messages(data);
					document.sendform.msgbox.focus();
				} );	
				$("#umenu").toggle();
			'>
		</div>

	<?
	}
	if($_SESSION['level']>=700)
	{
	?>
		<li><a href='#' onclick='$("#bipdiv").show();'>Бан IP</a>
		<div id=bipdiv style='display:none; width:168px'>
			
			<select style='width:168px' id=bipt>
				<option value=0>Выберите время
				<option value=300>5 мин
				<option value=1200>20 мин
				<option value=3600>1 час
				<option value=10800>3 часа
				<option value=86400>1 сутки
			</select><br>
			За <input type=text id='bipza'><br>
			<input type=button value='Убанить' onclick='
				$.get("/ip_ban.tse",{zid:<?=$arg_zid?>,za:$("#bipza").val(),time: $("#bipt").val(), r:Math.random()}, 
					function(data){
					append_messages(data);
					document.sendform.msgbox.focus();
				} );	
				$("#umenu").toggle();
			'>
		</div>
	
	<?	
	}
	if(isset($_SESSION['moder'][$arg_channel]))
	{
	?>
	<li><a href='#' onclick='$("#klapdiv").show();'>Кляп в <b><?=$chname?></b></a>
		<div id=klapdiv style='display:none; width:168px'>
			
			<select style='width:168px' id=klt>
				<option value=0>Выберите время
				<option value=300>5 мин
				<option value=1200>20 мин
				<option value=3600>1 час
				<option value=10800>3 часа
				<option value=86400>1 сутки
			</select><br>
			За <input type=text id='klza'><br>
			<input type=button value='Убанить' onclick='
				$.get("/klap_user.tse",{zid:<?=$arg_zid?>,za:$("#klza").val(),time: $("#klt").val(),channel:<?=$arg_channel?>, r:Math.random()}, 
					function(data){
					append_messages(data);
					document.sendform.msgbox.focus();
				} );	
				$("#umenu").toggle();
			'>
		</div>
	
	<?
	}
	?>
	</ul>
