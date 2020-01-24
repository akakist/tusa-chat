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

rooms=new Array();
<?
		$sql="select name,id from channels order by id";
		$result=mysql_query($sql) or die(mysql_error());
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

var butt_size=60;
var console_size=50;
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


function set_status(idd,pn,sd)
{
	var s='i'+idd;
	if(document.getElementById(s)){
		document.getElementById(s).src='/pics/s/sp'+pn+'.gif';
		document.getElementById(s).alt=sd;
		document.getElementById(s).title=sd;
	}
	else 
		log("el "+s+" not found");
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


function ch_room()
{
	$("#messages").html("");
	$("#users").html("");
	r=Math.round(Math.random(123)*1000);
	$.get("_change_channel.php",{channel: document.buttonsform.channel.options[document.buttonsform.channel.selectedIndex].value, r:Math.random()}, 
		function(data){
			append_messages(data);
			window.persistent.location.reload();
			document.sendform.msgbox.focus();
			currentArray=Array();
		} );
	return false;
}
function ChangeIgnore(ud,st,g)
{
	        var nm="";
	        var al="";
	    	var nm='/pics/ign.gif';
	    	var al='Игнорировать';
		var iid="";
		if(full_butt)
		 	iid="ig"+ud;
		else 
			iid="inf"+ud;
	    	if(st==1){
			
			if(full_butt==1) nm='/pics/ignr.gif';
			else  nm='/pics/uinfo'+g+'ig.gif';
			if(g==0)
				al='Игнорируемое';
			else if(g==1)
				al='Игнорируемый';
			else if(g==2)
				al='Игнорируемая';
		}
		else
		{
			if(full_butt==1)   nm='/pics/ign.gif';
			else  nm='/pics/uinfo'+g+'.gif'; 
			al='Игнорировать';
	
		}
		document.getElementById(iid).src=nm;
		document.getElementById(iid).title=al;
		document.getElementById(iid).alt=al;
		


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
function resize()
{
	clearTimeout(resizer);
	resizer=setTimeout('resize()',1000);
	
	var wh=$(window).height();
	if(jQuery.browser.opera)
		wh=$(document).height();
	h=wh-$("#buttons").height()-$("#addmessage").height();
	$('#messages').height(h);
	$('#users').height(h);
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
	var s="";
	
	var nick=u.n;
	
	if(u.v) nick='+'+nick;
	
	// nick
		s+="<a class='"+u.ns+"' href='#' onclick='Answer("+u.uid+","+u.nid+",\""+u.n+"\",0);'>"+nick+"</a>";

	var status='<img border=0 name="i'+u.uid+'" id="i'+u.uid+'" src="/pics/s/sp'+u.spn+'.gif" alt=\''+u.sn+'\' title=\''+u.sn+'\'>';
	if(u.uid!=uid)
		s+="<a href=\"#\" onclick=\"return InviteUser('"+u.n+"','"+u.uid+"');\">"+ status+ '</a>';
	else 
		s+=status;	

	// userinfo 
	if(u.hi)
	{
		var isig="";
		if(full_butt!=1 && u.ign==1)isig="ig";
		SS='<a href="#" onclick="return UserinfoID(\''+u.uid+'\');"><img border=0 name=\'inf'+u.uid+'\' id=\'inf'+u.uid+'\' src="/pics/uinfo'+u.g+isig+'.gif" alt="Инфо о пользователе" title="Инфо о пользователе"></a>';
		s+=SS;
	}
	if(full_butt)
	{
		if (u.a!=0)
		{
			var ad='Админ';
			if(u.g==2) ad='Админша';
			s+="<img border=0 src='/pics/admin"+u.ae+".gif' alt='"+ad+"' title='"+ad+"' style='width:19; height:16; border:0'>";
		}
		else if(u.uid!=uid)
		{
			s+="<a href=\"#\" OnClick=\"return IgnoreUser('"+u.uid+"');\">";
			if (u.ign==1)
			{
				s+="<img border=0 name='ig"+u.uid+"' id='ig"+u.uid+"' src='/pics/ignr.gif' alt='Игнорируемый' title='Игнорируемый'></a>";
			}
			else
			{
				s+="<img border=0 name='ig"+u.uid+"' id='ig"+u.uid+"' src='/pics/ign.gif' alt='Игнорировать'  title='Игнорировать'></a>";
			}
		}
		if(u.kb)
		{
			s+="<a href=\"#\" OnClick=\"return KickUser('"+u.uid+"','"+u.n+"');\"><img border=0 src='/pics/kick.gif' alt='Пинануть'></a>";
		}
	}
	var need_add=true;
	var a={nu:u.nu,uid:u.uid};
	a.nu=u.nu;
	a.uid=u.uid;
	sd="<div id='usr"+u.uid+"'>"+s+"</div>";
	var last_nu="";
	tmp=new Array();
	var inserted=false;
	for(i in currentArray)
	{
		if(u.nu>last_nu && u.nu<currentArray[i].nu)
		{
						tmp[tmp.length]=a;
						tmp[tmp.length]=currentArray[i];
						$("#usr"+currentArray[i].uid).before(sd);
						inserted=true;
					}
					else
					{
					
						tmp[tmp.length]=currentArray[i];
					}
					last_nu=currentArray[i].nu;
				}
				if(!inserted)
				{
					tmp[tmp.length]=a;
					$("#users").html($("#users").html()+sd);
				}
				currentArray=tmp;
		
}
function UpdateUsers(list)
{
	currentArray=new Array();
	$("#users").html("");
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
}
</script>
<body onresize="return res();" onload="on_load();" onKeyDown="return on_key(event.keyCode);">
<div id="wrapper">
<script>

</script>
<div id='ifrm'>
<iframe name='persistent' src='/chat_messages2.tse' width=10 height=10 style='position: absolute; left:-100;top:-100;' frameborder=0></iframe>
</div>

	<div id="buttons">
	<?
	include "buttons.php";
	?>
	</div>

	<div id="chatcontent">
		<div id="messages">
		</div>

	</div>

	<div id="users">
	</div>

</div>

<!--div id='actions'>
<div id='actionsform'>
</div>
</div-->
<div id="addmessage">
<?
	include "addmessage.php";
?>

</div>
</body>
</html>
<script>resize();</script>