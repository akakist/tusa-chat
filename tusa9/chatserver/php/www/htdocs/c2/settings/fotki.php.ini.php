<script type="text/javascript" src="/highslide/highslide-with-gallery.js"></script>
<link rel="stylesheet" type="text/css" href="/highslide/highslide.css" />

<script type="text/javascript"> 
	hs.graphicsDir = '/highslide/graphics/';
	hs.align = 'center';
	hs.transitions = ['expand', 'crossfade'];
	hs.outlineType = 'glossy-dark';
	hs.wrapperClassName = 'dark';
	hs.showCredits=false;
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
include 'inc/build_thumbnail.php';
include 'inc/cache_dir.php';

function chkdir($dir)
{
	global $VAR_DIR;
	$pi=pathinfo($VAR_DIR.$dir);
	if(!@stat($pi["dirname"]))
	{
		if(!mkdir($pi["dirname"],0777,true))
		{
			die("cannot mkdir ".$pi["dirname"]);
		}
	}	

}
function make_image($im,$uid,$ismain,$descr)
{
	global $VAR_DIR;
	$pid=$uid;
	if(!$ismain)
	{
		mysql_query("insert into photos (uid) values('$uid')") or die(mysql_error());
		$pid=mysql_select1("select last_insert_id()");
	}
	$dst=build_thumbnail($im,85,110);
	$TSU=thumb_small_url($pid,$ismain);
	chkdir($TSU);
	if(!imagejpeg($dst,$VAR_DIR.$TSU))die("Не могу записать изображение ".$VAR_DIR.$TSU);
	if($ismain)
	{
		$dst=build_thumbnail($im,400,550);
		$TBU=thumb_big_url($pid);
		chkdir($TBU);
		if(!imagejpeg($dst,$VAR_DIR.$TBU))die("Не могу записать изображение ".$VAR_DIR.$TBU);
	}
	else
	{
		$dst=resize_image($im,800,600);
		$IRU=image_resized_url($pid);
		chkdir($IRU);
		if(!imagejpeg($dst,$VAR_DIR.$IRU))die("Не могу записать изображение ".$VAR_DIR.$IRU);
	}

	if($ismain)
	{
		mysql_query("update tbl_users set foto_thumb_small='$TSU', foto_thumb_big='$TBU',has_main_foto=1 where id='$uid'") or die(mysql_error());
	}
	else
	{
	
		mysql_query("update photos set url_thumb_small='$TSU', url_scaled='$IRU', descr='$descr' where id='$pid'") or die(mysql_error());
		$np=mysql_select1("select count(*) from photos where uid='$uid'");
		mysql_query("update tbl_users set foto_count='$np' where id='$uid'") or die(mysql_error());
	}
}
if(isset($arg_rmmain))
{
	
	$TSU=thumb_small_url($uid,true);
	$TBU=thumb_big_url($uid);
	unlink($VAR_DIR.$TSU);
	unlink($VAR_DIR.$TBU);
	$g=mysql_select1("select gender from tbl_users where id='$uid'");
	if($g==2)
	{
		$fb="/pics/noimage-female-big.jpg";
		$fs="/pics/noimage-female-small.jpg";
	}
	else
	{
		$fb="/pics/noimage-male-big.jpg";
		$fs="/pics/noimage-male-small.jpg";
	}
	mysql_query("update tbl_users set has_main_foto=0,foto_thumb_small='$fs',foto_thumb_big='$fb' where id='$uid'");
	
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
	$res=mysql_query("select url_thumb_small,url_scaled from photos where uid='$uid' and id in($j)") or die(mysql_error());
	while($row=mysql_fetch_row($res))
	{
		foreach($row as $p)
		{
			$pn=$VAR_DIR.$p;
			unlink($pn);
		}
	}
	mysql_query("delete from photos where uid='$uid' and id in ($j)") or die(mysql_error());

	$np=mysql_select1("select count(*) from photos where uid='$uid'");
	mysql_query("update tbl_users set foto_count='$np' where id='$uid'") or die(mysql_error());
	
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
	if($im=&imagecreatefromjpeg($tmpname)) 
//	if($im=imagecreatefromjpeg($tmpname)) 
	{
		make_image($im,$uid,$ismain,$arg_descr);

	}
}

?>