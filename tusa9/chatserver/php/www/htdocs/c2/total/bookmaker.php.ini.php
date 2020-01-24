<?
include "inc/date.php";
//include "inc/split_long.php";
//include "inc/remove_maty.php";
//include "inc/remove_tags.php";
//include "inc/replace_links.php";
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


