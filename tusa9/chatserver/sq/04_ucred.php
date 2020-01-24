<?
		$db = mysql_connect('localhost:/tmp/mysql.sock', 'root', '');
		mysql_select_db('chat') or die ('Can"t select database : ' . mysql_error());
#	        mysql_query('set names cp1251');

		$sql="select refid, summa from user_credits order by refid";

/*


*/
		//echo "<p>$sql</p>";
		$result=mysql_query($sql);
		echo mysql_error();
    		while ($rw=mysql_fetch_row($result)){
//		$row=array();
//		    for($i=0;$i<count($rw);$i++)
//		    {
//			$row[i]=mysql_escape_string($rw[i]);
//		    }
		    mysql_query("update tbl_users set  
				credit_summa='$rw[1]'
			    where id=	'$rw[0]'
			    ");
		echo mysql_error();
		}	
?>