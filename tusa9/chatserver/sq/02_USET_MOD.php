<?
		$db = mysql_connect('localhost:/tmp/mysql.sock', 'root', '');
		mysql_select_db('chat') or die ('Can"t select database : ' . mysql_error());
#	        mysql_query('set names cp1251');

		$sql="select refid,lpp,show_nicks,show_level,neye,n_color_pack,contact_mode,contact_options,notes_msg_per_page,notes_save_copy,
		    notes_sort,notes_sort_desc,poweshen,last_nick_id,last_nick,last_channel,last_status_id,setting_autologin,setting_autochange,
		    setting_show_eye,setting_show_hints,setting_show_stat,setting_invite_sound,setting_full_buttons,ul_mode_hide_female,
		    ul_mode_hide_male,ul_mode_contacts_only,show_credits,primary_photo,level,vote_balls,db_privileges,last_www_channel,unread_notes	 from user_sets";

		//echo "<p>$sql</p>";
		$result=mysql_query($sql);
		echo mysql_error();
    		while ($row=mysql_fetch_row($result)){
#		$row=array();
#		    for($i=0;$i<count($rw);$i++)
#		    {
#			$row[i]=mysql_escape_string($rw[i]);
#		    }
		    mysql_query("update tbl_users set  
			 setting_lpp='$row[1]',
			 setting_show_nicks='$row[2]',
			 setting_show_level='$row[3]',
			 setting_neye='$row[4]',
			 setting_n_color_pack='$row[5]',
			 contact_mode='$row[6]',
			 contact_options='$row[7]',
			 notes_msg_per_page='$row[8]',
			 notes_save_copy='$row[9]',
			 notes_sort='$row[10]',
			 notes_sort_desc='$row[11]',
			 poweshen='$row[12]',
			 last_nick_id='$row[13]',
			 last_nick='$row[14]',
			 last_channel='$row[15]',
			 last_status_id='$row[16]',
			 setting_autologin='$row[17]',
			 setting_autochange='$row[18]',
			 setting_show_eye='$row[19]',
			 setting_show_hints='$row[20]',
			 setting_show_stat='$row[21]',
			 setting_invite_sound='$row[22]',
			 setting_full_buttons='$row[23]',
			 ul_mode_hide_female='$row[24]',
			 ul_mode_hide_male='$row[25]',
			 ul_mode_contacts_only='$row[26]',
			 setting_show_credits='$row[27]',
			 primary_photo='$row[28]',
			 level='$row[29]',
			 vote_balls='$row[30]',
			 db_privileges='$row[31]',
			 last_www_channel='$row[32]',
			 unread_notes	='$row[33]'	    
			    where id=	'$row[0]'
			    ");
		echo mysql_error();
		}	
?>