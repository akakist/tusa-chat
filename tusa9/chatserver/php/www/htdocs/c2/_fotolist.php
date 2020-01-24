<?
	header("Content-Type: text/html; charset=\"windows-1251\"");
        import_request_variables("gp", "arg_");
	include "inc/db_conn.php";
	check_conn();

			
				$result=mysql_query("select  id,url_thumb_small, url_scaled ,url_host from photos where uid='$arg_id' order by id") or die (mysql_error());
				if(mysql_num_rows($result))
				{
				while($row=mysql_fetch_row($result))
				{
					$pid=$row[0];
					$url_thumb_small=$row[1];
					$url_scale=$row[2];
					$url_host=$row[3];
					$url_s=$url_host.$url_thumb_small;
					$url_e=$url_host.$url_scale;
					echo "<div style='float: left' id='ph$pid'><a href='$url_e'><img border=0 src='$url_s'></a>  &nbsp;</div>\n";
				}
				}
				else echo "Нет фоток";
			

?>