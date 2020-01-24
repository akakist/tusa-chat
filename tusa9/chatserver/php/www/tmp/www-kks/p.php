<?
//	echo "-".$_COOKIE['cid']."-";
//	ini_set('display_errors','1');
//	ini_set('display_startup_errors','1');
	
//	echo phpinfo();

//	echo $_COOKIE['cid'];
	$c=$_COOKIE['cid'];
	$cc=base64_decode($c);
	echo "<br>cid=$c<br>decode cid=$cc";

	exit();

	$ip=$_SERVER['REMOTE_ADDR'];
	$r=split('\.',$ip);
	$l=sprintf("%c%c%c%c",$r[0],$r[1],$r[2],$r[3]);

	
	echo "<br><br>";
	$ip1=$cc[0].$cc[1].$cc[2].$cc[3];
	echo "$ip1 - $l";
	if($ip1==$l) echo "Yes!";
//	echo "sp=",sprintf('%0x',$ip1);
	
//	$ip1=sprintf("%d.%d.%d.%d",$cc[0],$cc[1],$cc[2],$cc[3]);
//	$ip1=sprintf("%u.%u.%u.%u",$c[0],$c[1],$c[2],$c[3]);
	
//	echo "ip stored $ip1";
	
	 $ip=$_SERVER['REMOTE_ADDR'];
	        $r=split('\.',$ip);
		        $l=sprintf("%d%d%d%d",$r[0],$r[1],$r[2],$r[3]);
			
//	echo $l;
//	echo "$ip !",$ip[0],"!";
?>