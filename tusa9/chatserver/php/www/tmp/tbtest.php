<?
		$db = mysql_connect('localhost:/tmp/mysql.sock', 'root','');
		mysql_select_db('t') or die ('Can"t select database : ' . mysql_error());
		for($i=0;$i<1000000000;$i++)
		{	
			$l=md5(rand());
			mysql_query("insert into a (a) values ('$l')");
		}

?>