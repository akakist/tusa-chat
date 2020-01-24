<?
	function remove_tags($s)
	{
		$patt=array("/\&/","/\</","/\>/");
		$repl=array("&amp;","&lt;","&gt;");
		return preg_replace($patt,$repl,$s);
	}

?>