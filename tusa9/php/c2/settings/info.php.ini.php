<?
     if (isset($_REQUEST['DATA1']))
     {
//       if(isset($arg_selother))
//       $city=mysql_escape_string($arg_selother);
//       else $city=mysql_escape_string(mysql_select1("select title from cities where citi_id='$arg_sel'"));
       $city=isset($arg_city)?mysql_escape_string($arg_city):"";
       $name=isset($arg_name)?mysql_escape_string($arg_name):"";
       $hide_name=isset($arg_hide_name)?$arg_hide_name=="on":false;
       $hide_bd=isset($arg_hide_bd)?$arg_hide_bd=="on":false;
       $hide_sel=isset($arg_hide_sel)?$arg_hide_sel=="on":false;
       $info=isset($arg_info)?mysql_escape_string($arg_info):"";
       $gn=isset($arg_gn)?mysql_escape_string($arg_gn):"";
       $bdate="$arg_by-$arg_bm-$arg_bd";
       
//       $gn=$arg_gn;
   
       $sql=sprintf("update tbl_users set city='$city',
            birth_date='$bdate',
            name='$name',
            hide_name='%d',
            hide_bdate='%d',
            info='$info',
            gender='$gn'
            where id='$uid'",$hide_name,$hide_bd);
       mysql_query($sql) or die(mysql_error().__FILE__.__LINE__);
       $error='Изменения внесены';

     }
     list($gn,$bd,$bm,$by,$city,$name,$hide_name,$hide_bdate,$info)=mysql_select1row("select gender,day(birth_date),month(birth_date),year(birth_date),city,name,hide_name,hide_bdate,info from tbl_users where id='$uid'");
?>