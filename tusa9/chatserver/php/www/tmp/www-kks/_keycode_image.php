<?
	srand(time());

//	if(isset($_REQUEST[session_name()])){
        	session_start();
//	}
	
		
	header ('Content-type: image/png');
	$im = imagecreatetruecolor(100, 30) or die('Cannot Initialize new GD image stream');
	$background = imagecolorallocate($im, 255, 255, 255);
	imagefill($im,0,0,$background);
	
	$text="";
	
	for($i=0; $i<5; $i++){
		$letter=rand(0,9);
		$text.=$letter;
		$text_color = imagecolorallocate($im, rand(0,150), rand(0,150), rand(0,150));
		imagestring($im, 5, $i*20+rand(0,15), rand(0,15), $letter, $text_color);
	}
	
	for($i=0; $i<200; $i++){
		$c=imagecolorallocate($im,rand(0,255),rand(0,255),rand(0,255));
		imagesetpixel($im,rand(0,100),rand(0,30),$c);
	}

//	if($_REQUEST[session_name()]){
        	$_SESSION['key'] = $text;
//	}
	
	imagepng($im);
	imagedestroy($im);
?>
