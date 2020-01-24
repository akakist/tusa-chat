<?
	include "inc/db_conn.php";
	check_conn();
	srand(time());
        	session_start();
//	header ('Content-type: text/plain');
	header ('Content-type: image/png');
$X=450;
$Y=250;
$MARGIN=30;

$ymax=$Y-2*$MARGIN;
$xmax=$X-2*$MARGIN;

function x($n)
{
	global $MARGIN;
	return $n+$MARGIN;
}

function y($n)
{
	global $MARGIN;
	global $Y;
	return $Y-$MARGIN-$n;
}
	
	$im = @imagecreatetruecolor($X, $Y) or die('Cannot Initialize new GD image stream');
	$background = imagecolorallocate($im, 0, 0x35, 0x70);
//	#003570
	$fg=imagecolorallocate($im, 0xee, 0xcc, 0x30);
	$ax=imagecolorallocate($im, 0xdc, 0xdc, 0xdc);
//	eecc30
	imagefill($im,0,0,$background);
	
	$text="";
	
	$res=mysql_query("select UNIX_TIMESTAMP(dt),cnt from users_count where dt> SUBDATE(NOW(), interval 1 day) order by dt") or die(mysql_error());
	$max=0;
	$mindt=time();
	$arr=array();
	while(list($dt,$cnt)=mysql_fetch_row($res))
	{
		if($cnt>$max)$max=$cnt;
		$arr[$dt]=$cnt;
//		array_push($arr,$dt=>$cnt);
	}
//	$max=1221;
	if($max%10>0)$max=(intval($max/10)+1)*10;
	// arrows
		//vert
//	imageline($im,x(0),y(0)$MARGIN,$MARGIN,$Y-$MARGIN,$fg);
	imageline($im,x(0),y(0),x(0),y($ymax),$ax);
	imageline($im,x(0),y(0),x($xmax),y(0),$ax);
	//hor
	$Ystep=$ymax/$max;
	$Xstep=$xmax/24;
	
	$Ystep=($Y-2*$MARGIN)/$max;
	
	imageline($im,x(-3),y($ymax),x(0),y($ymax),$ax);
	imagestring($im, 2, x(-23),y($ymax)-4, $max, $ax);
	
	imageline($im,x(-3),y($ymax/2),x(0),y($ymax/2),$ax);
	imagestring($im, 2, x(-23),y($ymax/2)-4, intval($max/2), $ax);
	
	$lt=localtime();
	$hour=$lt[2];
	$hrs=array();
	$h=$hour;
	for($i=0;$i<25;$i++)
	{
//		$l=$starth;
		if($h>23) $h=0;
		
		imageline($im,x($Xstep*$i),y(-3),x($Xstep*$i),y(0),$ax);
		imagestring($im, 2, x($Xstep*$i-2),y(-5), $h, $ax);
		$h++;
		
	}
	
//imagestring($im, 1, x(0),y(0), $hour[2], $fg);
	
	$start_t=time()-3600*24;
	
	foreach( $arr as $key=>$val)
	{
		
//		echo "$key $val\n";
//		echo ($key-$start_t)/(3600)."\n";
		$x=x(($key-$start_t)/(3600)*$Xstep);
		$y=y($val*$Ystep);
//		imageline($im,$x,$y,$x,y(0),$fg);
		imagefilledrectangle ( $im , $x,$y, $x+2, y(0), $fg );
		
		
		
	}
	
	/*for($i=0; $i<5; $i++){
		$letter=rand(0,9);
		$text.=$letter;
		$text_color = imagecolorallocate($im, rand(0,150), rand(0,150), rand(0,150));
		imagestring($im, 5, $i*20+rand(0,15), rand(0,15), $letter, $text_color);
	}
	
	for($i=0; $i<200; $i++){
		$c=imagecolorallocate($im,rand(0,255),rand(0,255),rand(0,255));
		imagesetpixel($im,rand(0,100),rand(0,30),$c);
	}

       	$_SESSION['key'] = $text;
	*/
	
	imagegif($im);
	imagedestroy($im);
?>
