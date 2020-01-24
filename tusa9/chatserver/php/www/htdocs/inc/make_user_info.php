<?
	function make_user_info($nid,$adm)
	{
		$out="";
		list($zid,$nick)=mysql_select1row("select uid,nick from nicks where id='$nid'");
		list($info,$reg_date,$city,$stat_last_date,$name,$hide_name, $last_nick,$gender,$setting_show_nicks,$birth_date,$hide_bdate,$setting_show_level,$level,$setting_show_credits,$credit_summa,$family_status,$hide_family_status)
		=mysql_select1row("select info, reg_date, city, stat_last_date, name, hide_name, last_nick,  gender, setting_show_nicks, birth_date, hide_bdate, setting_show_level, level, setting_show_credits, credit_summa, family_status, hide_family_status from tbl_users where id='$zid'");

		$out.= "<tr class=ileft><td colspan=2 align=center><b><big>$nick</big></b>\n";
	if(isset($_SESSION['level']) && $_SESSION['level']>=900)
	$out.= "<span style='margin-left:20px; position:relative;top:5px'><a href=\"javascript: opwin('/c2/admin/logininfo.php?id=$zid',550,500)\"><img src=\"/pics/quest.gif\" width=24 height=24 border=0 alt='Login info'></a></span>\n";
		
			if($_SESSION["level"]>=600)
		$out.= " </td></tr> \n"; 
		// fio
		if(!$hide_name || $adm)
		{
			$out.="<tr><td class=ileft>В реале&nbsp;</td> <td class=hname>$name";
			if($hide_name) $out.=" (скрыто)";
			$out.="</td></tr>\n";
		}

		// nicks	
		if($setting_show_nicks || $adm)
		{
			$res=mysql_query("select nick from nicks where uid='$zid'") or die(mysql_error());
			if(mysql_num_rows($res)>1)
			{
				$out.="<tr><td class=ileft>";
				if($gender==0)$out.="Известно ";
				else if($gender==1)$out.="Известен ";
				else if($gender==2)$out.="Известна ";
				$out.="также как &nbsp;</td><td class=infd class=nick>$last_nick ";

			 	while($r=mysql_fetch_row($res))
			 	{
		 			if($r[0]!=$last_nick) $out.=$r[0]." ";
			 	}
			 	if(!$setting_show_nicks) $out.=" (скрыто)";
			 	$out.="</td></tr>\n";
		 	}
		}
		// cities
		$out.="<tr><td class=ileft>Город&nbsp;</td> <td class=hname>$city</td></tr>\n";
		// gender
		$out.="<tr><td class=ileft>Пол&nbsp;</td> <td class=infd>";
		if($gender==0) $out.="Не известен";
		else if($gender==1) $out.="Мужской";
		else if($gender==2) $out.="Женский";
		$out.="</td></tr>\n";
		//date
		if(!$hide_bdate || $adm)
		{
   		  $out.="<tr><td class=ileft>";
		  if($gender==0) $out.="Родилось";
		  else if($gender==1) $out.="Родился";
		  else if($gender==2) $out.="Родилась";
		  $out.="&nbsp;</td>";
		  $out.="<td class=infd>".get_rusdate($birth_date)." ";
		  if($hide_bdate) $out.=" (скрыто)";
		  $out.="</td></tr>\n";
		}
		//level 
		if($setting_show_level || $adm)
		{
			$out.="<tr><td class=ileft>Уровень &nbsp;</td><td class=infd>";
			$out.=mysql_select1("select name from level_names where id='$level' and gender='$gender'");
			if(!$setting_show_level) $out.=" (скрыто)";
			$out.="</td></tr>\r\n";
		}
		if($setting_show_credits || $adm)
		{
			$out.="<tr><td class=ileft>Кредиты &nbsp;</td><td class=infd>$credit_summa";
			if(!$setting_show_credits) $out.=" (скрыто)";
			$out.="</td></tr>\r\n";
		}
		if((!$hide_family_status || $adm)&&strlen(trim($family_status))>0)
		{
			$out.="<tr><td class=ileft>Семейное положение &nbsp;</td><td class=infd>$family_status";
			if($hide_family_status) $out.=" (скрыто)";
			$out.="</td></tr>\r\n";
		}
		$out.="<tr><td class=ileft>Дата регистрации&nbsp;</td><td class=infd>".get_rusdate($reg_date)."</td></tr>\r\n";
		$out.="<tr><td class=ileft>Последний заход в чат&nbsp;</td><td class=infd>".get_rusdate($stat_last_date)."</td></tr>\r\n";
		// info
		$out.="<tr><td class=ileft>Немного о себе&nbsp;</td> <td class=infd>$info</td></tr>\n";

		return $out;
	}
?>