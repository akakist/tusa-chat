<?
function build_thumbnail($img, $tumb_width, $tumb_height)
{
//			echo sprintf(" KALL %s %d",__FILE__,__LINE__);
	$width = imageSX($img);
	$height = imageSY($img);

//			echo sprintf(" KALL %s %d",__FILE__,__LINE__);
	$target_width = $tumb_width;
	$target_height = $tumb_height;
	
	$target_ratio = $target_width / $target_height;
	$img_ratio = $width / $height;
//			echo sprintf(" KALL %s %d",__FILE__,__LINE__);
	
	$offx=0;
	$offy=0;
	$new_width=$width;
	$new_height=$height;
	
//			echo sprintf(" KALL %s %d",__FILE__,__LINE__);
	if($img_ratio > $target_ratio) {
		$diff_ratio = $target_ratio / $img_ratio;
		$new_width = $width * $diff_ratio;
		$offx = ($width - $new_width) / 2;
	}
//			echo sprintf(" KALL %s %d",__FILE__,__LINE__);
	if($img_ratio < $target_ratio){
		$diff_ratio = $img_ratio / $target_ratio;
		$new_height = $height * $diff_ratio;
		$offy = ($height - $new_height) / 2;
	}
//			echo sprintf(" KALL %s %d",__FILE__,__LINE__);

	$new_img = ImageCreateTrueColor($tumb_width, $tumb_height);

	// Fill the image black
//			echo sprintf(" KALL %s %d",__FILE__,__LINE__);
	if (!@imagefilledrectangle($new_img, 0, 0, $target_width-1, $target_height-1, 0)) {
		echo "ERROR\nCould not fill new image";
//		exit(0);
	}
//			echo sprintf(" KALL %s %d",__FILE__,__LINE__);

	if (!@imagecopyresampled($new_img, $img, 0, 0, $offx, $offy, $target_width, $target_height, $new_width, $new_height)) {
		echo "ERROR\nCould not resize image";
//		exit(0);
	}

	return $new_img;
}
function resize_image($img, $max_width,$max_height)
{
	$width = imageSX($img);
	$height = imageSY($img);

	if($width<$max_width && $height<$max_height) return $img;
	$ratio=$width/$max_width;
	if($height/$max_height>$ratio)$ratio=$height/$max_height;
	
	$new_width=intval($width/$ratio);
	$new_height=intval($height/$ratio);
	

	$new_img = ImageCreateTrueColor($new_width, $new_height);

	// Fill the image black
	if (!@imagefilledrectangle($new_img, 0, 0, $new_width-1, $new_height-1, 0)) {
		echo "ERROR\nCould not fill new image";
		exit(0);
	}

	if (!@imagecopyresampled($new_img, $img, 0, 0, 0, 0, $new_width, $new_height, $width, $height)) {
		echo "ERROR\nCould not resize image";
		exit(0);
	}

	return $new_img;
}

?>