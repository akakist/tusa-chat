<?
	session_start();
	header("Content-Type: text/html; charset=\"windows-1251\"");
        import_request_variables("gp", "arg_");
?>

<!--form name="transfer" method=post-->
Для перевода другому человеку введите в поле ввода ник и нажмите <b>Перевести</b>.
<br><br>
Перевести 
<script>
 var _nick='';
 var _summa='';
</script>
<input type=text name='t_summa' value="0" maxlength=17 size=17 onchange='_summa=this.value'> кредитов на ник 
<input type=text name='t_nick' value="" maxlength=16 size=20 onchange='_nick=this.value'> 

<input type=button value="Перевести" onclick="
		$('#trans').html('<h2>Ожидаем ответ</h2>');
//		alert(_nick+' '+_summa);
		$.post('_transfer_proceed.php',
				{ nick: _nick, 
				summa: _summa
				},
				function(data)
				{
				$('#trans').html(data); 
				});

		$('#credits').load('_credits.php');
				
				return false;


">
<!--/form-->
