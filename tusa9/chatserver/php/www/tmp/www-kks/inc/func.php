<?

function gen_cookie($_uid,$save)
{
	$s=$_uid.time();
	$ip=$_SERVER['REMOTE_ADDR'];
	$r=split('\.',$ip);
	$l=sprintf("%c%c%c%c",$r[0],$r[1],$r[2],$r[3]);
	$l.=pack("I*",$_uid,time(), rand());
	
//	$l=pack('C*',]);
	$c=base64_encode($l);
	//echo "$ip C=". $c;
	mysql_query("delete from chat_session where uid='$_uid'");
	mysql_query("insert delayed into chat_session (cookie,last_time,dont_delete,uid) values ('$c',NOW(),'$save','$_uid')");
	if($save){
		setcookie("cid", $c, time() + 3600*24*30);
	}else{
		setcookie("cid", $c);
	}
	return $c;
}

function rus_months($n)
{
	if($n==1) return "€нвар€";
	if($n==2) return "феврал€";
	if($n==3) return "марта";
	if($n==4) return "апрел€";
	if($n==5) return "ма€";
	if($n==6) return "июн€";
	if($n==7) return "июл€";
	if($n==8) return "августа";
	if($n==9) return "сент€бр€";
	if($n==10) return "окт€бр€";
	if($n==11) return "но€бр€";
	if($n==12) return "декабр€";
}

function calc_vozrast($d,$m,$y)
{
	$curr=localtime(time());
	$l=$curr[5]-$y+1900;
	if($curr[4]<=$m){
		if($curr[3]<$d) $l--;
	}
	$pref="лет";
	
	$z=$l % 10;
	if($l<10) $z=$l;
	
	if($z==1 || $l==1) $pref="год";
	if($z==2 || $z==3 || $z==4) $pref="года";
	if($l>9 && $l<20) $pref="лет";
	
	return $l." ".$pref;
}

function checked($z)
{
	if($z) return " checked ";
}

function checked2($z,$zz)
{
	if($z==$zz) return " checked ";
}

function selected2($z,$zz)
{
	if($z==$zz) return " selected ";
}

?>