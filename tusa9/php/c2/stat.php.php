<?
    $file=fopen("/tmp/chat_stat","r");
    $b=fread($file,filesize("/tmp/chat_stat"));
    $r=preg_split("/[\r\n]/",$b);
    $m=array();
    foreach($r as $l)
    {
	$p=preg_split("/\s/",$l);
	if(count($p)>=2)
	{
	    $m[$p[0]]=$p[1];
	}
//        echo $l."<br>";
    
    }
    
?>
    <style>
    .lft {font-weight:bold;text-align:right;padding:4px;}
    .rt {text-align:right;} 
    td{text-align:left;}
    </style>
    <div class='first-line'>Статистика чата</div>
    <p>
    <div style='margin-left:100px'>
    <img src=stat_image.php>
    <table>
    <tr><td class=lft>Всего сообщений написано</td><td><?=$m['allmsg']?></td></tr>
    <tr><td class=lft>Всего часов просижено</td><td><?=$m['allhours']?></td></tr>
    <tr><td class=lft>Зарегистрированных пользователей</td><td><?=$m['allusers']?></td></tr>
    <tr><td class=lft>Зарегистрированных ников</td><td><?=$m['allnicks']?></td></tr>
    <tr><td class=lft>Зарегистрированo сегодня</td><td><?=$m['regtoday']?></td></tr>
    <tr><td class=lft>Зарегистрированo вчера</td><td><?=$m['regyestoday']?></td></tr>
    <tr><td class='lft' style='text-decoration: underline' colspan=2 width=100%>Статистика по уровням</td></tr>
    <tr><td class=lft>Новых пользователей</td><td><?=$m['newusers']?></td></tr>
    <tr><td class=lft>Пользователей</td><td><?=$m['users']?></td></tr>
    <tr><td class=lft>Чаттеров</td><td><?=$m['chatters']?></td></tr>
    <tr><td class=lft>Тусовщиков</td><td><?=$m['tus']?></td></tr>
    <tr><td class=lft>VIP'ов</td><td><?=$m['vips']?></td></tr>
    <tr><td class=lft>Киллеров и выше</td><td><?=$m['adm']?></td></tr>
    
    </table><p>
<table cellspacing=1 cellpadding=1 border=0>
<tr>
<td align=center>
<b>Топ 50 по кол-ву сообщений</b><br><br>
<table border=0 cellpadding=2>
<tr><td>##</td><td>Ник</td><td>Сообщений</td></tr>
<?
    $ar=preg_split("/\;/",$m['topmess']);
    $i=1;
    foreach($ar as $it)
    {
	list($last_nick_id,$last_nick,$stat_m_count,$id)=split(":",$it);
	echo "<tr><td class=rt>$i</td><td><a href='chat_userinfo2.php?id=$id' target=_blank>$last_nick</a></td><td class=rt>$stat_m_count</td>";
	$i++;
    }
?>

</table>

</td>
<td align=center>
<b>Топ 50 по кол-ву часов</b><br><br>
<table border=0 cellpadding=2>
<tr><td>##</td><td>Ник</td><td>Время</td></tr>
<?
    $ar=preg_split("/\;/",$m['tophour']);
    $i=1;
    foreach($ar as $it)
    {
	list($last_nick_id,$last_nick,$stat_m_count,$id)=split(":",$it);
	echo "<tr><td class=rt>$i</td><td><a href='chat_userinfo2.php?id=$id' target=_blank>$last_nick</a></td><td class=rt>$stat_m_count</td>";
	$i++;
    }
?>

</table>

</td>
</tr>
</table>
    
    </div>