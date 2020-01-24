<?
	function get_rusmon($m)
	{
		switch($m)
		{
	case 1: return '€нвaр€';break;
	case 2: return 'феврал€';break;
	case 3: return 'марта';break;
	case 4: return 'апрел€';break;
	case 5: return 'ма€';break;
	case 6: return 'июн€';break;
	case 7: return 'июл€';break;
	case 8: return 'августа';break;
	case 9: return 'сент€бр€';break;
	case 10: return 'окт€бр€';break;
	case 11: return 'но€бр€';break;
	case 12: return 'декабр€';break;
		}
	}
		
		

	function get_rusdate($d)
	{
		$r=split(" ",$d);
		if(count($r)==2)
		{
			$dt=split("-",$r[0]);
			if(count($dt)==3)
			{
			return $dt[2]." ".get_rusmon(intval($dt[1]))." ".$dt[0];
			}
		}
		return "";
	}
	function get_time($d)
	{
		$r=split(" ",$d);
		if(count($r)==2)
		return $r[1];
		return "";
	
	}
?>
