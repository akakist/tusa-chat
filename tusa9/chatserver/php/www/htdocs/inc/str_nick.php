<?
    function str_nick($s)
    {
	$pat= '����������������������������������������������������������������abcdefghijklmnopqrstuvwxyz';
	$repl='A�B��E����K�MHO�PCT��X����������A�B��E����K�MHO�PCT��X����������ABCDEFGHIJKLMNOPQRSTUVWXYZ';
	return strtr($s,$pat,$repl);
    
    }
?>