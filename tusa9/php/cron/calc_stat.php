#!/usr/local/bin/php

<?
include "inc/db_conn.php";
check_conn();

//iterate_levelup_new_users

    $res=mysql_query("select id from tbl_users where stat_m_count>100 and stat_v_count>9 and stat_t_count>3600 and level=100 and UNIX_TIMESTAMP(reg_date)<(NOW()-86400)") or die(mysql_error());

    while(list($id)=mysql_fetch_row($res))
    {
	mysql_query("update tbl_users set level='200' where id='$id'") or die(mysql_error());
	mysql_query("insert into ext_events (event) values ('cmd=flush obj=tbl_users uid=$id')") or die(mysql_error().__FILE__.__LINE__);
    }
//iterate_bans
    mysql_query("delete from banned_ip where time_free<NOW() and UNIX_TIMESTAMP(time_free)!=0") or die (mysql_error());
    mysql_query("delete from banned_login where time_free<NOW() and UNIX_TIMESTAMP(time_free)!=0") or die (mysql_error());
//calc_statistic
    $out="";
    
    $out.="\nallmsg ".mysql_select1("select FORMAT(sum(stat_m_count),0) from tbl_users");
    $out.="\nallhours ".mysql_select1("select FORMAT(sum(stat_t_count)/3600,0) from tbl_users");
    $out.="\nallusers ".mysql_select1("select FORMAT(count(*),0) from tbl_users");
    $out.="\nallnicks ".mysql_select1("select FORMAT(count(*),0) from nicks");


//    list($)
    $out.="\nregtoday ".mysql_select1("select count(*) from tbl_users where reg_date>=date(now()) and make_stat='1'");
    $out.="\nregyestoday ".mysql_select1("select count(*) from tbl_users where reg_date>DATE(DATE_ADD(NOW(),INTERVAL -1 DAY)) and reg_date<=date(NOW()) and make_stat='1'");
    $out.="\nnewusers ".mysql_select1("select count(*) from tbl_users where level<200 and make_stat='1'");
    $out.="\nusers ".mysql_select1("select count(*) from tbl_users where level<300 and level>=200 and make_stat='1'");
    $out.="\nchatters ".mysql_select1("select count(*) from tbl_users where level<400 and level>=300 and make_stat='1'");
    $out.="\ntus ".mysql_select1("select count(*) from tbl_users where level<500 and level>=400 and make_stat='1'");
    $out.="\nvips ".mysql_select1("select count(*) from tbl_users where level<600 and level>=500 and make_stat='1'");
    $out.="\nadm ".mysql_select1("select count(*) from tbl_users where level>=600 and make_stat='1'");
    $out.="\ntopmess";
    $res=mysql_query("select last_nick_id,last_nick,FORMAT(stat_m_count,0),id from tbl_users where  make_stat='1' order by stat_m_count desc limit 50") or die(mysql_error());
    $rw=array();
    while($row=mysql_fetch_row($res))
    {
	array_push($rw,join(":",$row));
//	$out.=" ".join(":",$row);
    }
    $out.=" ".join(";",$rw);
    $out.="\ntophour";
    $res=mysql_query("select last_nick_id,last_nick,FORMAT(stat_t_count/3600,0),id from tbl_users  where make_stat='1' order by stat_t_count desc limit 50") or die(mysql_error());
    $rw=array();
    while($row=mysql_fetch_row($res))
    {
	array_push($rw,join(":",$row));
//	$out.=" ".;
    }
    $out.=" ".join(";",$rw);

		$f=fopen("/tmp/chat_stat","wb");
		fwrite($f,$out);
		fclose($f);



?>