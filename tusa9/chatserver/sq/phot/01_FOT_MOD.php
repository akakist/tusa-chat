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
function old_cache_dir($name, $uid)
{

    if ($uid<100)
    {
        return sprintf("/var/chat/$name/0/%02d",$uid);
    }
    else if ($uid<10000)
    {
    	$u1=$uid/100;
	$u2=$uid%100;
        return sprintf ("/var/chat/$name/1/%02d/%02d",$u1,$u2); 
    }
    else if ($uid<1000000)
    {
        $u1=round($uid/10000);
        $u2=round(($uid-($u1*10000))/100);
        $u3=$uid%100;
	$uid/=100;
	$u2=$uid%100;
	$uid/=100;
	$u1=$uid%100;
        return  sprintf("/var/chat/$name/2/%02d/%02d/%02d",$u1,$u2,$u3); 
    }
    else{
    	echo "Error limit";
    }
    return "";

}
function new_cache_dir($name, $uid)
{
	$uid/=100;
    if ($uid<100)
    {
        return sprintf("/var/chat/$name/0/%02d",$uid);
    }
    else if ($uid<10000)
    {
    	$u1=$uid/100;
	$u2=$uid%100;
        return sprintf ("/var/chat/$name/1/%02d/%02d",$u1,$u2); 
    }
    else if ($uid<1000000)
    {
        $u1=round($uid/10000);
        $u2=round(($uid-($u1*10000))/100);
        $u3=$uid%100;
	$uid/=100;
	$u2=$uid%100;
	$uid/=100;
	$u1=$uid%100;
        return  sprintf("/var/chat/$name/2/%02d/%02d/%02d",$u1,$u2,$u3); 
    }
    else{
    	echo "Error limit";
    }
    return "";

}

function old_foto_pn($uid,$pid, $ext)
{
    $pn=old_cache_dir("user",$uid)."/photos/$pid.$ext";
    return $pn;
}
function new_foto_pn($pid, $ext)
{
	$d=new_cache_dir("photos",$pid);
	if(!file_exists($d)){
		mkdir($d,0777,true);
	}	
    	$pn=$d."/$pid.$ext";
    return $pn;
}


		$db = mysql_connect('localhost:/tmp/mysql.sock', 'root', '');
		mysql_select_db('chat') or die ('Can"t select database : ' . mysql_error());
#	        mysql_query('set names cp1251');
/*
 `ID` int(10) unsigned NOT NULL auto_increment,
   `filename` text NOT NULL,
  `orig_filename` text NOT NULL,
  `descr` text NOT NULL,
  `sx` int(20) default NULL,
  `sy` int(20) default NULL,
  `uid` int(20) unsigned NOT NULL default '0',
  `size` int(10) NOT NULL default '0',
  `ext` text NOT NULL,
  `rating` blob NOT NULL,
  `rating_result` int(11) NOT NULL default '0',
  `add_date` datetime NOT NULL default '2008-01-01 00:00:00',
  `moderated` char(1) NOT NULL default '0',

*/
		$result=mysql_query("delete from phs");
		echo mysql_error();
		mysql_query("DROP TABLE IF EXISTS `phs`");
		echo mysql_error();
		mysql_query("CREATE TABLE `phs` (
  `ID` int(10) unsigned NOT NULL auto_increment,
  `filename` text NOT NULL,
  `orig_filename` text NOT NULL,
  `descr` text NOT NULL,
  `sx` int(20) default NULL,
  `sy` int(20) default NULL,
  `uid` int(20) unsigned NOT NULL default '0',
  `size` int(10) NOT NULL default '0',
  `ext` text NOT NULL,
  `rating` blob NOT NULL,
  `rating_result` int(11) NOT NULL default '0',
  `add_date` datetime NOT NULL default '2008-01-01 00:00:00',
  `moderated` char(1) NOT NULL default '0',
  PRIMARY KEY  (`ID`),
  KEY `ID` (`ID`),
  KEY `uidi` (`uid`)
) ENGINE=MyISAM DEFAULT CHARSET=cp1251;");
		echo mysql_error();

		$sql="select id,filename,orig_filename,descr,uid,size,ext from photos";

		$result=mysql_query($sql);
		echo mysql_error();
		$i=0;
    		while ($row=mysql_fetch_row($result)){
			$i++;
			if($i%1000==0)
			{
				echo "$i\n";
			}
			$id=$row[0];
			$filename=$row[1];
			$orig_filename=$row[2];
			$descr=$row[3];
			$uid=$row[4];
			$size=$row[5];
			$ext=$row[6];
		    mysql_query("insert into phs (filename,orig_filename,descr,uid,size,ext) values (
			    '".mysql_escape_string($filename)."',
			    '".mysql_escape_string($orig_filename)."',
			    '".mysql_escape_string($descr)."',
			    '".mysql_escape_string($uid)."',
			    '".mysql_escape_string($size)."',
			    '".mysql_escape_string($ext)."')");
	    		echo mysql_error();
			$newid=select_1("select LAST_INSERT_ID()");
			$oldpn=old_foto_pn($uid,$id,$ext);
			$newpn=new_foto_pn($newid,$ext);
			if(!link($oldpn,$newpn))
			{
				echo "error link $oldpn $newpn\n";
			}
			
		}	
?>