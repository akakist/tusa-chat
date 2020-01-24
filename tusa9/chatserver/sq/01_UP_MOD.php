<?
		$db = mysql_connect('localhost:/tmp/mysql.sock', 'root', '');
		mysql_select_db('chat') or die ('Can"t select database : ' . mysql_error());
#	        mysql_query('set names cp1251');

		$sql="select refid,icq,city,info,homepage,tel,b_day,b_mon,b_year,fname,lname,email,reg_date,login,pass,upperlogin,gender,hide_fname,hide_lname,hide_bdate,
		    hide_tel,hide_icq,hide_email,bought_invisibility,family_status,hide_family_status	 from user_profiles";

/*
alter table users add column  `icq` text;
alter table users add column   `city` text;
alter table users add column   `info` text;
alter table users add column   `homepage` text;
alter table users add column   `tel` text;
alter table users add column   `b_day` varchar(10) NOT NULL default '';
alter table users add column   `b_mon` int(3) NOT NULL default '0';
alter table users add column   `b_year` varchar(4) NOT NULL default '1980';
alter table users add column   `fname` text;
alter table users add column   `lname` text;
alter table users add column   `email` text;
alter table users add column   `reg_date` datetime default NULL;
alter table users add column   `login` varchar(18) NOT NULL default '';
alter table users add column   `pass` text;
alter table users add column   `upperlogin` varchar(20) NOT NULL default '';
alter table users add column   `gender` char(1) NOT NULL default '0';
alter table users add column   `has_clan` char(1) NOT NULL default '0';
alter table users add column   `hide_fname` char(1) NOT NULL default '0';
alter table users add column   `hide_lname` char(1) NOT NULL default '0';
alter table users add column   `hide_bdate` char(1) NOT NULL default '0';
alter table users add column   `hide_tel` char(1) NOT NULL default '0';
alter table users add column   `hide_icq` char(1) NOT NULL default '0';
alter table users add column   `hide_email` char(1) NOT NULL default '0';
alter table users add column   `bought_invisibility` double NOT NULL default '0';
alter table users add column   `bought_quota` int(10) NOT NULL default '0';
alter table users add column   `family_status` text NOT NULL;
alter table users add column   `hide_family_status` char(1) NOT NULL default '0';
alter table users add   KEY (`login`);
alter table users add   KEY (`reg_date`);

*/
		//echo "<p>$sql</p>";
		$result=mysql_query($sql);
		echo mysql_error();
    		while ($row=mysql_fetch_row($result)){
	//#	$row=array();
	//#	    for($i=0;$i<count($rw);$i++)
	//#	    {
	//#		$row[i]=mysql_escape_string($rw[i]);
	//#	    }
		    mysql_query("update tbl_users set  
			    icq=	'".mysql_escape_string($row[1])."',
			    city=	'".mysql_escape_string($row[2])."',
			    info=	'".mysql_escape_string($row[3])."',
			    homepage=	'".mysql_escape_string($row[4])."',
			    tel=	'".mysql_escape_string($row[5])."',
			    b_day=	'".mysql_escape_string($row[6])."',
			    b_mon=	'".mysql_escape_string($row[7])."',
			    b_year=	'".mysql_escape_string($row[8])."',
			    fname=	'".mysql_escape_string($row[9])."',
			    lname=	'".mysql_escape_string($row[10])."',
			    email=	'".mysql_escape_string($row[11])."',
			    reg_date=	'".mysql_escape_string($row[12])."',
			    login=	'".mysql_escape_string($row[13])."',
			    pass=	'".mysql_escape_string($row[14])."',
			    upperlogin=	'".mysql_escape_string($row[15])."',
			    gender=	'".mysql_escape_string($row[16])."',
			    hide_fname=	'".mysql_escape_string($row[17])."',
			    hide_lname=	'".mysql_escape_string($row[18])."',
			    hide_bdate=	'".mysql_escape_string($row[19])."',
			    hide_tel=	'".mysql_escape_string($row[20])."',
			    hide_icq=	'".mysql_escape_string($row[21])."',
			    hide_email=	'".mysql_escape_string($row[22])."',
			    bought_invisibility=
					'".mysql_escape_string($row[23])."',
			    family_status=
					'".mysql_escape_string($row[24])."',
			    hide_family_status=
					'".mysql_escape_string($row[25])."'
			    where id=	'".mysql_escape_string($row[0])."'
			    ");
			    		echo mysql_error();

		}	
?>