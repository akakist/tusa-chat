<?

include "$BASE_DIR/inc/str_nick.php";
include "$BASE_DIR/inc/check_nick.php";
include "$BASE_DIR/inc/check_login.php";
$login="";
$pass="";
$nick="";
$done=false;

								
$_SESSION["rega"]=1;
if(isset($arg_DATA1))
{
	$login=$arg_login;
	$pass=$arg_pass;
	$nick=$arg_nick;
	if(!isset($error) && !check_login($login))
	{
		$error="email задан неверно, можно только латинские буквы и символы '.-_@'";
	}
	if(!isset($error) && !check_nick($nick))
	{
		$error="Nick задан неверно, можно только русские и латинские буквы '.-_@'";
	}
	$rs=mysql_select1("select id from tbl_users where login='".mysql_escape_string($login)."'");
	if(isset($rs))
	{
		$error="Такой email уже зарегистрирован";
	}
	$strnick=str_nick($nick);
	$_rn=mysql_select1("select uid from nicks where str_nick='".mysql_escape_string($strnick)."'");
	if(isset($_rn))
	{
		$error="Такой nick уже зарегистрирован  ".$_rn[0];
	}
		
	if(!isset($error) && $arg_pass!=$arg_pass2)
	{
		$error="Пароли не совпадают";
	}
	$key='';
	if(isset($_SESSION['key'])) $key=$_SESSION['key'];
	$ekey='-fgjusdlfgkj3941';
	if(isset($arg_key)) $ekey=$arg_key;
	if($key!=$ekey)
	{
		$error="Код на картинке введен неверно";
	}
		
	if(!isset($error))
	{
		$thumb_big="";
		$thumb_small="";
		if($arg_gender==1)
		{
			$thumb_big="/pics/noimage-male-big.jpg";
			$thumb_small="/pics/noimage-male-small.jpg";
		}
		else if($arg_gender==2)
		{
			$thumb_big="/pics/noimage-female-big.jpg";
			$thumb_small="/pics/noimage-female-small.jpg";
		}
		$strl=strtoupper(str_nick($login));
		mysql_query("insert into tbl_users (upperlogin,login,pass,level,gender,foto_thumb_small,foto_thumb_big,reg_date) values ('".mysql_escape_string($strl)."','".mysql_escape_string($login)."',md5('".mysql_escape_string($pass)."'),'100','".intval($arg_gender)."','".mysql_escape_string($thumb_small)."','".mysql_escape_string($thumb_big)."',NOW())") or die(mysql_error().__FILE__.__LINE__);
		$uid=mysql_select1("select LAST_INSERT_ID()");
		//echo "uid $iuid<br>";
		mysql_query("insert into nicks (nick,str_nick,uid,banned,bby,last_usage_date) values ('".mysql_escape_string($nick)."','".mysql_escape_string($strnick)."','$uid','0','0',NOW())") or  die(mysql_error().__FILE__.__LINE__);;


		$_SESSION['uid']=$uid;
		$_SESSION['login']=$login;
		$_SESSION['level']=100;
		$_SESSION['cnick']=$nick;
		header("Location: /c2/settings/info.php?r=".rand());die();
	}
}
?>
