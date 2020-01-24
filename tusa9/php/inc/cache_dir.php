<?
function new_cache_dir($name, $uid)
{
	global $VAR_DIR;
	$uid=$uid/100;
    if ($uid<100)
    {
        return sprintf("/$name/0/%02d",$uid);
    }
    else if ($uid<10000)
    {
    	$u1=$uid/100;
	$u2=$uid%100;
        return sprintf ("/$name/1/%02d/%02d",$u1,$u2); 
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
        return  sprintf("/$name/2/%02d/%02d/%02d",$u1,$u2,$u3); 
    }
    else{
    	echo "Error limit";
    }
    return "";

}
function thumb_big_url($pid)
{// only main img
	return new_cache_dir("thumb-big-main",$pid)."/$pid.jpeg";
}

function thumb_small_url($pid,$ismain)
{
	if($ismain)
	return new_cache_dir("thumbs-small-main",$pid)."/$pid.jpeg";
	else
	return new_cache_dir("thumbs-small-photo",$pid)."/$pid.jpeg";
	
}
function image_resized_url($pid)
{// only not main image
	return new_cache_dir("resized-photo",$pid)."/$pid.jpeg";
	
}

?>