<?
	header("Content-Type: text/html; charset=\"windows-1251\"");
        import_request_variables("gp", "arg_");
	include "inc/db_conn.php";
	check_conn();
	$aid=intval($arg_id);



	
?>
<!--CROP-->	
	<div style='width: 400px'>
		<div class="highslide-gallery">
	<?
	$result=mysql_query("select url_thumb_small,url_scaled,descr from photos where uid='$aid' order by id");
	while(list($url_thumb_small,$url_scaled,$descr)=mysql_fetch_row($result))
	{

	?>
			<a href="<?=$url_scaled?>" class="highslide" onclick="return hs.expand(this)">
				<img src="<?=$url_thumb_small?>" alt="Фотка" title="<?=$descr?>" /> <!--"<??> "'-->
			</a>
			<div class="highslide-caption"><?=$descr?></div>
	<?	
	}
	?>
		</div>
	</div>
<!--CROP-->	
