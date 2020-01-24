<?

error_reporting (E_ALL);

function mysql_select1($sql)	
{
	$r=mysql_query($sql);
	if(!$r){
		echo (mysql_error() . "SQL: $sql");
		return '';
	}
	$res = mysql_fetch_array($r);
	if(count($res)) return $res[0];
	return '';
}

function mysql_select1row($sql)	
{
	$r=mysql_query($sql);
	if(!$r){
		echo (mysql_error() . "SQL: $sql");
		return array();
	}
	$res = mysql_fetch_array($r);
	return $res;
}

function check_session()
{
	if(!isset($_COOKIE['cid'])) return false;

	$ipp=$_SERVER['REMOTE_ADDR'];
	$r=split('\.',$ipp);
	$ip=sprintf("%c%c%c%c",$r[0],$r[1],$r[2],$r[3]);

	$c=$_COOKIE['cid'];
	$cc=base64_decode($c);
	$ip1=$cc[0].$cc[1].$cc[2].$cc[3];

	//ip sess and ip client mismatch, return
	if($ip!=$ip1) return false;

	$uid=mysql_select1("select uid from chat_session where cookie='$c'");
	if($uid=="") return false;
	return $uid;
}

?>