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
    <div class='first-line'>Лучшие игроки чата</div>
    <p>
    <div style='margin-left:100px'>

<table cellspacing=1 cellpadding=1 border=0>
<tr>
<td align=center>
<b>Топ 50 викторины</b><br><br>
<table border=0 cellpadding=2>
<tr><td>##</td><td>Ник</td><td>Ответов</td>
<?
    $quiz=mysql_query("
	SELECT login,SUM(score) AS val FROM(
	SELECT login,score from quiz_all_score
        UNION ALL SELECT login,score from quiz_rating ) AS u
        GROUP BY login ORDER by val desc limit 50          ") or die(mysql_error());
    for ($i=1;$row=mysql_fetch_row($quiz);$i++)  {
	list($last,$tid)=mysql_select1row(" select last_nick,id from tbl_users where login='".mysql_escape_string($row[0])."'");
	echo "<tr><td class=rt>$i</td><td>
	<a href='chat_userinfo2.php?id=$id' target=_blank>$last</a></td>
	<td class=rt>$row[1]</td></tr>";  }

/*
    $ar=preg_split("/\;/",$m['topmess']);
    $i=1;
    foreach($ar as $it)
    {
	list($last_nick_id,$last_nick,$stat_m_count,$id)=split(":",$it);
	echo "<tr><td class=rt>$i</td><td><a href='chat_userinfo2.php?id=$id' target=_blank>$last_nick</a></td><td class=rt>$stat_m_count</td>";
	$i++;
    }
*/


?>

</table>
<td align=center>
<br>
<b>Топ 50 игроков в мафию</b><br>
<table border=0 cellpadding=2>
<td>##</td> <td>Ник</td> <td>Очков</td> <td>Играл(а)</td> <td>Выигрышей</td> <td>Проигрышей</td>
<br>
<br>
<?

    $mafia=mysql_query("
	SELECT login,SUM(win),SUM(loose),SUM(score) AS val FROM(
	SELECT login,win,loose,score from mafia_all_score
        UNION ALL 
        SELECT login,win,loose,score from mafia_score ) AS u
        GROUP BY login ORDER by val desc limit 50          ") or die(mysql_error());
    for ($i=1;$row=mysql_fetch_row($mafia);$i++)  {
	$ss=$row[1]+$row[2];
	list($last,$tid)=mysql_select1row(" select last_nick,id from tbl_users where login='".mysql_escape_string($row[0])."'");
	echo "<tr><td class=rt>$i</td>
	<td><a href='chat_userinfo2.php?id=$id' target=_blank>$last</a>	</td>
	<td class=rt>$row[3]</td>
	<td class=rt>$ss</td>
	<td class=rt>$row[1]</td>
	<td class=rt>$row[2]</td></tr>";  }




/*

    $ar=preg_split("/\;/",$m['tophour']);
    $i=1;
    foreach($ar as $it)
    {
	list($last_nick_id,$last_nick,$stat_m_count,$id)=split(":",$it);
	echo "<tr><td class=rt>$i</td><td><a href='chat_userinfo2.php?id=$id' target=_blank>$last_nick</a></td><td class=rt>$stat_m_count</td>";
	$i++;
    }
*/
?>

</table>

</td>
</tr>
</table>
    
    </div>