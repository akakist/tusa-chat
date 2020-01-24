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

	mysql_query("DROP TABLE IF EXISTS `user_status_new`");
mysql_query("CREATE TABLE `user_status_new` (
  `ID` int(10) unsigned NOT NULL auto_increment,
  `uid` int(10) unsigned NOT NULL default '0',
  `name` text,
  `pic` int(11) default NULL,
  `disable_invite` char(1) NOT NULL default '0',
  `uniq` char(1) NOT NULL default '0',
  primary KEY (`ID`),
  KEY `uidi` (`uid`)
) ENGINE=MyISAM DEFAULT CHARSET=cp1251");

		$sql="select id,uid,name,pic,disable_invite from user_status";

		$result=mysql_query($sql);
		echo mysql_error();
    		while ($row=mysql_fetch_row($result)){
				$id=$row[0];
				$uid=$row[1];
		    mysql_query("insert into user_status_new (uid,name,pic,disable_invite) values (
			    '".mysql_escape_string($row[1])."',
			    '".mysql_escape_string($row[2])."',
			    '".mysql_escape_string($row[3])."',
			    '".mysql_escape_string($row[4])."')");
	    		echo mysql_error();
		}	
?>