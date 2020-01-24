<?
    function str_nick($s)
    {
	$pat= "РСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэюя№ёђѓєѕіїјљњћќ§ўџabcdefghijklmnopqrstuvwxyz";
	$repl="AСBУФEЦЧШЩKЫMHOЯPCTгдXжзийклмнопAСBУФEЦЧШЩKЫMHOЯPCTгдXжзийклмнопABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return strtr($s,$pat,$repl);
    
    }
    
    function check_nick($s)
    {
    	if(preg_match("/^[A-Z,a-z,р-џ,Р-п]+[A-Z,a-z,р-џ,Р-п,0-9]+$/",$s)){
		return 1;
	}else{
		return 0;
	}
    }
    
?>