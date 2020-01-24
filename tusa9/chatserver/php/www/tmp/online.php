<?
	header("Content-Type: text/html; charset=\"windows-1251\"");

?>
<li class='online-title' >Сейчас в чате</li>
<li class='online-block'>
<?
	$fn="/tmp/users_online";
	$c="";
	$f=fopen($fn,"r");
	if($fn)
	{
		echo filesize($fn);
		if(filesize($fn)>0)
		{
			$c=fread($f,filesize($fn));
		}	
	fclose($f);
	}
	
	$r=preg_split("[\n]",$c);
	$total=0;
	foreach($r as $l)
	{
		$vv=split(" ",$l);
		if(count($vv)==3)
		{
			$total+=$vv[2];
			echo "<a href=\"\">$vv[1] ($vv[2])</a>\n";
		}	
		
	}
?>
<div class="online-info">Всего: <span style="font-weight: bold;"><?=$total?></span></div>
</li>
