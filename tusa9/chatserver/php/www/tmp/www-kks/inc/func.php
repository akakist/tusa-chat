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
	if($n==1) return "������";
	if($n==2) return "�������";
	if($n==3) return "�����";
	if($n==4) return "������";
	if($n==5) return "���";
	if($n==6) return "����";
	if($n==7) return "����";
	if($n==8) return "�������";
	if($n==9) return "��������";
	if($n==10) return "�������";
	if($n==11) return "������";
	if($n==12) return "�������";
}

function calc_vozrast($d,$m,$y)
{
	$curr=localtime(time());
	$l=$curr[5]-$y+1900;
	if($curr[4]<=$m){
		if($curr[3]<$d) $l--;
	}
	$pref="���";
	
	$z=$l % 10;
	if($l<10) $z=$l;
	
	if($z==1 || $l==1) $pref="���";
	if($z==2 || $z==3 || $z==4) $pref="����";
	if($l>9 && $l<20) $pref="���";
	
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