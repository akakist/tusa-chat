<?
    function str_nick($s)
    {
	$pat= "����������������������������������������������������������������abcdefghijklmnopqrstuvwxyz";
	$repl="A�B��E����K�MHO�PCT��X����������A�B��E����K�MHO�PCT��X����������ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return strtr($s,$pat,$repl);
    
    }
    
    function check_nick($s)
    {
    	if(preg_match("/^[A-Z,a-z,�-�,�-�]+[A-Z,a-z,�-�,�-�,0-9]+$/",$s)){
		return 1;
	}else{
		return 0;
	}
    }
    
?>