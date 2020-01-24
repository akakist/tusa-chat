<?

     	    function split_long($s)
     	    {
     	    	return $s;
     	    	$out="";
     	    	$r=split(" ",$s);
     	    	foreach($r as $v)
     	    	{
     	    		if(strlen($v)>$MAX_WORD_SIZE)
     	    		{
     	    			while(strlen($v))
     	    			{
     	    				$subs=substr($v,0,$MAX_WORD_SIZE);
     	    				$v=substr($v,$MAX_WORD_SIZE);
     	    				$out.=" ".$subs;
     	    			}
     	    		}
     	    		else $out.=$v;
     	    	}
     	    	return $out;

     	    }

?>