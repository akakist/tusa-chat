<?
        import_request_variables("gp", "arg_");

	include "inc/db_conn.php";
	include "inc/db_func.php";
	include "inc/func.php";
	
	if(!($uid=check_session())) {
		header("Location: /");
		exit();
	}
	
	if($arg_page=="" || $arg_page=="1") include "inc/profile_edit_main.php";
	if($arg_page=="2") include "inc/profile_edit_contacts.php";

?>

