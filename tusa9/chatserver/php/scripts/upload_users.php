#!/usr/local/bin/php
 <?php

		$db = mysql_connect('localhost:/tmp/mysql.sock', 'root', '');
		mysql_select_db('chat') or die ('Can"t select database : ' . mysql_error());
	        mysql_query('set charset cp1251');

    
    
   // ������� ���� ��� ������
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
  

   // ��������� ����������
   $conn_id = ftp_connect("komstar.tomsk.ru",21,30);

   // ���� � ������ ������������ � �������
   $login_result = ftp_login($conn_id, "tusovka","fjgr78t4");
    if(!$login_result)
    {
	echo "ftp login error\n";
    }

   // ������� ����������� �����
   if (ftp_fput($conn_id, "/recepients/tusovka.csv.1", $temp, FTP_ASCII)) {
       echo "�������� ���� $file\n";
	ftp_delete($conn_id,"/recepients/tusovka.csv");
       ftp_rename($conn_id,"/recepients/tusovka.csv.1","/recepients/tusovka.csv");
   } else {
       echo "�������� ����������� $file\n";
   }

   // close the connection and the file handler
   ftp_close($conn_id);
   fclose($temp);
//  ftp://tusovka:fjgr78t4@komstar.tomsk.ru
   ?>
