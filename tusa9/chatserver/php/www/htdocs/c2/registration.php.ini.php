<?

include "inc/str_nick.php";
include "inc/check_nick.php";
include "inc/check_login.php";
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
	$rs=mysql_select1("select id from tbl_users where login='$login'");
	if(isset($rs))
	{
		$error="“акой email уже зарегистрирован";
	}
	$strnick=str_nick($nick);
	$_rn=mysql_select1("select uid from nicks where str_nick='$strnick'");
	if(isset($_rn))
	{
		$error="“акой nick уже зарегистрирован  ".$_rn[0];
	}
		
	if(!isset($error) && $arg_pass!=$arg_pass2)
	{
		$error="ѕароли не совпадают";
	}
	$key='';
	if(isset($_SESSION['key'])) $key=$_SESSION['key'];
	$ekey='-fgjusdlfgkj3941';
	if(isset($arg_key)) $ekey=$arg_key;
	if($key!=$ekey)
	{
		$error=" од на картинке введен неверно";
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
		mysql_query("insert into tbl_users (upperlogin,login,pass,level,gender,foto_thumb_small,foto_thumb_big,reg_date) values ('$strl','$login',md5('$pass'),'100','$arg_gender','$thumb_small','$thumb_big',NOW())") or die(mysql_error().__FILE__.__LINE__);
		$uid=mysql_select1("select LAST_INSERT_ID()");
		//echo "uid $iuid<br>";
		mysql_query("insert into nicks (nick,str_nick,uid,banned,bby,last_usage_date) values ('$nick','$strnick','$uid','0','0',NOW())") or  die(mysql_error().__FILE__.__LINE__);;


		$_SESSION['uid']=$uid;
		$_SESSION['login']=$login;
		$_SESSION['level']=100;
		$_SESSION['cnick']=$nick;
		header("Location: /c2/settings/info.php?r=".rand());die();
	}
}
?>
