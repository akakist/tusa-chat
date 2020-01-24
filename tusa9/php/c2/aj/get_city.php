<?
        import_request_variables("gp", "arg_");
	include "$BASE_DIR/inc/db_conn.php";
	check_conn();
	?>
						<select name=sel>
					<OPTION VALUE=0 SELECTED>Выберите город
						<?
						$c=$arg_r;
							$result=mysql_query("select city_id,title from cities where region_id='".mysql_escape_string($c)."' order by 1") or die(mysql_error());
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

