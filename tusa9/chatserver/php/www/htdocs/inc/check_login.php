<?
	function check_login($str)
	{
	    	$chars = preg_split("/[0-9a-zA-Z\@\.\-\_]+/", $str, -1, PREG_SPLIT_NO_EMPTY);
       		if(!count($chars))
	     	  	return true;
       		else 
       			return false;

		return false;
       }
	         
       
?>