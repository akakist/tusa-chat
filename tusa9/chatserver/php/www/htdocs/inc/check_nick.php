<?
	function check_nick($str)
	{
	    	$chars = preg_split("/[0-9a-zA-ZР-пр-џ\$\*\-\_]+/", $str, -1, PREG_SPLIT_NO_EMPTY);
       		if(count($chars))
       			return false;
		preg_match("/^[\_\-\=\*]/",$str,$matches,PREG_OFFSET_CAPTURE);
		if(count($matches))
			return false;
		return true;
	}
?>