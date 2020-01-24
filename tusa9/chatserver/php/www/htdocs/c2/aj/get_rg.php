<?
//	header("Content-Type: text/html; charset=\"windows-1251\"");
        import_request_variables("gp", "arg_");
	include "inc/db_conn.php";
	check_conn();
	?>
					<select name=sel onChange="select_city(this.form)">
					<OPTION VALUE=0 SELECTED>Выберите регион
						<?
						$c=$arg_c;
							$result=mysql_query("select region_id,title from regions where country_id='$c' order by 1") or die(mysql_error());
		
					    		while ($row=mysql_fetch_row($result)){
							    if(count($row)==2)
							    {
							    	$cid=$row[0];
								$cname=$row[1];
							    	echo "<OPTION VALUE='$cid'>$cname\n";
							    }
							}	
							
						?>
					</select>

