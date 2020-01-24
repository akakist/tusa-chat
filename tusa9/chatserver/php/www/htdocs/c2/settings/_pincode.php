<?
	session_start();
	header("Content-Type: text/html; charset=\"windows-1251\"");
        import_request_variables("gp", "arg_");
?>
<!--FORM method="GET" name="form_pin" -->

	Введите пинкод и нажмите "Пополнить"
	<input input type=text name=v maxlength=14 size=14 onchange='_pin=this.value;'>
	<input type=button value="Пополнить" onclick='
		$("#pin").html("<h2>Ожидаем ответ</h2>");
		$.post("_pin_proceed.php",
				{ v: _pin},
				function(data)
				{
				$("#pin").html(data); 
				});

		
		$("#credits").load("_credits.php");
		return false;	
	'>
<!--/form-->


