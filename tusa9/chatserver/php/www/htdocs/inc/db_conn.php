<?
function check_conn()
{
	{
		$db = mysql_connect('localhost:/tmp/mysql.sock', 'root','');
		mysql_select_db('chat') or die ('Can"t select database : ' . mysql_error());
		mysql_query("set charset cp1251") or die(mysql_error());
	}
    	
}
function mysql_select1($sql)	
{
	$r=mysql_query($sql) or die(mysql_error().$sql);
	if(!$r){
		echo (mysql_error() . "SQL: $sql");
		return '';
	}
	$res = mysql_fetch_array($r);
	if(count($res)) return $res[0];
//	return '';
}
function mysql_select1row($sql)	
{
	$r=mysql_query($sql) or die(mysql_error().$sql);
	if(!$r){
		echo (mysql_error() . "SQL: $sql");
		return array();
	}
	$res = mysql_fetch_array($r);
	return $res;
}
function mysql_select1column($sql)	
{
	$r=mysql_query($sql) or die(mysql_error().$sql);
	if(!$r){
		echo (mysql_error() . "SQL: $sql");
		return array();
	}
	$ret=array();
	while($res = mysql_fetch_array($r))
	{
		array_push($ret,$res[0]);
	}
	return $ret;
}
function MES($str)
{
	return mysql_escape_string($str);
}

function sel_options($sql,$def)
{
		$result=mysql_query($sql) or die(mysql_error().$sql);
    		while ($row=mysql_fetch_row($result)){
		    if(count($row)==2)
		    {
		    	$cid=$row[0];
			$cname=$row[1];
			if($def!=$cid)
		    	echo "<OPTION VALUE='$cid'>$cname\n";
			else
		    	echo "<OPTION VALUE='$cid' SELECTED>$cname\n";
		    }
		}	

}
?>
