<?
	include "inc/nick_func.php";
	
	import_request_variables("gp", "arg_");

	session_start();

	$valid_key=0;
	header("Content-Type: text/html; charset=\"windows-1251\"");

	if($arg_key=="" || $_SESSION['key'] != $arg_key){
//		echo "1:Контрольное число введено неверно";
		echo "1\nКонтрольное число введено неверно";
		exit();
	}

	if(!check_nick($arg_nick) || strlen($arg_nick)>16){
		echo "2\nНеверный ник";
		exit();
	}
	if(strlen($arg_passwd)<3 || strlen($arg_passwd)>16){
		echo "2\nКороткий или слишком длинный пароль";
		exit();
	}
	if($arg_fname=="" || strlen($arg_fname)>32){
		echo "2\nВведите реальное имя!";
		exit();
	}
	if($arg_city=="" || strlen($arg_city)>32){
		echo "2\nВведите город";
		exit();
	}
		
	if($arg_gender!="1" && $arg_gender!="2"){
		echo "2\nнеправильный пол -$arg_gender-";
		exit();
	}
	
	include "inc/db_conn.php";
	include "inc/db_func.php";
	include "inc/func.php";
	
	$un=str_nick($arg_nick);
	$id=mysql_select1("select id from nicks where str_nick='$un'");
	if($id!=""){
		echo "2\nНик уже существует";
		exit();
	}

	if($arg_newcity==1){
		mysql_query("insert into cities (name) values ('$arg_city')");
	}

	$pass=strtoupper(md5($arg_passwd));
	mysql_query("insert into tbl_users (reg_date,pass,gender,fname,city) values (NOW(),'$pass',$arg_gender,'$arg_fname','$arg_city')");
	$uid=mysql_select1("select LAST_INSERT_ID() from tbl_users");
	mysql_query("insert into nicks (nick,str_nick,uid,last_usage_date) values ('$arg_nick','$un',$uid,NOW())");
	$nid=mysql_select1("select LAST_INSERT_ID() from nicks");
	
	mysql_query("update users set last_nick_id=$nid, last_nick='$arg_nick' where id=$uid");
	
//	echo "0\nПолный зачоддд!!";

	unset($_SESSION['key']);

	gen_cookie($uid,0);

	echo "0";
?>
