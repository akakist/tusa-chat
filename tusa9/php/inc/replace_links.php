<?
	function replace_links($s)
	{
            $patt="/(http|ftp|mailto):\/\/([\?\/\w\.\%\&\=€-ï]+)/";
            return preg_replace($patt,"<a href='$1://$2' target=_blank>$1://$2</a>",$s);

	
	}
?>