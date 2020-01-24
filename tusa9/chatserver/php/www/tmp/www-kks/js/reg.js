

var aj=null;
var valid_nick=0;


function process_nick_response()
{
	if(aj.readyState==4){
//		document.getElementById("nickhelp").innerHTML=
		var c=aj.responseText;
		var h=document.getElementById("nickhelp");
		if(c=="0"){
			h.innerHTML="<b><font color=darkgreen>Ник свободен!</font></b>";
			valid_nick=1;
		}else
		if(c==1){
			h.innerHTML="<b><font color=darkred>К сожалению ник занят...</font></b>";
		}else{
			h.innerHTML="<b><font color=darkred>Недопустимый ник.</font></b>";
		}
	}
}

function check_nick()
{
	var n=document.getElementById("rnick").value;
	document.getElementById("nickhelp").innerHTML="Проверяем...";
	aj=CreateAjax();
//	alert(escape(n));
	aj.open("GET","/ajax/check_nick.php?nick="+escape(n),true);
	aj.send(null);
	aj.onreadystatechange=process_nick_response;
}

function check_city()
{
	var sel=document.reg_form.city;
	if(sel.options[sel.selectedIndex].value=="0"){
		document.getElementById("other_city_div").style.display="block";
		document.reg_form.other_city.focus();
	}else{
		document.getElementById("other_city_div").style.display="none";
	}
	return true;
}


function submit_reg()
{
	ok=true;
	if(!valid_nick){
		document.getElementById("rnick").style.backgroundColor="#ffc0c0";
		ok=false;
	}else{
		document.getElementById("rnick").style.backgroundColor="";
	}
	
	if(document.reg_form.fname.value==""){
		document.getElementById("fname").style.backgroundColor="#ffc0c0";
		ok=false;
	}else{
		document.getElementById("fname").style.backgroundColor="";
	}
	
	if(document.reg_form.rpasswd.value!=document.reg_form.rpasswd2.value){
		document.getElementById("rpasswd").style.backgroundColor="#ffc0c0";
		document.getElementById("rpasswd2").style.backgroundColor="#ffc0c0";
		ok=false;
	}else{
		document.getElementById("rpasswd").style.backgroundColor="";
		document.getElementById("rpasswd2").style.backgroundColor="";
	}

	if(document.reg_form.rpasswd.value.length<3){
		document.getElementById("rpasswd").style.backgroundColor="#ffc0c0";
		ok=false;
	}else{
		document.getElementById("rpasswd").style.backgroundColor="";
	}
	
	var re=new RegExp("[0-9]{5}");
	if(!document.reg_form.key.value.match(re)){
		document.getElementById("key").style.backgroundColor="#ffc0c0";
		document.getElementById("keyhelp").innerHTML="<b><font color=darkred>Число введено неверно...</b></font>"
		ok=false;
	}else{
		document.getElementById("key").style.backgroundColor="";
		document.getElementById("keyhelp").innerHTML="Введите число на картинке.";
	}
	
	if(ok){
		var f=document.reg_form;
		
		
		f.sub.value="Ждите...";
		f.sub.disabled=true;
		var reg_aj=CreateAjax();
		var gender="2";
		if(document.getElementById("male").checked) gender="1";

		var city;
		var selcity=document.reg_form.city;
		var new_city="0";
		
		if(selcity.options[selcity.selectedIndex].value=="0"){
			city=document.reg_form.other_city.value;
			new_city="1";
		}else{
			city=selcity.options[selcity.selectedIndex].text;
		}
		
		var city_id=selcity.options[selcity.selectedIndex].value;

		var d="nick="+escape(f.rnick.value)+"&";
		d+="fname="+escape(f.fname.value)+"&";
		d+="passwd="+escape(f.rpasswd.value)+"&";
		d+="gender="+escape(gender)+"&";
		d+="city="+escape(city)+"&";
		d+="newcity="+new_city+"&";
		d+="key="+escape(f.key.value);

		reg_aj.open("POST","/registration.php?"+document.getElementById("session").name+"="+document.getElementById("session").value,false);
		reg_aj.setRequestHeader("Content-type", "application/x-www-form-urlencoded"); 
		reg_aj.send(d);
		f.sub.value="Зарегистрироваться";
		f.sub.disabled=false;

		var resp=reg_aj.responseText.split("\n");
		if(resp[0]=="0"){
//			alert("Регистрация ОК!");
			window.location="/my";
		}
		else
		if(resp[0]=="1"){
			document.getElementById("key").style.backgroundColor="#ffc0c0";
			document.getElementById("keyhelp").innerHTML="<b><font color=darkred>Число введено неверно...</b></font>"
		}else
		if(resp[0]=="2"){
			alert(resp[1]);
		}else{
			alert("Сервер временно недоступен...");
		}
	}
}

function do_login()
{
	var f=document.login_form;
	if(f.nick.value==""){
		alert("Вы забыли ввести ник...");
		f.nick.focus();
		return false;
	}
	if(f.passwd.value.length<3){
		alert("Пароль должен быть не короче 3х символов...");
		f.passwd.focus();
		return false;
	}
	var d="nick="+escape(f.nick.value)+"&";
	d+="passwd="+escape(f.passwd.value)+"&";
	if(f.save.checked){
		d+="save=1";
	}else{
		d+="save=0";
	}
//	alert(d);

	f.passwd.value="";
	f.subm.value="Ждите...";
	f.subm.disabled=true;

	var log_aj=CreateAjax();
	log_aj.open("POST","/login.php",false);
	log_aj.setRequestHeader("Content-type", "application/x-www-form-urlencoded"); 
	log_aj.send(d);
//	alert(log_aj.responseText);

	if(log_aj.responseText=="1"){
		window.location="/my";
	}else{
		document.getElementById("login_info").innerHTML="<center><font color=darkred>Ник или пароль<br>введены неверно...</font></center>";
		f.subm.value="Вход";
		f.subm.disabled=false;
		f.passwd.focus();
	}
	return false;
}

