<?
	include "../inc/db_conn.php";
	include "../inc/db_func.php";
	include "../inc/nick_func.php";
	
        import_request_variables("gp", "arg_");
	header("Content-Type: text/html; charset=\"windows-1251\"");

	if(!preg_match("/^\d+$/",$arg_id)){
		echo "��������...";
		exit();
	}
	
	if(!($uid=check_session())) {
		header("Location: /");
		exit();
	}
	
	$r=mysql_query("select * from detailed_user_info where uid='$arg_id'");
	if(mysql_num_rows($r)<1){
?>
		<center>
		<br><br><br>
		� ��������� ������������ ��� ��� �� �������� ���� ���� :(
		<br><br><br><br>
		</center>
<?		exit(0);
	}
?>
