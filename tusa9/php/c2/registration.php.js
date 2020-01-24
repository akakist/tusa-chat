	function checkform()
	{
	if(document.form1.pass.value=="")
	{
		alert("Вы забыли ввести Ваш пароль...");
		document.form1.pass.focus();
		return false;
	}
	if(document.form1.pass.value.length<3)
	{
		alert("Пароль должен быть не короче 3 символов...");
		document.form1.pass.focus();
		return false;
	}
	if(document.form1.pass2.value!=document.form1.pass.value)
	{
		alert("Ваш пароль не совпадает с подтверждением...");
		document.form1.pass.focus();
		return false;
	}
	if(document.form1.nick.value=="")
	{
		alert("Вы забыли ввести свой ник...");
		document.form1.nick.focus();
		return false;
	}
	if(document.form1.login.value=="")
	{
		alert("Вы забыли ввести свой логин...");
		document.form1.login.focus();
		return false;
	}

	document.form1.reg.disabled=true;
		return true;
	}
