<?
function calc_age($byear,$bday)	
{
	if(!isset($byear)) return "����������";
	$r=localtime();
	$age=$r[5]+1900-$byear-1;
	if($r[7]>=$bday) $age+=1;
	if($age>200) return "����������";
	return $age;
}

?>