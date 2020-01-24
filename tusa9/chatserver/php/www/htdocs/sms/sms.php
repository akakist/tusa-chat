<?

//	$kurs=27;

	$db = mysql_connect('localhost:/tmp/mysql.sock', 'root', '');
	mysql_select_db('chat') or die ('Can"t select database : ' . mysql_error());
	mysql_query("set charset cp1251") or die(mysql_error());

function mysql_select1($sql)	
{
	$r=mysql_query($sql);
	if(!$r){
		return '';
//		echo (mysql_error());
	}
	$res = mysql_fetch_array($r);
	if(count($res)) return $res[0];
	return '';
}

$smsid=$_GET['smsid'];
#echo "Ваш ответ абоненту\n";
#echo "111111111111Ваш ответ абоненту\n";
#echo 'cost='.$_GET['cost']."\n";
    $v=split(" ",$_GET['msg']);
    if(count($v)>1)
    {
	$uid=$v[1];
	$dt	=mysql_escape_string($_GET['date']);
	$cost	=$_GET['cost_rur'];
//	$cost*=$kurs;
	$operator_id	=$_GET['operator_id'];
	$user_id	=$_GET['user_id'];
	$smsid		=$_GET['smsid'];
	$num		=$_GET['num'];
	$ip		=getenv("REMOTE_ADDR");
	$file=fopen("/tmp/sms.log",'a');
	fwrite($file,"dt=$dt; cost=$cost; operator_id=$operator_id; user_id=$user_id; smsid=$smsid; num=$num ip=$ip\n");
	fclose($file);
	$credits=$cost*100;
	$cr_round=sprintf("%4.2f",$credits);
	mysql_query("insert into ext_bill(uid,dt,cost,credits,operator_id,user_id,smsid,num,ip) values ('$uid','$dt','$cost','$cr_round','$operator_id','$user_id','$smsid','$num','$ip')") or die(mysql_error());
	
	//if(!$res)
	{
	//	echo mysql_error();
	//	die;
	}
	$opcode="SMS.a1agregator";
	$cmd="cmd=inc_credit_summa uid=$uid summa=$cr_round opcode=$opcode";
	$msg="Зачислены кредиты в сумме $cr_round .$opcode";
	if($cost>50)$msg=" Телефонный номер $user_id включен в вашу регистрационную запись и  подтвердил вашу регистрацию.";
	mysql_query("insert into ext_events (uid,event,d1,d2) values ('$uid','$cmd','$msg','')") or die(mysql_error());
	if($cost>50)
	{
		mysql_query("delete from phones where phone='$user_id'") or die(mysql_error());
		mysql_query("insert delayed into phones (uid,phone) values ('$uid','$user_id')") or die(mysql_error());
	}
	
	$login=mysql_select1("select login from tmp_users where id=$uid");
echo "smsid:$smsid\n";
echo "status:reply\n";
echo "content-type:text/plain\n";
echo "\n";
	echo "platezh prinyat na summu $cost rub, na login '$login' budet za4isleno $cr_round creditov";


    }
    else
    {
	echo 'newernyj format zaprosa';
    }
// date=kall&cost=22&operator_id=333&user_id=44&smsid=345&num=333
//wget http://tusovka.tomsk.ru:81/sms/sms.php?date=kall\&cost=22\&operator_id=333\&user_id=44\&smsid=345\&num=333\&msg=devtusa%2099
?>