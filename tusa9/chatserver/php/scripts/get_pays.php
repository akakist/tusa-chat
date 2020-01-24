#!/usr/local/bin/php
 <?php

		$db = mysql_connect('localhost:/tmp/mysql.sock', 'root', '');
		mysql_select_db('chat') or die ('Can"t select database : ' . mysql_error());
	        mysql_query('set charset cp1251');

    
/*    
   // открыть файл для чтения
    $temp = tmpfile();
		fwrite($temp,"AccountNr;SomeText\n");

	    $sql="select id,login from tbl_users order by id";
	    $result=mysql_query($sql);
	    if(!$result)
	    {
		echo mysql_error();
		return false;
	    }
    	    while ($row=mysql_fetch_row($result)){
		{
		    $uid=$row[0];
		    $login=$row[1];
		    fwrite($temp,"$uid;$login\n");
		}
	    }	
	    mysql_free_result($result);
	    
   fseek($temp, 0);
  
*/
   // установка соединения
   $conn_id = ftp_connect("komstar.tomsk.ru",21,30);

   // вход с именем пользователя и паролем
   $login_result = ftp_login($conn_id, "tusovka","fjgr78t4");
    if(!$login_result)
    {
	echo "ftp login error\n";
    }
    $ls=array();
    $ls=ftp_nlist ( $conn_id , "/payment");
    if(!$ls)
    {
	echo "nlist err\n";
	die;
    }
    #var_dump($ls);
    for($i=0;$i<count($ls);$i++)
    {
#	echo $ls[$i]."\n";
	$fn=$ls[$i];
	$gres=ftp_get ( $conn_id , "/tmp/$fn" , "/payment/$fn", FTP_ASCII);
	$file=fopen("/tmp/$fn",'r');
	$content=fread($file,filesize($fn));
	fclose($file);
//	unlink()
#	echo $content."\n";
	$rows=split("[\r\n]",$content);
	foreach($rows as $row)
	{
	    $pair=split("[\;]",$row);
	    list($PaymentDate,$AccountNr,$MachineMark,$TransferSum)=split("[\;]",$row); 
	    $PaymentDate=preg_replace('[\.]','-',$PaymentDate);
	    if('PaymentDate'==$PaymentDate) continue;
#	    echo $PaymentDate;
#	    var_dump($pair);
#	    echo count($pair)."\n";
	    if(count($pair)==4)
	    {
		$creds=$TransferSum*10000000000;
		mysql_query("insert into komstar_payments (processed,uid,dt,ext_date,cost,MachineMark,credits) values ('0','$AccountNr',NOW(),'$PaymentDate','$TransferSum','$MachineMark','$creds')");
		echo mysql_error();

	$cmd="inc_credit_summa $AccountNr $creds";
	$opcode="komstar";
	$msg="Зачислены кредиты в сумме $creds .$opcode";
	mysql_query("insert into ext_events (uid,event,d1,d2) values ('$uid','$cmd','$opcode','$msg')");
		
#		echo $pair[1]." ".$pair[3]."\n";
		
	    }
	}
	ftp_delete($conn_id,"/payment/$fn");
	
	
    }
    
/*   // попытка закачивания файла
   if (ftp_fput($conn_id, "/recepients/tusovka.csv.1", $temp, FTP_ASCII)) {
       echo "Загружен файл $file\n";
	ftp_delete($conn_id,"/recepients/tusovka.csv");
       ftp_rename($conn_id,"/recepients/tusovka.csv.1","/recepients/tusovka.csv");
   } else {
       echo "Проблема закачивания $file\n";
   }

   // close the connection and the file handler
   */
   ftp_close($conn_id);
//   fclose($temp);
//  ftp://tusovka:fjgr78t4@komstar.tomsk.ru
   ?>
