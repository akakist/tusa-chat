
function check_city()
{
	var sel=document.f.city;
//	var t=sel.options[sel.selectedIndex].value;
	if(sel.options[sel.selectedIndex].value=="0"){
		document.getElementById("other_city_div").style.display="block";
		document.f.other_city.focus();
	}else{
		document.getElementById("other_city_div").style.display="none";
	}
	return true;
}

function submit_page1()
{
	var f=document.f;
	var re=new RegExp("^[а-яА-Я]{2,32}$");
	var rec=new RegExp("^[а-яА-Я0-9- ]{2,32}$");
	if(!f.fname.value.match(re)){
		alert("Пожалуйста, введите свое РЕАЛЬНОЕ имя!");
		f.fname.focus();
		return false;
	}
	if(f.lname.value!="" && !f.lname.value.match(re)){
		alert("Введите РЕАЛЬНУЮ фамилию. Так можете оставить это поле пустым.");
		f.lname.focus();
		return false;
	}
	if(f.b_day.selectedIndex!=0 || f.b_mon.selectedIndex!=0 || f.b_year.selectedIndex!=0){
		if(f.b_day.selectedIndex!=0 && f.b_mon.selectedIndex!=0 && f.b_year.selectedIndex!=0){
		}else{
			alert("Введите день рождения полностью. Ниже Вы можете скрыть отображение этой информации.");
			return false;
		}
	}
	if(f.city.options[f.city.selectedIndex].value=="0"){
		if(!f.other_city.value.match(rec)){
			alert("Пожалуйста, заполните правильно поле ГОРОД. Допускаются только русские символы и знаки '-' и '.'");
			f.other_city.focus();
			return false;
		}
	}else{
		f.other_city.value=f.city.options[f.city.selectedIndex].text;
	}
	return true;
}

function show_pwd_line()
{
	document.f.email_changed.value="1";
	document.getElementById("passwd_div").style.display="block";
	document.f.passwd.focus();
}

function submit_page2()
{
	var f=document.f;
	if(f.email.value.search(/^\S+\@\S+\..+$/)==-1){
		alert("E-Mail введен неверно. Пожалуйста, проверьте.");
		f.email.focus();
		return false;
	}
	if(document.getElementById("passwd_div").style.display=="block"){
		if(f.passwd.value==""){
			alert("Введите пожалуйста Ваш текущий пароль. Он требуется для безопасного изменения E-MAIL.");
			f.passwd.focus();
			return false;
		}
	}
	return true;
}
