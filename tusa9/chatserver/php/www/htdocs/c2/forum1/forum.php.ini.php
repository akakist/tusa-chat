<?
include "inc/date.php";
include "inc/split_long.php";
include "inc/remove_maty.php";
include "inc/remove_tags.php";
include "inc/replace_links.php";
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
function select_page($t,$tsize,$page,$FORUM_MSG_PER_PAGE)
{
	$sp="<select onchange=\"psel=this; pg=psel.options[psel.selectedIndex].value;window.location.href='/c2/forum/forum.php?";
	if($t) $sp.="t=$t&";
  	$sp.="s='+(pg-1)*$FORUM_MSG_PER_PAGE;\">";
	$p=0;
	for($i=0;$i<$tsize;$i+=$FORUM_MSG_PER_PAGE)
	{
	 	if($i<$tsize)
		{
		 	$p++;
		 	$sp.="<option value=$p ";
			if($p-1==$page) $sp.=" SELECTED ";
			$sp.=">$p\n";
		}
	 }
	 $sp.="</select>";
	 return $sp;
				
}
function nick_select($uid)
{
	$out="";
	$out.='<select name="nick">';
	
	$nid=mysql_select1("select last_nick_id from tbl_users where id='$uid'");
	$res=mysql_query("select id,nick from nicks where uid='$uid' order by 2") or die(mysql_error());
	while($r=mysql_fetch_row($res))
	{
		$id=$r[0];
		$n=$r[1];
		if($nid==$id)
		$out.="<option value=$id selected> $n\n";
		else
		$out.= "<option value=$id> $n\n";
	}
	$out.="	</select>";
	return $out;
}

////body

$forum=1;
if(isset($arg_add) && isset($arg_data))
{
	$nid=intval($arg_nick);
	$nick=mysql_select1("select nick from nicks where id='$nid'");
	$ip=$_SERVER['REMOTE_ADDR'];
	$msgc=0;
	if(strlen($arg_msg))$msgc=1;

	if(strlen($arg_ta)==0) die("не введена тема");
 	$arg_ta=remove_maty(split_long($arg_ta));
	
 	if(!isset($_SESSION['privs']['tags'])) $arg_ta=remove_tags($arg_ta);
 	$arg_ta=replace_links($arg_ta);
	$arg_ta=preg_replace("/[\n\r]+/","",$arg_ta);
	$arg_ta=mysql_escape_string($arg_ta);
 	mysql_query("insert into Forum_themes (author,name,nid,uid,ip,add_date,create_date,msgcnt,last_by,last_by_id) values('$nick','$arg_ta','$nid','$uid','$ip',NOW(),NOW(),'$msgc','$nick','$nid')") or die(mysql_error());
	$tid=mysql_select1("select last_insert_id()");
 	$arg_msg=remove_maty(split_long($arg_msg));
 	if(!isset($_SESSION['privs']['tags'])) $arg_msg=remove_tags($arg_msg);
 	$arg_msg=replace_links($arg_msg);
	$arg_msg=preg_replace("/[\n\r]+/","[BR]",$arg_msg);
	$_SESSION['last_nick']=$nick;
	$_SESSION['last_nick_id']=$nid;
	if($tid)
	{
		$nick=mysql_escape_string($nick);
		$arg_msg=mysql_escape_string($arg_msg);
		$ip=$_SERVER['REMOTE_ADDR'];
		 mysql_query("insert into Forum_messages (author,subj,tid,nid,uid,ip,add_date,msg) values('$nick','','$tid','$nid','$uid','$ip',NOW(),'$arg_msg') ") or die(mysql_error());

	}
	header("Location: /c2/forum/forum.php");die;
}

if(isset($_SESSION['privs']['forum']))
{
	$adm=1;
}
if(isset($arg_rmth) && isset($arg_t))
{
	$arg_t=intval($arg_t);
	mysql_query(sprintf("delete from Forum_messages where tid='%d'",$arg_t)) or die(mysql_error());
	mysql_query(sprintf("delete from Forum_themes where id='%d'",$arg_t)) or die(mysql_error());
 	header("Location: /c2/forum/forum.php");die;
}
if(isset($arg_addmsg) && isset($arg_t))
{
	$arg_t=intval($arg_t);
 	$arg_msg=remove_maty(split_long($arg_msg));
 	$arg_subj=remove_maty(split_long($arg_subj));
 	
 	if(!isset($_SESSION['privs']['tags'])) $arg_msg=remove_tags($arg_msg);
 	if(!isset($_SESSION['privs']['tags'])) $arg_subj=remove_tags($arg_subj);
// 	$arg_msg=set_font($arg_msg);
 	$arg_msg=replace_links($arg_msg);
	$arg_msg=preg_replace("/[\n\r]+/","[BR]",$arg_msg);
//	$arg_msg=preg_replace("/[\n\r]+/","[BR]",$arg_msg);
	$nid=intval($arg_nick);
	$nick=mysql_select1("select nick from nicks where id='$nid'");
	$_SESSION['last_nick']=$nick;
	$_SESSION['last_nick_id']=$nid;
	$arg_t=intval($arg_t);
	$tid=mysql_select1("select id from Forum_themes where id='$arg_t'");
	if($tid)
	{
		$nick=mysql_escape_string($nick);
		$arg_subj=mysql_escape_string($arg_subj);
		$arg_msg=mysql_escape_string($arg_msg);
		$ip=$_SERVER['REMOTE_ADDR'];
		mysql_query("insert into Forum_messages (author,subj,tid,nid,uid,ip,add_date,msg) values('$nick','$arg_subj','$arg_t','$nid','$uid','$ip',NOW(),'$arg_msg') ") or die(mysql_error());
		mysql_query("update Forum_themes set msgcnt=msgcnt+1, add_date=NOW(),last_by='$nick' where id='$arg_t'") or die(mysql_error());
	}
	header("Location: /c2/forum/forum.php?t=$arg_t");die;
}
?>


