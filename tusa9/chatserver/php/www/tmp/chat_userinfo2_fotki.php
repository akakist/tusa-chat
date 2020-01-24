<?
	header("Content-Type: text/html; charset=\"windows-1251\"");
        import_request_variables("gp", "arg_");
	include "inc/db_conn.php";
	check_conn();
	$arg_id=intval($arg_id);
	$result=mysql_query("select url_thumb_small,url_scaled from photos where uid='$arg_id' order by id");
	echo "<div style='width: 400px'>";
	while(list($url_thumb_small,$url_scaled)=mysql_fetch_row($result))
	{
		echo " <a  href=$url_scaled tbb=1><img  class='ph' src=$url_thumb_small></a>";
	}
	echo "</div>";
	
?>

