<?
	 $str = ' string@mail.ru';
	    $chars = preg_split("/[a-zA-Z\@\.]+/", $str, -1, PREG_SPLIT_NO_EMPTY);
       print_r($chars);
       if(!count($chars))
       echo 'OK';
       else 
       echo 'FALSE';
	         
       
?>