<?
	session_start();
        import_request_variables("gp", "arg_");
	include "inc/db_conn.php";
	check_conn();
     if(isset($_SESSION['login']))
     {
     	$login=$_SESSION['login'];
	$uid=$_SESSION['uid'];
     }
    
     if(!isset($login))
     {
     	header("Location: /");
     }
	
		if(isset($_REQUEST['DATA1']))
		{
			if(isset($arg_selother))
				$city=mysql_escape_string($arg_selother);
			else $city=mysql_escape_string(mysql_select1("select title from cities where city_id=$arg_sel"));
			$fname=isset($arg_fname)?mysql_escape_string($arg_fname):"";
			$lname=isset($arg_lname)?mysql_escape_string($arg_lname):"";
			$hide_name=isset($arg_hide_name)?$arg_hide_name=="on":false;
			$hide_bd=isset($arg_hide_bd)?$arg_hide_bd=="on":false;
			$hide_sel=isset($arg_hide_sel)?$arg_hide_sel=="on":false;

			$bdate="$arg_by-$arg_bm-$arg_bd";

			$sql=sprintf("update tbl_users set city='$city', 
							birth_date='$bdate',
							fname='$fname',
							lname='$lname', 
							hide_fname='%d', 
							hide_lname='%d', 
							hide_bdate='%d', 
							hide_city='%d' where id=$uid",$hide_name,$hide_name,$hide_bd,$hide_sel);
			mysql_query($sql) or die(mysql_error());
			echo mysql_error();				
			header("Location: fotki.php?r=".rand());
		}
		$r=mysql_select1row("select day(birth_date), 
					month(birth_date),
					year(birth_date),
					city,
					fname,
					lname, 
					hide_fname,
					hide_city, 
					hide_bdate 
					from tbl_users
					where id=$uid");
			echo mysql_error();				
		
		$bd=$r[0];
		$bm=$r[1];
		$by=$r[2];
		$city=$r[3];
		$fname=$r[4];
		$lname=$r[5];
		$hide_name=$r[6];
		$hide_city=$r[7];
		$hide_bdate=$r[8];
		if(isset($error))
		{
			?>
			<div align=center class=yelmsg style='margin-bottom: 20px'><b> <?=$error?></b></div>
			<?
		}
		else
		{	
		}
//		echo '<script>window.top.location="/registration/fotki.php"</script>';
		
	

  ?>
<html>
<head>
  <meta http-equiv="PRAGMA" content="no-cache">
  <meta http-equiv="Content-Type" content="text/html; charset=windows-1251">

  <title>Чат "Тусовка"</title>
  <link rel="stylesheet" type="text/css" href="/css/main.css">
	<script type="text/javascript" src="/js/jquery.pack.js"></script>
  
  <script language="javascript" src="/css/mmove.js" type="text/javascript"></script>
</head>
<script>
function on_subm()
{
	return false;
}
				var country_id=0;
				var region_id=0;
				var city_id=0;
				    function select_region(f) {  
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
				    }
						    

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
	<div id=regform>
	<form method="post" action="/registration/2.php" name="form1" onsubmit="return checkform();">
               <fieldset>
                        <legend class="leg"><big><b>Страница 2 из 2</b></big></legend> 
                        <table border="0" cellspacing="0" cellpadding="5">
                            <td align="right" width="125">Ваше имя:</td>
                            <td>
			    	<input type="text" maxlength="16" size="20" name="fname" value='<?=$fname?>' >
							    <!--'<??> '-->

<!--			    	<input type="text" maxlength="16" size="20" name="lname" value='<?=$lname?>' > -->
							    <!--'<??> '-->
			    </td>
			    
                            <td><input id=hide_name type=checkbox name=hide_name class=c_b <?if($hide_name) echo 'CHECKED'?> > <label for=hide_name>скрыть имя</label></td>
	                  </tr>
                          <tr valign="top">
                            <td align="right">Дата рождения</td>
                            <td>
			    	<select name=bd>
				<?
					for($i=1;$i<31;$i++)
					{
						if($i==$bd)
						echo "<OPTION value=$i SELECTED> ".sprintf("%02d",$i)."\n";
						else
						echo "<OPTION value=$i> ".sprintf("%02d",$i)."\n";
					}
				?>
				</select>
				<select name=bm>
				<option value=1> января <option value=2> февраля <option value=3> марта
				<option value=4> апреля <option value=5> мая	<option value=6> июня
				<option value=7> июля 	<option value=8> августа <option value=9> сентября <option value=10> октября
				<option value=11> ноября <option value=12> декабря
				</select>
				<select name=by>
				<?
					if(!isset($by)) $by=1985;
					for($i=1900;$i<2000;$i++)
					{
						if($i==$by)
							echo "<OPTION value=$i SELECTED> $i\n";
						else 
							echo "<OPTION value=$i> $i\n";
					}
				?>
				</select>
			    
			    </td>
                            <td><input type=checkbox id=hide_bd name=hide_bd class=c_b <?if($hide_bdate) echo 'CHECKED'?> > <label for=hide_bd>скрыть дату рождения</label></td>
                          </tr>
                          <tr valign="top">
				<script>
				</script>

                          <tr valign="top">
                            <td align="right" width="125">Мой город</td>
                            <td>
			    	<div id='location'> 
				
					<select name="selother">
					<!--onChange="select_region(this.form)-->
					<!--OPTION VALUE='' SELECTED>Выберите город-->
<!--					<OPTION VALUE='Томск' SELECTED>Томск
					<OPTION VALUE='Северск'>Северск
-->
<?
	$sel="Томск";
	if(isset($arg_selother)) $sel=$arg_selother;
	$r=mysql_query("select title from cities where region_id=65 order by title") or die(mysql_error());
        while($row=mysql_fetch_array($r)){
?>
						<option value="<?=$row["title"]?>" <?=$sel==$row["title"]?" SELECTED":""?> > <?=$row["title"]?>  <!--" -->
<?
	}
?>
					</select>
				</div>
<!--				<div id=another>
				<input type=checkbox name=another onclick="do_another();" class=c_b> Другое
				</div>
-->
				<?
					if(strlen(trim($city))>0) echo "<script>do_another();form1.selother.value='$city';</script>";
				?>
			    </td>
<!--                            <td><input type=checkbox name=hide_sel class=c_b <?if($hide_city) echo 'CHECKED'?> > скрыть</td> -->
	                  </tr>

			 </table>	 

			  

		</fieldset>
		<p>
                      <center>
                        <input type="hidden" name="DATA1" value="yes"> 
			<input type="submit" value="Продолжить" name="reg"><br>
                      </center>
	</form>

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
</html>
