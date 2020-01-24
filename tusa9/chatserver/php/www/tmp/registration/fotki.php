<?
	session_start();
        import_request_variables("gp", "arg_");
	include "inc/db_conn.php";
	include 'inc/conf.php';
	include 'inc/build_thumbnail.php';
	include 'inc/cache_dir.php';
	check_conn();
     if(isset($_SESSION['login']))
     {
     	$login=$_SESSION['login'];
	$uid=$_SESSION['uid'];
     }
    
     if(!isset($login))
     {
     	header("Location: /");
	die;
     }
  ?>
<html>
<head>
  <meta http-equiv="PRAGMA" content="no-cache">
  <meta http-equiv="Content-Type" content="text/html; charset=windows-1251">

  <title>Чат "Тусовка"</title>
  <link rel="stylesheet" type="text/css" href="/css/main.css">
    <link rel="stylesheet" href="/css/fancy.css" type="text/css">
<!--[if lte IE 6]><style type="text/css" media="screen">/* <![CDATA[ */ @import url(/css/fancy.ie.css); /* ]]> */</style><![endif]-->

	<script type="text/javascript" src="/js/jquery.pack.js"></script>
      
  <script language="javascript" src="/css/mmove.js" type="text/javascript"></script>
   <script language="javascript" src="/js/fancybox.js"></script>
</head>
<script>

function move_to_trash(pid)
{
	document.frem.remf.value+="_"+pid;
	//document.write(document.frem.remf.value+'<br>');
	document.getElementById('trash').innerHTML+=document.getElementById('ph'+pid).innerHTML;
	document.getElementById('ph'+pid).innerHTML="";
	$("#trash").show();
	return false;
}
function on_remove()
{
	return true;
}
function on_subm()
{
	return false;
}
				var country_id=0;
				var region_id=0;
				var city_id=0;
/*				    function select_region(f) {  
				          n = f.sel.selectedIndex;  
					  country_id=f.sel.options[n].value;
					  if(n){
					  	$("#location").load("/registration/get_rg.php?c="+country_id);
					  }
				    }  
				    function select_city(f) {  
				          n = f.sel.selectedIndex;  
					  region_id=f.sel.options[n].value;
					  if(n){
					  	$("#location").load("/registration/get_city.php?r="+region_id);
					  }
				    }  
				    function do_another()
				    {
				    	$("#location").html('<input type="text" maxlength="16" size="20" name="selother" value="">');
					$("#another").html('');
				    }*/
						    

</script>
			 <script>
			 	$("a[tb=1]").fancybox();
			 </script>
<body>

  <table border="0" width="100%" cellspacing="0" cellpadding="0">
  <?
    include 'diz/head_row.php';
  ?>

    <tr height="5">
      <td colspan="5"></td>
    </tr>

    <tr valign="top">
	<?
	    include 'diz/left_col.php';
    	?>

      <td></td>

      <td>
      <!--START-->
	
	<div align=center class=border style='margin-bottom: 20px'><b>Регистрация</b></div>
	<?
		function make_image($im,$id,$type, $ismain)
		{
			global $VAR_DIR;
			if($type=='tb')$url=thumb_big_url($id,$ismain);
			else if($type=='ts')$url=thumb_small_url($id,$ismain);
			else if($type=='rs')$url=image_resized_url($id,$ismain);
			$pi=pathinfo($VAR_DIR.$url);
			if(!@stat($pi["dirname"]))
			{
				if(!mkdir($pi["dirname"],0777,true))
				{
					$error="cannot mkdir ".$pi["dirname"];
					echo $error;
				}
			}	
			if($type=='ts')$dst=build_thumbnail($im,85,110);
			else if($type=='tb')$dst=build_thumbnail($im,400,550);
			else if($type=='rs')$dst=resize_image($im,800,600);
			if(!imagejpeg($dst,$VAR_DIR.$url))
			{
			 $error="error write $path";
			 echo $error;
			} 
			if(!isset($error))
			{
				
				if($ismain)
				{
					
				}
			}
			
			 
		}
		if(isset($arg_remf))
		{
			$r=split("_",$arg_remf);
			$rr=array();
			for($i=0;$i<count($r);$i++)
			{
				if(strlen($r[$i]))array_push($rr,$r[$i]);
			}
			$j=join(",",$rr);
			
			$res=mysql_query("select url_thumb_small,url_thumb_big,url_scaled from photos where uid='$uid' and id in($j)") or die(mysql_error());
			while($row=mysql_fetch_row($res))
			{
				foreach($row as $p)
				{
				$pn=$VAR_DIR.$p;
				unlink($pn);
				}
			}
			
			$sql="delete from photos where uid='$uid' and id in ($j)";
			mysql_query($sql) or die(mysql_error());
			
		}
		if(isset($arg_MAIN))
		{
				$ismain=false;
				if(isset($arg_ismain))
				{
					if($arg_ismain=='on')$ismain=true;
				}
				$name=$_FILES['foto']['name'];
				$tmpname=$_FILES['foto']['tmp_name'];
				if($im=imagecreatefromjpeg($tmpname)) 
				{
					if($ismain)
					{
						make_image($im,$uid,'ts',true);
						make_image($im,$uid,'tb',true);
						make_image($im,$uid,'rs',true);
						$BU=thumb_big_url($uid,true);
						$SU=thumb_small_url($uid,true);
						$IR=image_resized_url($uid,true);
						mysql_query("update tbl_users set foto_big='$IR', foto_thumb_small='$SU', foto_thumb_big='$BU' where id='$uid'") or die(mysql_error());
						$np=mysql_select1("select count(*) from photos where uid='$uid'");
						mysql_query("update tbl_users set foto_count='$np' where id='$uid'") or die(mysql_error());
					}
					else
					{
						mysql_query("insert into photos (uid) values($uid)") or die(mysql_error());
						$pid=mysql_select1("select last_insert_id()");
						make_image($im,$pid,'ts',false);
						make_image($im,$pid,'tb',false);
						make_image($im,$pid,'rs',false);
						$BU=thumb_big_url($pid,false);
						$SU=thumb_small_url($pid,false);
						$IR=image_resized_url($pid,false);
						mysql_query("update photos set url_thumb_small='$SU', url_thumb_big='$BU', url_scaled='$IR' ,url_host='$MYHOST' where id='$pid'") or die(mysql_error());
						$np=mysql_select1("select count(*) from photos where uid='$uid'");
						mysql_query("update tbl_users set foto_count='$np' where id='$uid'") or die(mysql_error());
						
					}
				}
		
		}
		if(isset($arg_DATA1))
		{
			
			$name=$_FILES['foto']['name'];
			$tmpname=$_FILES['foto']['tmp_name'];
			mysql_query("insert into photos (uid) values($uid)") or die(mysql_error());
			$pid=mysql_select1("select last_insert_id()");

			if($im=imagecreatefromjpeg($tmpname)) 
			{
				make_image($im,$pid,'ts',true);
				make_image($im,$pid,'tb',true);
				make_image($im,$pid,'rs',true);
			}
			else
			{
				mysql_query("delete from photos where id='$pid'") or die(mysql_error());
				$error="Ошибка загрузки изображения";
			}
			$np=mysql_select1("select count(*) from photos where uid='$uid'");
			mysql_query("update tbl_users set foto_count='$np' where id='$uid'") or die(mysql_error());
		}
		
		list($main_foto_thumb_small,$main_foto_big)=mysql_select1row("select foto_thumb_small,foto_big from tbl_users where id='$uid'");
//		echo $main_foto_thumb_small,$main_foto_big;
	?>
	<div id=regform>
	<!--form method="post" name="form1"  enctype="multipart/form-data"-->
               <fieldset>
                        <legend class="leg"><big><b> Фотки</b></big></legend> 
                        <table border="0" cellspacing="0" cellpadding="5" width="100%">
		    	  <form method="post" name="form1"  enctype="multipart/form-data">
			  <tr>
			  <td colspan=3>
			    <input type='file' name='foto'><br>
			    <input type=checkbox name='ismain'> Как главную
			  <input type="submit" value="Загрузить" name="reg"><br>
			  </td>
			  </tr>
                          <tr valign="top">
                            <td align="center" colspan=3>
			    <b>Главная фотка</b>:<p>
			    <input type=hidden name='MAIN' value='1'>
			    <div id='mphot' class=phpoplist>
			    <a href='<?=$main_foto_big?>' tb=1><!--'<??> '-->
			    <img border=0 src='<?=$main_foto_thumb_small?>'></td><!--'<??> '-->
			    </a>
			    </div>
				</td>
                          </tr>
			    </form>
			    <tr><td>
			<?
//	die;
				$result=mysql_query("select  id,url_thumb_small, url_scaled ,url_host from photos where uid='$uid' order by id") or die(mysql_error());
				while($row=mysql_fetch_row($result))
				{
					$pid=$row[0];
					$url_thumb_small=$row[1];
					$url_scale=$row[2];
					$url_host=$row[3];
					$url_s=$url_host.$url_thumb_small;
					$url_e=$url_host.$url_scale;
					echo "<div style='float: left' id='ph$pid' class=photolist><a href='$url_e' tb=1><img border=0 src='$url_s'></a> <a href='#' onclick='return move_to_trash($pid);'><img src='/pics/del.gif' alt='Удалить фотку' style='position: relative; left: -10px'></a> &nbsp;</div>\n";
				}
			?>

			    </td></tr>
			 </table>	 
			 <table></table>
			  <div id='trash' style="width: 100%; display: none; ">
			  <form name='frem' method=post>
			  <input type=hidden name=remf>
			  <h3>Помойка</h3>
			  <input type=submit value='Удалить фотки' onclick="return on_remove();"><br>
			  </form>
			  </div>

		</fieldset>
		<p>
                      <center>
                        <input type="hidden" name="DATA1" value="yes"> 
			<input type="submit" value="Продолжить" name="reg"><br>
                      </center>
	<!--/form-->

	</div>

		

      <?
      //END
      ?>
      </td>

      <td></td>

      <td>
        <?
            include 'inc/user_list.php';
        ?>
      </td><!-- up to 22 may-->
    </tr>
  </table>

  <p align="left"> </p>
  <hr>

    <?
    include 'diz/bottom_table.php';
    ?>
    
</body>
			 <script>
			 	$("a[tb=1]").fancybox();
			 </script>

</html>
