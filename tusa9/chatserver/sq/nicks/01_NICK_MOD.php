<?

function select_1($sql)	
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

		$db = mysql_connect('localhost:/tmp/mysql.sock', 'root', '');
		mysql_select_db('chat') or die ('Can"t select database : ' . mysql_error());
#	        mysql_query('set names cp1251');

		$sql="select id,uid,nick,str_nick,banned,bby,last_usage_date from nicks";

		$result=mysql_query($sql);
		echo mysql_error();
    		while ($row=mysql_fetch_row($result)){
				$id=$row[0];
				$uid=$row[1];
		    mysql_query("insert into nn (uid,nick,str_nick,banned,bby,last_usage_date) values (
			    '".mysql_escape_string($row[1])."',
			    '".mysql_escape_string($row[2])."',
			    '".mysql_escape_string($row[3])."',
			    '".mysql_escape_string($row[4])."',
			    '".mysql_escape_string($row[5])."',
			    '".mysql_escape_string($row[6])."')");
	    		echo mysql_error();
			$newid=select_1("select LAST_INSERT_ID()");
			echo mysql_error();
			mysql_query("update Forum_messages set id=$newid where id=$id and uid=$uid");
			echo mysql_error();
			mysql_query("update Forum_themes set id=$newid where id=$id and uid=$uid");echo mysql_error();
			mysql_query("update notes set from_nick_id=$newid where from_nick_id=$id and owner_uid=$uid");echo mysql_error();
			mysql_query("update notes set to_nick_id=$newid where to_nick_id=$id and owner_uid=$uid");echo mysql_error();
			

		}	
?>