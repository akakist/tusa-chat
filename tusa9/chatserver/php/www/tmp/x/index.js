
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
	chrs=" !İ¹;%?ı()*+á-ş.0123456789ÆæÁ=Ş,\"ÔÈÑÂÓÀÏĞØÎËÄÜÒÙÇÉÊÛÅÃÌÖ×Íßõ/ú:_¸ôèñâóàïğøîëäüòùçéêûåãìö÷íÿÕ\\Ú¨"
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
	document.sendform.fornick.value='Âñåì';
	document.sendform.privbox.checked=false;
	document.sendform.makeitbox.checked=false;
	document.sendform.msgbox.focus();
	if(level>899) document.sendform.sysbox.checked=false;
}

function on_key(code)
{
//	alert(code);
	if(code==113){XMM2RUS(); return false;}
	if(code==118){document.sendform.privbox.checked=!document.sendform.privbox.checked; return false;}
	if(code==119){document.sendform.makeitbox.checked=!document.sendform.makeitbox.checked; return false;}
	if(code==27) {document.sendform.msgbox.value=''; return false;}
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
