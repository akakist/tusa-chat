function chk_f()
{
	if(document.f.msg.value==""){
		alert('Введите сообщение');
		document.f.msg.focus();
		return false;
	}
	document.f.smt.disabled=true;
	return true;
}

function d_r(n)
{
	s=document.getElementById('bex'+n).innerHTML;
/*	re=/<BR>/g;	s=s.replace(re,'\r\n');
	re=/<br>/g;	s=s.replace(re,'\r\n');
	re=/<\/A>/g;	s=s.replace(re,'');
	re=/<\/FONT>/g;	s=s.replace(re,'');
	re=/<[A,F].{1,}>/g;	s=s.replace(re,'');
	re=/&lt;/g;		s=s.replace(re,'<');
	re=/&gt;/g;		s=s.replace(re,'>');
*/	
	au=document.getElementById('au'+n).innerHTML;
 	document.f.msg.value="[quote]"+s+"\n[small]@"+au+"[/small][/quote]\n";
	ms=document.getElementById('s'+n).innerHTML;
	document.f.subj.value='Re:'+ms;
	document.location.href="#add";
	document.f.msg.focus();
	return false;
}

function remove_msg(n)
{
	$('#d'+n).load("/c2/forum/_remove_msg.php?n="+n);
	if(jQuery.browser.msie) location.reload();
	return false;
}

uinfo=0;
function ui(nick)
{
	r=Math.round(Math.random(123)*1000);
	{
		locat='/c2/chat_userinfo2.php?ni='+escape(nick);
		open(locat,'uinfo'+r,'toolbar=0,status=0,resizable=1,scrollbars=1,width=1000,height=800');
	}
	return false;
}

function chk_add()
{
	 if (document.f.ta.value==''){
	 	alert('Вы забыли ввести тему...');
		 document.f.ta.focus();
		 return false;
	 }
	 if (document.f.msg.value==''){
	 	if (confirm('Вы не ввели первое сообщение. Продолжить?')) return true;
		 document.f.msg.focus();
		 return false;
	 }
	return true;
}

function voting(aElement,aValue) {
	   var el=document.getElementById(aElement);
	   el.value = aValue;
	    el.parentNode.submit();
}


