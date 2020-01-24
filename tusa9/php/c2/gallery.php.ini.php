<script type="text/javascript" src="/highslide/highslide-with-gallery.js"></script>
<link rel="stylesheet" type="text/css" href="/highslide/highslide.css" />

<script type="text/javascript"> 
	hs.graphicsDir = '/highslide/graphics/';
	hs.align = 'center';
	hs.transitions = ['expand', 'crossfade'];
	hs.outlineType = 'glossy-dark';
	hs.wrapperClassName = 'dark';
	hs.fadeInOut = true;
	//hs.dimmingOpacity = 0.75;
 
	// Add the controlbar
	if (hs.addSlideshow) hs.addSlideshow({
		//slideshowGroup: 'group1',
		interval: 5000,
		repeat: false,
		useControls: true,
		fixedControls: 'fit',
		overlayOptions: {
			opacity: .6,
			position: 'bottom center',
			hideOnMouseOut: true
		}
	});
</script>

<?
if(isset($arg_remf) && isset($_SESSION['privs']['photo']))
{
	$r=split("_",$arg_remf);
	$zid=intval($arg_zid);
	$rr=array();
	for($i=0;$i<count($r);$i++)
	{
		if(strlen($r[$i]))array_push($rr,intval($r[$i]));
	}
	$j=join(",",$rr);
	$res=mysql_query("select url_thumb_small,url_scaled from photos where uid='".intval($zid)."' and id in($j)") or die(mysql_error());
	while($row=mysql_fetch_row($res))
	{
		foreach($row as $p)
		{
			$pn=$VAR_DIR.$p;
//echo $pn;
			unlink($pn);
		}
	}
	mysql_query("delete from photos where uid='".intval($zid)."' and id in ($j)") or die(mysql_error());

	$np=mysql_select1("select count(*) from photos where uid='".intval($zid)."'");
	mysql_query("update tbl_users set foto_count='$np' where id=".intval($zid)."''") or die(mysql_error());
	
}
?>