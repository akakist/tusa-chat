<?
	function get_rusmon($m)
	{
		switch($m)
		{
	case 1: return '���a��';break;
	case 2: return '�������';break;
	case 3: return '�����';break;
	case 4: return '������';break;
	case 5: return '���';break;
	case 6: return '����';break;
	case 7: return '����';break;
	case 8: return '�������';break;
	case 9: return '��������';break;
	case 10: return '�������';break;
	case 11: return '������';break;
	case 12: return '�������';break;
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
