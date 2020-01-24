<?
	include 'inc/db_conn.php';
	include "inc/conf.php";
	include 'inc/cache_dir.php';
	check_conn();
	
	$result=mysql_query('select id,gender from tbl_users order by id');
	while ($r=mysql_fetch_row($result))
	{
		$id=$r[0];
		if($r[1]=='2')
		{
					$thumb_big="/pics/noimage-female-big.jpg";
					$thumb_small="/pics/noimage-female-small.jpg";
		}
		else 
		{
					$thumb_big="/pics/noimage-male-big.jpg";
					$thumb_small="/pics/noimage-male-small.jpg";
		}
		mysql_query("update tbl_users set foto_thumb_big='$thumb_big', foto_thumb_small='$thumb_small',foto_big='$thumb_big'  where id='$id'") or die(mysql_error());
		if($r[0]%1000==0) echo $r[0]."\n";
		
		$n=mysql_select1("select count(*) from photos where uid='$id'");

		if($n>0)
		{
			$pid=mysql_select1("select min(id) from photos where uid='$id'")or die(mysql_error());
			$big=thumb_big_url($pid,false);
			$small=thumb_small_url($pid,false);
//#			echo "$big $small\n";
			mysql_query("update tbl_users set foto_count='$n',foto_thumb_big='$big', foto_thumb_small='$small', foto_big='$big' where id='$id'")or die(mysql_error());
			
		}
	}
	
	$result=mysql_query("select id,uid from photos");
	while($r=mysql_fetch_row($result))
	{
		$pid=$r[0];
		$uid=$r[1];
						$BU=thumb_big_url($pid,false);
						$SU=thumb_small_url($pid,false);
						$IR=image_resized_url($pid,false);
						mysql_query("update photos set url_thumb_small='$SU', url_thumb_big='$BU', url_scaled='$BU' ,url_host='$MYHOST' where id='$pid'")or die(mysql_error());
	
		/*
		 url_thumb_small | url_thumb_big | url_scaled | url_host |
		 
		*/
	}
?>