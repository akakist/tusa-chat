<?
include "$BASE_DIR/inc/date.php";
function format_msg($msg)
{
	$msg=preg_replace("/\[quote\]/","<div class='forum-quote'>",$msg);
	$msg=preg_replace("/\[\/quote\]/","</div>",$msg);
	$msg=preg_replace("/\[small\]/","<small>",$msg);
	$msg=preg_replace("/\[\/small\]/","</small>",$msg);
	$msg=preg_replace("/[\n\r]+/","<BR>",$msg);
	$msg=preg_replace("/\[BR\]/","<BR>",$msg);
	return $msg;
}



?>


