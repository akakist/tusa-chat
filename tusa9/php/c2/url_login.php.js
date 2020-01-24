  function chk_f()
  {
    if(!document.loginform.nick){return true;}
        if(document.loginform.nick.options.length==0){
                alert('У Вас нету ников для входа в чат... Создайте себе хотя бы один ник!');
                return false;
        }
        return true;
  }

 function AddNick()
 {
	 nwin=open('/newnick.tse', 'NewNick', 'toolbar=0,status=0,resizable=0,scrollbars=0,width=350,height=160');
	 nwin.focus();
	 return false;
 }
 function remove_nick()
 {
	 d=document.loginform;
	 n=document.loginform.nick.selectedIndex;
	 if(!confirm('Удалить ник "'+d.nick.options[n].text+'" ?')){
		 return false;
	 }
 	$.post("/remove_nick.tse",{nick:$("#_nick").val()},function(data){window.location.reload();});
	
//	 document.tempform.nick.value=d.nick.options[n].value;
//	 document.tempform.removenick.value='yes';
//	 document.tempform.submit();
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
