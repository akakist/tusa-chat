	function checkform()
	{
	if(document.form1.pass.value=="")
	{
		alert("�� ������ ������ ��� ������...");
		document.form1.pass.focus();
		return false;
	}
	if(document.form1.pass.value.length<3)
	{
		alert("������ ������ ���� �� ������ 3 ��������...");
		document.form1.pass.focus();
		return false;
	}
	if(document.form1.pass2.value!=document.form1.pass.value)
	{
		alert("��� ������ �� ��������� � ��������������...");
		document.form1.pass.focus();
		return false;
	}
	if(document.form1.nick.value=="")
	{
		alert("�� ������ ������ ���� ���...");
		document.form1.nick.focus();
		return false;
	}
	if(document.form1.login.value=="")
	{
		alert("�� ������ ������ ���� �����...");
		document.form1.login.focus();
		return false;
	}

	document.form1.reg.disabled=true;
		return true;
	}
