
function DoSend()
{
	var d=document.sendform;
	if (d.msgbox.value=='')
	{
		d.msgbox.focus();
		return false;
	}
	msgs[max_m]=d.msgbox.value;
	max_m++;
	curr_m=max_m;
	
	var sys=false;
	if(document.sendform.sysbox)
		sys=document.sendform.sysbox.checked;
        $.post("/chat_sendmessage.tse",{
		msg: escape(document.sendform.msgbox.value),
		fornick: escape(document.sendform.fornick.value),
		priv: document.sendform.privbox.checked,
		sys: sys,
		makeit: document.sendform.makeitbox.checked,
		version:9,
               	r: Math.random()
                  },function(data){append_messages(data); });
	
	d.msgbox.focus();
	d.msgbox.value="";

	var secs=last_date.getSeconds();
	dt2=new Date();
	var secs2=dt2.getSeconds();
	var psec;
	if(secs>secs2){
		psec=(60-secs)+secs2;
	}else{
		psec=secs2-secs;
	}
	if(psec>=30){
		last_date=new Date();
	}
	return false;
}

function XMM2RUS (obj) {
	chrs=" !Э№;%?э()*+б-ю.0123456789ЖжБ=Ю,\"ФИСВУАПРШОЛДЬТЩЗЙКЫЕГМЦЧНЯх/ъ:_ёфисвуапршолдьтщзйкыегмцчняХ\\ЪЁ"
	so=document.sendform.msgbox.value;
	s=""
	for (i=0;i<so.length;i++){
		ch = so.charAt(i).charCodeAt();
		s+=ch<0x80 ? chrs.charAt(ch-0x20) : so.charAt(i);
	}
	document.sendform.msgbox.value=s;
	document.sendform.msgbox.focus();
}
function on_to_all_click()
{
	document.sendform.fornick.value='Всем';
	document.sendform.privbox.checked=false;
	document.sendform.makeitbox.checked=false;
	document.sendform.msgbox.focus();
	if(level>899) document.sendform.sysbox.checked=false;
}

function on_key(code)
{
//	alert(code);
	if(code==113){XMM2RUS(); return false;}
	if(code==118){document.sendform.privbox.checked=!document.sendform.privbox.checked;document.sendform.msgbox.focus(); return false;}
	if(code==119){document.sendform.makeitbox.checked=!document.sendform.makeitbox.checked; document.sendform.msgbox.focus();return false;}
	if(code==27) {document.sendform.msgbox.value=''; document.sendform.msgbox.focus();return false;}
	if(code!=38 && code!=40) return true;
	if(max_m<=0) return true;
	if(code==38 && curr_m>0) curr_m--;
	if(code==40 && curr_m<max_m) curr_m++; 
	s = "";
	if(curr_m<max_m) s=msgs[curr_m];
	document.sendform.msgbox.value=s;

	document.sendform.msgbox.focus();

	return false;
}

function _AddUser(u)
{
	var s="";
	
	var nick=u.n;
	
	if(u.v) nick='+'+nick;
	
	var r="";
	// nick
	r="<a class='"+u.ns+"' href='#' onclick='return Answer("+u.uid+","+u.nid+",\""+u.n+"\",0);'>"+nick+"</a>\n";

	s+="<span class=ni oncontextmenu='return OpenMenu("+u.uid+",\""+u.n+"\");'>"+r+"</span>\n";
	r="";
	var status='<img border=0 name="i'+u.uid+'" id="i'+u.uid+'" src="/pics/s/sp'+u.spn+'.gif" alt=\''+u.sn+'\' title=\''+u.sn+'\'/>\n';

	if(u.uid!=uid)
		r+="<a href=\"#\" onclick=\"return InviteUser('"+u.n+"',"+u.uid+");\">"+ status+ '</a>\n';
	else 
		r+=status;	
	s+="<span class=invite>"+r+"</span>\n";
/*
*/
	r="";
	// userinfo 
	if(u.hi)
	{
		var isig="";
		if(full_butt!=1 && u.ign==1)isig="ig";
		SS='<a href="#" onclick="return UserinfoID('+u.uid+');" ><img border=0 name=inf'+u.uid+' id=inf'+u.uid+' src="/pics/uinfo'+u.g+isig+'.gif" alt="Инфо о пользователе" title="Инфо о пользователе"></a>\n';
		s+=SS;
	}
	s+="<span class=info>"+r+"</span>";

	full_butt=false;
	if(full_butt)
	{
		r="";
		if (u.a!=0)
		{
			var ad='Админ';
			if(u.g==2) ad='Админша';
			r="<img border=0 src='/pics/admin"+u.ae+".gif' alt='"+ad+"' title='"+ad+"'>";
			s+="<span class=eye>"+r+"</span>\n";
			
		}
		else if(u.uid!=uid)
		{
			r="<a  href=\"#\" OnClick=\"return IgnoreUser('"+u.uid+"');\">";
			if (u.ign==1)
			{
				r+="<img   border=0 name='ig"+u.uid+"' id='ig"+u.uid+"' src='/pics/ignr.gif' alt='Игнорируемый' title='Игнорируемый'></a>";
			}
			else
			{
				r+="<img  border=0 name='ig"+u.uid+"' id='ig"+u.uid+"' src='/pics/ign.gif' alt='Игнорировать'  title='Игнорировать'></a>";
				
			}
			s+="<span class='ignore'>"+r+"</span>\n";
			
		}
		else
		{
		s+='<span class="ignore-empty"> </span>\n';
		}
		if(u.kb)
		{
			s+="<span class=kb><a  href=\"#\" OnClick=\"return KickUser('"+u.uid+"','"+u.n+"');\"><img border=0 src='/pics/kick.gif' alt='Пинануть'></a></span>\n";
		}
		else
		{
			s+='<span class=kbempty></span>\n';
		}
	}
	
	var need_add=true;
	var a={nu:u.nu,uid:u.uid};
	a.nu=u.nu;
	a.uid=u.uid;
	sd="<div class='ulist-row' id='usr"+u.uid+"'>\n"+s+"</div>\n";
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
	
	$("#wsego").html("Всего "+currentArray.length);

}

function _ChangeIgnore(ud,st,g)
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
function ch_room()
{
	$("#messages").html("");
	$("#users").html("<div class=prisut>Присутствуют</div>");
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


function ch_voice(zid)
{
	$.get("/change_voice.tse",{channel: document.buttonsform.channel.options[document.buttonsform.channel.selectedIndex].value,zid:selected_nick_uid, r:Math.random()}, 
		function(data){
			append_messages(data);
			document.sendform.msgbox.focus();
		} );

	return false;
}

function KickUser(zuid,nm)
{
	s=prompt(nm+' будет выставлен из чата за ?????? (Указать за что, например: "маты", только без слова "ЗА")','');
	if(s==null)
	{
		return false;
	}
	$.get("/kick_user.tse",{zid:zuid,msg:s, r:Math.random()}, 
		function(data){
			append_messages(data);
			document.sendform.msgbox.focus();
		} );	
	return false;
}

function KickUserZa(zuid,za)
{
	$.get("/kick_user.tse",{zid:zuid,msg:za, r:Math.random()}, 
		function(data){
			append_messages(data);
			document.sendform.msgbox.focus();
		} );	
	return false;
}

function open_n(param)
{
    w=780;
    h=500;
    if(param!='undefined'){
    	param='?'+param;
    }else{
    	param='';
    }
	nwin=open('/notes.tse/frames.tse'+param, 'notes', 'toolbar=0,status=0,resizable=1,scrollbars=1,left=10,top=10,width='+w+',height='+h);
	nwin.focus();
	return false;
}
function o_l(url)
{
	r=Math.round(Math.random(123)*1000);
	n=window.open(url,'wind'+r,'toolbar=1,menubar=1,status=1,location=1,status=1,resizable=1,scrollbars=1,personalbar=1,directories=1');
	return false;
}


function set_state_hide_female(){}
function set_state_hide_male(){}
function set_state_contact_mode(){}
