<?
	include "inc/func.php";
	include "inc/nick_func.php";

	import_request_variables("gp", "arg_");
	
	if(!isset($arg_nick) || !isset($arg_passwd)){
		header("Location: /");
		exit();
	}
	
	//is nick correct ?
	
	if(!check_nick($arg_nick) || strlen($arg_nick>16) || strlen($arg_passwd)<3 || strlen($arg_passwd)>16){
		header("Location: /");
		exit();
	}
	
	include "inc/db_conn.php";
	include "inc/db_func.php";
	
	$n=str_nick($arg_nick);
	$pass=strtoupper(md5($arg_passwd));
	
	$save=0;
	if($arg_save=="1") $save=1;
//	echo "s=$arg_save";
	
	$uid=mysql_select1("select uid from nicks where str_nick='$n'");
	if($uid==""){
		echo "0";
		exit();
	}
	$pw=mysql_select1("select pass from tbl_users where id=$uid");
	if($pw==$pass){
		gen_cookie($uid,$save);
		echo "1";
		exit();
	}else{
		echo "0";
		exit();
	}

?>