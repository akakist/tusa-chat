<?
		$db = mysql_connect('localhost:/tmp/mysql.sock', 'root', '');
		mysql_select_db('chat') or die ('Can"t select database : ' . mysql_error());
#	        mysql_query('set names cp1251');

		$sql="select refid, last_date,last_ip,v_count,m_count,t_count,kick_count,kicked_count from user_stats";

/*
alter table users add column   `stat_last_date` datetime NOT NULL default '2006-01-01 00:00:00';
alter table users add column   `stat_last_ip` text NOT NULL;
alter table users add column   `stat_v_count` int(11) NOT NULL default '0';
alter table users add column   `stat_m_count` int(10) NOT NULL default '0';
alter table users add column   `stat_t_count` int(10) NOT NULL default '0';
alter table users add column   `kick_count` int(10) unsigned NOT NULL default '0';
alter table users add column   `kicked_count` int(10) unsigned NOT NULL default '0';


*/
		//echo "<p>$sql</p>";
		$result=mysql_query($sql);
		echo mysql_error();
    		while ($rw=mysql_fetch_row($result)){
//		$row=array();
//		    for($i=0;$i<count($rw);$i++)
//		    {
//			$rw[i]=mysql_escape_string($rw[i]);
//		    }
		    mysql_query("update tbl_users set  
				stat_last_date='$rw[1]',
				stat_last_ip='$rw[2]',
				stat_v_count='$rw[3]',
				stat_m_count='$rw[4]',
				stat_t_count='$rw[5]',
				kick_count  ='$rw[6]',
				kicked_count='$rw[7]'
			    where id='$rw[0]'
			    ");
		echo mysql_error();
		}	
?>