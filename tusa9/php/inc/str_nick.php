<?
    function str_nick($s)
    {
	$pat= 'РСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэюя№ёђѓєѕіїјљњћќ§ўџabcdefghijklmnopqrstuvwxyz';
	$repl='AСBУФEЦЧШЩKЫMHOЯPCTгдXжзийклмнопAСBУФEЦЧШЩKЫMHOЯPCTгдXжзийклмнопABCDEFGHIJKLMNOPQRSTUVWXYZ';
	return strtr($s,$pat,$repl);
    
    }
?>