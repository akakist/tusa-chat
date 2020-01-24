#!/usr/local/bin/php
<?php
function new_cache_dir($name, $uid)
{
	$uid=$uid/100;
    if ($uid<100)
    {
        return sprintf("/var/chat/$name/0/%02d",$uid);
    }
    else if ($uid<10000)
    {
    	$u1=$uid/100;
	$u2=$uid%100;
        return sprintf ("/var/chat/$name/1/%02d/%02d",$u1,$u2); 
    }
    else if ($uid<1000000)
    {
        $u1=$uid/10000;
        $u2=($uid-($u1*10000))/100;
        $u3=$uid%100;
	$uid/=100;
	$u2=$uid%100;
	$uid/=100;
	$u1=$uid%100;
        return  sprintf("/var/chat/$name/2/%02d/%02d/%02d",$u1,$u2,$u3); 
    }
    else{
    	echo "Error limit";
    }
    return "";

}
function new_foto_pn($pid, $ext)
{
	$d=new_cache_dir("photos",$pid);
    	$pn=$d."/$pid.$ext";
    return $pn;
}
function thumb_big($pid)
{
	return new_cache_dir("thumbs-big",$pid)."/$pid.jpeg";
}

function thumb_small($pid)
{
	return new_cache_dir("thumbs-small",$pid)."/$pid.jpeg";
}

function build_thumbnail($img, $tumb_width, $tumb_height)
{
	$width = imageSX($img);
	$height = imageSY($img);

	$target_width = $tumb_width;
	$target_height = $tumb_height;
	
	$target_ratio = $target_width / $target_height;
	$img_ratio = $width / $height;
	
	$offx=0;
	$offy=0;
	$new_width=$width;
	$new_height=$height;
	
	if($img_ratio > $target_ratio) {
		$diff_ratio = $target_ratio / $img_ratio;
		$new_width = $width * $diff_ratio;
		$offx = ($width - $new_width) / 2;
	}
	if($img_ratio < $target_ratio){
		$diff_ratio = $img_ratio / $target_ratio;
		$new_height = $height * $diff_ratio;
		$offy = ($height - $new_height) / 2;
	}

	$new_img = ImageCreateTrueColor($tumb_width, $tumb_height);

	// Fill the image black
	if (!@imagefilledrectangle($new_img, 0, 0, $target_width-1, $target_height-1, 0)) {
		echo "ERROR\nCould not fill new image";
		exit(0);
	}

	if (!@imagecopyresampled($new_img, $img, 0, 0, $offx, $offy, $target_width, $target_height, $new_width, $new_height)) {
		echo "ERROR\nCould not resize image";
		exit(0);
	}

	return $new_img;
}



		$db = mysql_connect('localhost:/tmp/mysql.sock', 'root', '');
		mysql_select_db('chat') or die ('Can"t select database : ' . mysql_error());

		$sql="select id,uid from photos order by id";
		$result=mysql_query($sql) or die (mysql_error());

    		while ($row=mysql_fetch_row($result)){
			$id=$row[0];
			$uid=$row[1];
			$src_path=new_foto_pn($id,"jpeg");
			$dst_big_path=thumb_big($id);
			$dst_small_path=thumb_small($id);
			if(!stat($dst_big_path))
			{

			if(!stat($src_path))
			{
				echo "not foubnd $src_path\n";
		echo "\ndelete from photos where id=$id;\n";
				continue;
			}
			
			if($im=imagecreatefromjpeg($src_path)) 
			{
				$dst_big=build_thumbnail($im,400,550);
				$dst_small=build_thumbnail($im,85,110);
				$p_big=pathinfo($dst_big_path);
				$p_small=pathinfo($dst_small_path);
				if(!stat($p_big["dirname"]))
				{
					mkdir($p_big["dirname"],0777,true);
				}
				if(!stat($p_small["dirname"]))
				{
					mkdir($p_small["dirname"],0777,true);
				}
				imagejpeg($dst_big,$dst_big_path);
				imagejpeg($dst_small,$dst_small_path);
					echo "$id\n";
			}
			else
			{
		echo "delete from photos where id=$id;\n";
			}
			}
	}

?>