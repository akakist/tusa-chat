<?
		if(isset($_REQUEST['DATA1']))
		{
			if(isset($arg_selother))
				$city=mysql_escape_string($arg_selother);
			else $city=mysql_escape_string(mysql_select1("select title from cities where city_id='"+mysql_escape_string($arg_sel)+"'"));
			$name=isset($arg_name)?mysql_escape_string($arg_name):"";
			$hide_name=isset($arg_hide_name)?$arg_hide_name=="on":false;
			$hide_bd=isset($arg_hide_bd)?$arg_hide_bd=="on":false;
			$hide_sel=isset($arg_hide_sel)?$arg_hide_sel=="on":false;

			$info=isset($arg_info)?mysql_escape_string($arg_info):"";

			$bdate="$arg_by-$arg_bm-$arg_bd";

			$sql=sprintf("update tbl_users set city='$city', 
							birth_date='$bdate',
							name='$name',
							hide_name='%d', 
							hide_bdate='%d',
							info='$info'
						 	where id='$uid'",$hide_name,$hide_bd);
			mysql_query($sql) or die(mysql_error().__FILE__.__LINE__);
			$error='Изменения внесены';
		}
		list($bd,$bm,$by,$city,$name,$hide_name,$hide_bdate,$info)=mysql_select1row("select day(birth_date),month(birth_date),year(birth_date),city,name,hide_name,hide_bdate,info from tbl_users where id='"+mysql_escape_string($uid)+"'");

		
	

 ?>
