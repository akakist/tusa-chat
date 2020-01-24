<?
	$imgn=$_REQUEST["n"];
?>
<script>
function sp(n)
{
	var el=document.getElementById('sp<?=$imgn?>');
	if(el)
	{
		el.src='/pics/s/sp'+n+'.gif';
	}
	else alert("element not found sp<?=$imgn?>");
	document.form1.spi<?=$imgn?>.value=n;
//	window.close();
	return false;
}
lobj=null;
lnum=0;
function ch(obj,num)
{
	if(num==lnum) return false;
    if(lobj!=null){
    	lobj.style.fontWeight='';
		document.getElementById('l'+lnum).style.visibility='hidden';
    }
	document.getElementById('l'+num).style.visibility='visible';
	obj.style.fontWeight='bold';
	lobj=obj;
	lnum=num;
	return false;
}
</script>
<body>
<style>
IMG {width: 16; height: 16; border: 0}
#l1 {visibility: hidden; position: absolute; left: 130;}
#l2 {visibility: hidden; position: absolute; left: 130;}
#l3 {visibility: hidden; position: absolute; left: 130;}
#l4 {visibility: hidden; position: absolute; left: 130;}
#l5 {visibility: hidden; position: absolute; left: 130;}
#l6 {visibility: hidden; position: absolute; left: 130;}
</style>

<table class=border cellPadding=0 cellSpacing=0 width=100%>
<tr><td class=b align=center height=17>Выбор картинки</td></tr>
<tr><td>
<table cellspacing=0 cellpadding=1 border=0 width=100%>

<tr>
<td width=100>
<a href="#" onclick="return ch(this,1);" name=main>Основные</a><br>
<a href="#" onclick="return ch(this,2);">Смайлики</a><br>
<a href="#" onclick="return ch(this,3);">Действия</a><br>
<a href="#" onclick="return ch(this,4);">Страшилки</a><br>
<a href="#" onclick="return ch(this,5);">Животные</a><br>
<a href="#" onclick="return ch(this,6);">Другое</a><br>
</td>

<td>

<div id=l1>
<a href="#" onclick="return sp(1)"><img src="/pics/s/sp1.gif"></a>
<a href="#" onclick="return sp(2)"><img src="/pics/s/sp2.gif"></a>
<a href="#" onclick="return sp(3)"><img src="/pics/s/sp3.gif"></a>
<a href="#" onclick="return sp(4)"><img src="/pics/s/sp4.gif"></a>
<a href="#" onclick="return sp(5)"><img src="/pics/s/sp5.gif"></a>
<a href="#" onclick="return sp(6)"><img src="/pics/s/sp6.gif"></a>
</div>

<div id=l2>
<a href="#" onclick="return sp(111)"><img src="/pics/s/sp111.gif"></a>
<a href="#" onclick="return sp(91)"><img src="/pics/s/sp91.gif"></a>
<a href="#" onclick="return sp(16)"><img src="/pics/s/sp16.gif"></a>
<a href="#" onclick="return sp(19)"><img src="/pics/s/sp19.gif"></a>
<a href="#" onclick="return sp(17)"><img src="/pics/s/sp17.gif"></a>
<a href="#" onclick="return sp(20)"><img src="/pics/s/sp20.gif"></a>
<a href="#" onclick="return sp(119)"><img src="/pics/s/sp119.gif"></a>
<a href="#" onclick="return sp(21)"><img src="/pics/s/sp21.gif"></a>
<a href="#" onclick="return sp(120)"><img src="/pics/s/sp120.gif"></a>
<a href="#" onclick="return sp(117)"><img src="/pics/s/sp117.gif"></a>
<a href="#" onclick="return sp(68)"><img src="/pics/s/sp68.gif"></a>
<a href="#" onclick="return sp(79)"><img src="/pics/s/sp79.gif"></a>
<a href="#" onclick="return sp(25)"><img src="/pics/s/sp25.gif"></a>
<a href="#" onclick="return sp(10)"><img src="/pics/s/sp10.gif"></a>
<a href="#" onclick="return sp(39)"><img src="/pics/s/sp39.gif"></a>
<a href="#" onclick="return sp(40)"><img src="/pics/s/sp40.gif"></a>
<a href="#" onclick="return sp(42)"><img src="/pics/s/sp42.gif"></a>
<a href="#" onclick="return sp(50)"><img src="/pics/s/sp50.gif"></a>
<a href="#" onclick="return sp(51)"><img src="/pics/s/sp51.gif"></a>
<a href="#" onclick="return sp(52)"><img src="/pics/s/sp52.gif"></a>
<a href="#" onclick="return sp(53)"><img src="/pics/s/sp53.gif"></a>
<a href="#" onclick="return sp(54)"><img src="/pics/s/sp54.gif"></a>
<a href="#" onclick="return sp(55)"><img src="/pics/s/sp55.gif"></a>
<a href="#" onclick="return sp(56)"><img src="/pics/s/sp56.gif"></a>
<a href="#" onclick="return sp(57)"><img src="/pics/s/sp57.gif"></a>
<a href="#" onclick="return sp(58)"><img src="/pics/s/sp58.gif"></a>
<a href="#" onclick="return sp(59)"><img src="/pics/s/sp59.gif"></a>
<a href="#" onclick="return sp(60)"><img src="/pics/s/sp60.gif"></a>
<a href="#" onclick="return sp(61)"><img src="/pics/s/sp61.gif"></a>
<a href="#" onclick="return sp(62)"><img src="/pics/s/sp62.gif"></a>
<a href="#" onclick="return sp(63)"><img src="/pics/s/sp63.gif"></a>
<a href="#" onclick="return sp(64)"><img src="/pics/s/sp64.gif"></a>
<a href="#" onclick="return sp(65)"><img src="/pics/s/sp65.gif"></a>
<a href="#" onclick="return sp(116)"><img src="/pics/s/sp116.gif"></a>
<a href="#" onclick="return sp(67)"><img src="/pics/s/sp67.gif"></a>
<a href="#" onclick="return sp(69)"><img src="/pics/s/sp69.gif"></a>
<a href="#" onclick="return sp(72)"><img src="/pics/s/sp72.gif"></a>
<a href="#" onclick="return sp(74)"><img src="/pics/s/sp74.gif"></a>
<a href="#" onclick="return sp(75)"><img src="/pics/s/sp75.gif"></a>
<a href="#" onclick="return sp(70)"><img src="/pics/s/sp70.gif"></a>
</div>

<div id=l3>
<a href="#" onclick="return sp(24)"><img src="/pics/s/sp24.gif"></a>
<a href="#" onclick="return sp(13)"><img src="/pics/s/sp13.gif">
<a href="#" onclick="return sp(9)"><img src="/pics/s/sp9.gif"></a>
<a href="#" onclick="return sp(12)"><img src="/pics/s/sp12.gif"></a>
<a href="#" onclick="return sp(11)"><img src="/pics/s/sp11.gif"></a>
<a href="#" onclick="return sp(46)"><img src="/pics/s/sp46.gif"></a>
<a href="#" onclick="return sp(32)"><img src="/pics/s/sp32.gif"></a>
<a href="#" onclick="return sp(134)"><img src="/pics/s/sp134.gif"></a>
<a href="#" onclick="return sp(136)"><img src="/pics/s/sp136.gif"></a>
<a href="#" onclick="return sp(44)"><img src="/pics/s/sp44.gif"></a>
<a href="#" onclick="return sp(47)"><img src="/pics/s/sp47.gif"></a>
<a href="#" onclick="return sp(66)"><img src="/pics/s/sp66.gif"></a>
<a href="#" onclick="return sp(7)"><img src="/pics/s/sp7.gif"></a>
<a href="#" onclick="return sp(41)"><img src="/pics/s/sp41.gif"></a>
<a href="#" onclick="return sp(22)"><img src="/pics/s/sp22.gif"></a>
<a href="#" onclick="return sp(43)"><img src="/pics/s/sp43.gif"></a>
<a href="#" onclick="return sp(8)"><img src="/pics/s/sp8.gif"></a>
<a href="#" onclick="return sp(82)"><img src="/pics/s/sp82.gif"></a>
<a href="#" onclick="return sp(147)"><img src="/pics/s/sp147.gif"></a>
<a href="#" onclick="return sp(45)"><img src="/pics/s/sp45.gif"></a>
<a href="#" onclick="return sp(15)"><img src="/pics/s/sp15.gif"></a>
<a href="#" onclick="return sp(118)"><img src="/pics/s/sp118.gif"></a>
<a href="#" onclick="return sp(18)"><img src="/pics/s/sp18.gif"></a>
<a href="#" onclick="return sp(78)"><img src="/pics/s/sp78.gif"></a>
<a href="#" onclick="return sp(101)"><img src="/pics/s/sp101.gif"></a>
<a href="#" onclick="return sp(104)"><img src="/pics/s/sp104.gif"></a>
<a href="#" onclick="return sp(105)"><img src="/pics/s/sp105.gif"></a>
<a href="#" onclick="return sp(81)"><img src="/pics/s/sp81.gif"></a>
<a href="#" onclick="return sp(86)"><img src="/pics/s/sp86.gif"></a>
<a href="#" onclick="return sp(84)"><img src="/pics/s/sp84.gif"></a>
<a href="#" onclick="return sp(89)"><img src="/pics/s/sp89.gif"></a>
<a href="#" onclick="return sp(100)"><img src="/pics/s/sp100.gif"></a>
<a href="#" onclick="return sp(92)"><img src="/pics/s/sp92.gif"></a>
<a href="#" onclick="return sp(102)"><img src="/pics/s/sp102.gif"></a>
<a href="#" onclick="return sp(107)"><img src="/pics/s/sp107.gif"></a>
<a href="#" onclick="return sp(103)"><img src="/pics/s/sp103.gif"></a>
<a href="#" onclick="return sp(110)"><img src="/pics/s/sp110.gif"></a>
<a href="#" onclick="return sp(106)"><img src="/pics/s/sp106.gif"></a>
<a href="#" onclick="return sp(108)"><img src="/pics/s/sp108.gif"></a>
<a href="#" onclick="return sp(128)"><img src="/pics/s/sp128.gif"></a>
<a href="#" onclick="return sp(138)"><img src="/pics/s/sp138.gif"></a>
</div>

<div id=l4>
<a href="#" onclick="return sp(112)"><img src="/pics/s/sp112.gif"></a>
<a href="#" onclick="return sp(113)"><img src="/pics/s/sp113.gif"></a>
<a href="#" onclick="return sp(114)"><img src="/pics/s/sp114.gif"></a>
<a href="#" onclick="return sp(115)"><img src="/pics/s/sp115.gif"></a>
<a href="#" onclick="return sp(77)"><img src="/pics/s/sp77.gif"></a>
<a href="#" onclick="return sp(99)"><img src="/pics/s/sp99.gif"></a>
<a href="#" onclick="return sp(96)"><img src="/pics/s/sp96.gif"></a>
<a href="#" onclick="return sp(97)"><img src="/pics/s/sp97.gif"></a>
<a href="#" onclick="return sp(87)"><img src="/pics/s/sp87.gif"></a>
</div>

<div id=l5>
<a href="#" onclick="return sp(49)"><img src="/pics/s/sp49.gif"></a>
<a href="#" onclick="return sp(23)"><img src="/pics/s/sp23.gif"></a>
<a href="#" onclick="return sp(33)"><img src="/pics/s/sp33.gif"></a>
<a href="#" onclick="return sp(90)"><img src="/pics/s/sp90.gif"></a>
<a href="#" onclick="return sp(93)"><img src="/pics/s/sp93.gif"></a>
<a href="#" onclick="return sp(145)"><img src="/pics/s/sp145.gif"></a>
</div>

<div id=l6>
<a href="#" onclick="return sp(14)"><img src="/pics/s/sp14.gif"></a>
<a href="#" onclick="return sp(85)"><img src="/pics/s/sp85.gif"></a>
<a href="#" onclick="return sp(94)"><img src="/pics/s/sp94.gif"></a>
<a href="#" onclick="return sp(26)"><img src="/pics/s/sp26.gif"></a>
<a href="#" onclick="return sp(27)"><img src="/pics/s/sp27.gif"></a>
<a href="#" onclick="return sp(28)"><img src="/pics/s/sp28.gif"></a>
<a href="#" onclick="return sp(29)"><img src="/pics/s/sp29.gif"></a>
<a href="#" onclick="return sp(30)"><img src="/pics/s/sp30.gif"></a>
<a href="#" onclick="return sp(31)"><img src="/pics/s/sp31.gif"></a>
<a href="#" onclick="return sp(34)"><img src="/pics/s/sp34.gif"></a>
<a href="#" onclick="return sp(109)"><img src="/pics/s/sp109.gif"></a>
<a href="#" onclick="return sp(35)"><img src="/pics/s/sp35.gif"></a>
<a href="#" onclick="return sp(48)"><img src="/pics/s/sp48.gif"></a>
<a href="#" onclick="return sp(130)"><img src="/pics/s/sp130.gif"></a>
<a href="#" onclick="return sp(36)"><img src="/pics/s/sp36.gif"></a>
<a href="#" onclick="return sp(37)"><img src="/pics/s/sp37.gif"></a>
<a href="#" onclick="return sp(38)"><img src="/pics/s/sp38.gif"></a>
<a href="#" onclick="return sp(80)"><img src="/pics/s/sp80.gif"></a>
<a href="#" onclick="return sp(71)"><img src="/pics/s/sp71.gif"></a>
<a href="#" onclick="return sp(73)"><img src="/pics/s/sp73.gif"></a>
<a href="#" onclick="return sp(76)"><img src="/pics/s/sp76.gif"></a>
<a href="#" onclick="return sp(83)"><img src="/pics/s/sp83.gif"></a>
<a href="#" onclick="return sp(88)"><img src="/pics/s/sp88.gif"></a>
<a href="#" onclick="return sp(98)"><img src="/pics/s/sp98.gif"></a>
<a href="#" onclick="return sp(133)"><img src="/pics/s/sp133.gif"></a>
<a href="#" onclick="return sp(122)"><img src="/pics/s/sp122.gif"></a>
<a href="#" onclick="return sp(121)"><img src="/pics/s/sp121.gif"></a>
<a href="#" onclick="return sp(123)"><img src="/pics/s/sp123.gif"></a>
<a href="#" onclick="return sp(148)"><img src="/pics/s/sp148.gif"></a>
<a href="#" onclick="return sp(149)"><img src="/pics/s/sp149.gif"></a>
<a href="#" onclick="return sp(150)"><img src="/pics/s/sp150.gif"></a>
</div>

</td>
</tr>
</table>

<script>
ch(document.getElementById('main'),1);
</script>

</td></tr>
</table>

<!--/html-->