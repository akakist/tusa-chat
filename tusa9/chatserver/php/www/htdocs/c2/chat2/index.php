<?
	session_start();
	include "inc/conf.php";
	include "inc/db_conn.php";
	check_conn();
	if(!isset($_SESSION['uid']))
	{
		header("Location: /c2/");die;
	}
	$uid=$_SESSION['uid'];
	$login=$_SESSION['login'];
  
      list($setting_invite_sound,$setting_full_buttons,$level,$last_status_id,$last_channel,$last_nick_id)=mysql_select1row("select setting_invite_sound,setting_full_buttons,level,last_status_id,last_channel,last_nick_id from tbl_users where id='$uid'");
      $cansettopic=$level>499;
      $msglen=mysql_select1("select msg_len from levels where id='$level'");
      $moderated=mysql_select1("select moderated from channels where id='$last_channel'");
      $ip=$_SERVER["REMOTE_ADDR"];
      mysql_query("update tbl_users set stat_last_ip='$ip' where id='$uid'") or die(mysql_error().__FILE__.__LINE__);
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
<!--link href="main2.css" type="text/css" rel="stylesheet"-->
<title>Чат "Тусовка"</title>
<script src="/c2/js/jquery.min.js" type="text/javascript"></script>
<script src="/c2/js/main.js" type="text/javascript"></script>

<script src="index.js" type="text/javascript"></script>
<script src="invite_user.js" type="text/javascript"></script>
<link href="index.css" type="text/css" rel="stylesheet">
</head>
<style>
</style>
<script>


//определяем браузер 
isOpera=isOpera5=window.opera&&isDOM; //Opera 5+ 
isMSIE=document.all&&document.all.item&&!isOpera; //MSIE 4+ 
isMozilla=navigator.appName=="Netscape"; //Mozilla 

//объявляем глобальные переменные и обнуляем их 
var mousex = 0; 
var mousey = 0; 

//находим координаты мышки в Эксплорере и иже с ним 
if (isMSIE || isOpera){ 
	document.onmousemove = function(){ 
	mousex = event.clientX ;
	mousey = event.clientY ;
	return true; 
	} 
} 
//находим координаты мышки в Мозилле 
else if (isMozilla){ 
	document.onmousemove=function(e){ 
	mousex = e.pageX; 
	mousey = e.pageY; 

	return true; 
	} 
} 

//отобразить div в соответствии с координатами 


rooms=new Array();
<?
		$result=mysql_query("select name,id from channels order by id") or die(mysql_error());
		$i=0;
		$c_select="<select name=channel onchange='ch_room();' class=bsel>";
    		while ($row=mysql_fetch_row($result)){
			$n=$row[0];
			echo "rooms[$i]=\"$n\";\r\n";
			$c_select.="<option value=$row[1]";
			if($last_channel==$row[1]) $c_select.=" SELECTED";
			$c_select.=">$n\n";
		    $i++;
		}	
		$c_select.="</select>";
    
?>

var butt_size=65;
var console_size=65;
var userlist_width=200;

var uid=<?=$uid?>;
var full_butt=<?=intval($setting_full_buttons)?>;

var last_date=new Date();
msgs = new Array();
max_m  = 0;
curr_m = 0;
var channel=1;
var moderated=0;
var selected_nick="";
var selected_nick_id=0;
var selected_nick_uid=0;
var userlist_idgen=0;
var invite_sound=<?=$setting_invite_sound?>;

var currentArray=new Array();
var need_resize=false;

function Answer(uid,nid,name,priv)
{
	selected_nick=name;
	selected_nick_id=nid;
	selected_nick_uid=uid;
	if(priv==1)
		document.sendform.privbox.checked=true;
	else
		document.sendform.privbox.checked=false;
	document.sendform.fornick.value=name;
	document.sendform.msgbox.focus();
	return false;
}

var s=0;
var need_scroll=true;

function set_scroll(v)
{
	need_scroll=v;
}

function scroll()
{
}


var timer_update=0;
var debug=1;


var level=0;
function get_level()
{
	return level;
}
function set_level(l)
{
	level=l;
}




function get_channel()
{
	return channel;
}
function set_channel(c)
{
	channel=c;
	if(document.buttonsform.channel.selectedIndex!=c)
		document.buttonsform.channel.selectedIndex=c;
}
function clean_frames()
{
	$("#messages").html("");
	$("#users").html("<div class=prisut>Присутствуют</div>");
	currentArray=Array();
}
function ch_room_on_maty(ch)
{
	clean_frames();
	r=Math.round(Math.random(123)*1000);
	$.get("_change_channel.php",{channel: ch, r:Math.random()}, 
		function(data){
			append_messages(data);
			window.persistent.location.reload();
			document.sendform.msgbox.focus();
		} );
	return false;
}
function reload_chat()
{
	clean_frames();
	window.persistent.location.reload();
	document.sendform.msgbox.focus();
	return true;
}
function set_status(idd,pn,sd)
{
	var s='i'+idd;
	if(document.getElementById(s)){
		document.getElementById(s).src='/pics/s/sp'+pn+'.gif';
		document.getElementById(s).alt=sd;
		document.getElementById(s).title=sd;
	}
}
function rc(l)
{
	r=rooms;
	s=document.buttonsform.channel;
	for(var n=0; n<r.length; n++){
		s.options[n].text=r[n]+' ('+l[n]+')';
	}
}
function DS()
{
	if(need_scroll)
		document.getElementById('messages').scrollTop=document.getElementById('messages').scrollHeight;

}
function set_my_status(n)
{
	if(document.sendform.status.selectedIndex!=n)
		document.sendform.status.selectedIndex=n;
	
}


function ChangeIgnore(ud,st,g)
{
		
	return _ChangeIgnore(ud,st,g);

}


function IgnoreUser(n)
{
	$.post("/ignore_user.tse",{id:n,r:Math.random()});
	return false;
}


function change_nick()
{
	$.post("/change_nick.tse",{id:document.buttonsform.nick.options[document.buttonsform.nick.selectedIndex].value,r:Math.random()});
	document.sendform.msgbox.focus();
}
function change_status()
{
	$.post("/set_user_status.tse",{status:document.sendform.status.options[document.sendform.status.selectedIndex].value,r:Math.random()}
	
	);
	document.sendform.msgbox.focus();
	
}
function exit_chat()
{
	window.top.location='/chat_exit.tse';
	return false;
}

function toggle_moderated()
{
        $.post("/toggle_moderated.tse",{
		version:9,
               	r: Math.random()
                },function(data){append_messages(data); });
}
function on_load()
{
	if(jQuery.browser.msie) alert("Связь с сервером потеряна");
	else
	append_messages("<span style='font-size:20px'>Связь потеряна</span>");
	return false;
}

function res()
{
	resize();
}

function append_messages(txt)
{
	$("#messages").append(txt);
	var el=document.getElementById('messages');

	if(el.scrollHeight>el.clientHeight*3 && need_scroll)
	{
		el.removeChild(el.firstChild);
	}
	if(el.scrollHeight>el.clientHeight*5 && need_scroll)
	{
		el.removeChild(el.firstChild);
		el.removeChild(el.firstChild);
		el.removeChild(el.firstChild);
		el.removeChild(el.firstChild);
		if(need_scroll)
		{
			el.scrollTop=el.scrollHeight;
		}	
	}

}
function log(a)
{
	append_messages("LOG: "+a+"<br>");
}
var resizer=setTimeout('resize()',1000);
last_ww=0;
last_wh=0;
llast_ww=0;
llast_wh=0;
function resize()
{
	window.status='';
	clearTimeout(resizer);


	if(!jQuery.browser.opera)
	{
		resizer=setTimeout('resize()',100);
	}
	
	var wh=$(window).height();
	if(jQuery.browser.opera)
		wh=$(document).height();

	var ww=$(window).width();
	if(jQuery.browser.opera)
		ww=$(document).width();

	if((wh==last_wh && ww==last_ww) || (wh==llast_wh && ww==llast_ww)) return;
	
	llast_ww=last_ww;
	llast_wh=last_wh;
	
	last_ww=ww;
	last_wh=wh;
	$("#buttons").css("left","0");
	$("#buttons").css("top","0");
	$("#buttons").css("width",ww-4);
	$("#buttons").css("height",butt_size);


	$("#messages").css("left","0");
	$("#messages").css("top",butt_size+2);
	$("#messages").css("width",ww-221);
	$("#messages").css("height",wh-butt_size-2-console_size-2);
	
	$("#users").css("left",ww-220+7);
	$("#users").css("top",butt_size+2);
	$("#users").css("width",220-8-7);
	$("#users").css("height",wh-butt_size-2-console_size-2 );
	
	 	
	$("#addmessage").css("left","3");
	$("#addmessage").css("top",wh-console_size+6);
	$("#addmessage").css("width",ww-4);
	$("#addmessage").css("height",console_size);

	$("#wsego").css("left",ww-65);
	$("#wsego").css("top",wh-console_size+20);
	$("#wsego").css("width",65);
	$("#wsego").css("height",20);
	return true;
}
var pagetitle = document.title;
var topic='';
function set_topic(t)
{
	var s='';
	if(moderated) s='[+m] ';
	if(t!=''){
		document.title=pagetitle+" "+s+"- "+t;
	}else{
		document.title=pagetitle+" "+s;
	}
	topic=t;
}
function set_moderated(n)
{
	if(document.sendform.moderated)
		document.sendform.moderated.checked=n;
	moderated=n;
}

uinfo=0;
locat="";
function UserinfoID(uid)
{
	
	r=Math.round(Math.random(123)*1000);
	locat='/c2/chat_userinfo2.php?id='+uid;
	
	open(locat,'uinfo'+r,'toolbar=0,status=0,resizable=1,scrollbars=1,width=1000,height=800');
	return false;
}
function userinfoNI(nick)
{
	r=Math.round(Math.random(123)*1000);
	{
		locat='/c2/chat_userinfo2.php?ni='+escape(nick);
		open(locat,'uinfo'+r,'toolbar=0,status=0,resizable=1,scrollbars=1,width=1000,height=800');
	}
	return false;
}
function DoInvite(sid, who, nick, txt, tm)
{
	n='invite'+Math.round(Math.random(123)*1000);
	invitewin=open('/c2/chat2/invite_window.php?sid='+sid+'&txt='+escape(txt)+'&time='+escape(tm)+'&who='+who, n, 'toolbar=0,status=0,resizable=0,scrollbars=0,width=600,height=50');
/*
	s='<html> <title>Чат \"Тусовка\" - '+tm+'</title>\n';
	s+='<LINK rel=\"stylesheet\" type=\"text/css\" href=\"/css/main.css\">';
	s+='<BODY>';
	if(invite_sound){
		s+='<bgsound src=ringout.wav>\n';
	}
	s+='<table border=0 width=100%>\n';
	s+='<tr><td>Пользователь <font class=nick><b>';
	s+=who;
	s+='</b></font> пытается привлечь внимание <font class=nick><b>'+nick+'</b></font>!\n'+
	'</td></tr>\n';
	if (txt!='' && txt!=null){
		s+='<tr><td width=\"90%\" valign=\"top\">\n<font class=yelmsgnb>';
		s+=txt;
		s+='</font>\n</td><td valign=top><form name=frm>';
		s+='<input name=repl type=button OnClick=\"window.close();window.opener.focus();window.opener.InviteUser(\''+who+'\',\''+sid+'\');\" value=\"Ответить\" class=b_l>';
		s+='</form></td></tr>\n';
	}
	s+='</table></html>';
	invitewin.document.write(s);
	invitewin.document.close();
*/	
}

function AddUser(u)
{
	return _AddUser(u);
		
}
function UpdateUsers(list)
{
	currentArray=new Array();
	$("#users").html("<div class=prisut>Присутствуют</div>");
	for(var i in list){
		AddUser(list[i],1);
	}

}
function DeleteUser(d)
{
	$("#usr"+d).remove();
	var tmp=new Array();
	for(i in currentArray)
	{	
		if(currentArray[i].uid!=d)
			tmp[tmp.length]=currentArray[i];
	}
	currentArray=tmp;
	$("#wsego").html("Всего "+currentArray.length);
	 
}
var menu_opened=false;

function OpenMenu(id,nick)
{
	CloseMenu();
	if(!menu_opened)
	{
	menu_opened=true;

	$("#umenu").load("_umenu.php",{channel:document.buttonsform.channel.options[document.buttonsform.channel.selectedIndex].value,zid:id},
	function(data)
	{
		$("#umenu").css("top",mousey-10);
		$("#umenu").css("left",mousex-10);
		
		if($("#umenu").width()+mousex>last_ww)
		{
			var x_overflow=last_ww-mousex-$("#umenu").width();
			$("#umenu").css("left",mousex-10+x_overflow);
		}
		if($("#umenu").height()+mousey>last_wh)
		{
			var y_overflow=last_wh-mousey-$("#umenu").height();
			$("#umenu").css("top",mousey-10+y_overflow);
		}

		$("#umenu").show();
	
	}
	);

	

	}
	return false;
}
function CloseMenu()
{
	if(menu_opened)
	{
		menu_opened=false;
		$("#umenu").hide();
	}
}
</script>
<!--
	append_messages('on resize '+screen.width+' '+screen.height);
	clearTimeout(resizer);
	resizer=setTimeout('resize(1)',100);
	need_resize=true;
	return true;
"

-->
<body  onload="on_load();" onKeyDown="return on_key(event.keyCode);"" >
	<div id='ifrm'>
		<iframe name='persistent' src='/chat_messages2.tse' width=0 height=0 frameborder=0></iframe>
	</div>
	<div id="buttons" onclick='CloseMenu()'>
	<?
	include "buttons.php";
	?>
	</div>
	<div id="messages" onclick='CloseMenu()'></div>
	
	<div id="users" onclick='CloseMenu()'>
	<div class=prisut>Присутствуют</div>
	</div>
	
	<div id='wsego'>
	</div>

<div id="addmessage" onclick='CloseMenu()'>
<?
	include "addmessage.php";
?>
</div>

	<div id='umenu'>	
	</div>

</body>
</html>
<script>
	if(!jQuery.browser.opera)
	{
		clearTimeout(resizer);
		resizer=setTimeout('resize()',100);
		need_resize=true;
	}
	resize();
</script>