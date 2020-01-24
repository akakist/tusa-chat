<?
function calc_age($byear,$bday)	
{
	$r=localtime();
	$age=$r[5]+1900-$byear-1;
	if($r[7]>=$bday) $age+=1;
	return $age;
}
	printf("%d",calc_age(1980,1));

?>

