<?
	include "../inc/db_conn.php";
	include "../inc/db_func.php";
	include "../inc/nick_func.php";
	
        import_request_variables("gp", "arg_");
	
	if(!isset($arg_nick) || strlen($arg_nick)>32){
		echo "2";
		exit();
	}
	
	if(!check_nick($arg_nick)){
		echo "2";
		exit();
	}

	$snick=str_nick($arg_nick);
	
	$enick=mysql_select1("select id from nicks where str_nick='$snick'");
	$ex=1;
	if($enick!="") $ex=1;
	else $ex=0;
	echo "$ex";

?>
