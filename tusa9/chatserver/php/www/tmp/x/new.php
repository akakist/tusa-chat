
<HTML>
<HEAD>
<META HTTP-EQUIV="PRAGMA" CONTENT="no-cache">
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=windows-1251">
<TITLE>Чат "Тусовка"</TITLE>
<LINK href="/c2/css/reset.css" rel=stylesheet type=text/css>
<LINK href="/css/main.css" rel=stylesheet type=text/css>
</HEAD>

<script type="text/javascript" src="/js/jquery.pack.js"></script>

<script>
var butt_size=60;
var console_size=50;
function resize()
{
var sw=document.body.clientWidth;
var sh=document.body.clientHeight;
$('#buttons').css('height',butt_size);
$('#messages').css('width',sw-200);
$('#users').css('width',200);
$('#messages').css('height',sh-butt_size-console_size);
$('#users').css('height',sh-butt_size-console_size);
$('#console').css('height',console_size);

return true;

}
</script>

<body style='margin:0; padding:0;' onresize="return resize();" onload="return resize();">
<div id='buttons' style='height:60px; border: 1px solid black; margin:0; padding:0;border-collapse: collapse;'>
buttons
</div>
<div id='messages' style='float:left;border: 1px solid black; border-collapse: collapse;'>messages</div>
<div id='users' style='float:right;border: 1px solid black; border-collapse: collapse;'>users</div>
<div id='console' style='border: 1px solid black; border-collapse: collapse;'>console</div>

<!--iframe src="1.html" style='position: absolute; left:-100;top:-100:width:2;height:2;' frameborder=0>~nusr~</iframe-->
</body>