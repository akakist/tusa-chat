<body>
<style>
.lft {font-weight:bold;text-align:right;padding:4px;}
.rt {text-align:right;} 
td{text-align:left;}
</style>

<div class='first-line'>Лучшие игроки чата с 1 января 2010 года</div>
<p>
<div style='margin-left:11px'>

<table cellspacing=1 cellpadding=3 border=0 width=80%>
<tr width=60%>
<td align=center colspan=3>
<b><center><big>Топ 50 викторины</big></b><td>
<td align=center colspan=6>
<b><center><big>Топ 50 игроков в мафию</big></center></b><td></tr>
<tr><td><b>##</td><td><b>Ник</td><td><b>Ответов</td><td>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp</td>
<td><b>##</td> <td><b>Ник</td> <td><b>Очков</td> <td><b>Играл(а)</td> <td><b>Выигрышей</td> <td><b>Проигрышей</b></td>
<?
    $quiz=mysql_query("
	SELECT login,SUM(score) AS val FROM(
	SELECT login,score from quiz_all_score
        UNION ALL SELECT login,score from quiz_rating ) AS u
        GROUP BY login ORDER by val desc limit 50          ") or die(mysql_error());
    $mafia=mysql_query("
	SELECT login,SUM(win),SUM(loose),SUM(score) AS val FROM(
	SELECT login,win,loose,score from mafia_all_score
        UNION ALL 
        SELECT login,win,loose,score from mafia_score ) AS u
        GROUP BY login ORDER by val desc limit 50          ") or die(mysql_error());


    for ($i=1;$i<51;$i++)  {
	$row=mysql_fetch_row($quiz);
	$row1=mysql_fetch_row($mafia);
	list($last,$tid)=mysql_select1row(" select last_nick,id from tbl_users where login='$row[0]'");
	list($last1,$tid1)=mysql_select1row(" select last_nick,id from tbl_users where login='$row1[0]'");
	$ss=$row1[1]+$row1[2];

	echo "<tr><td class=rt>$i</td><td>
	<a href='chat_userinfo2.php?id=$tid' target=_blank>$last</a></td>
	<td class=rt>$row[1]</td>
	<td></td>
	<td class=rt>$i</td>
	<td><a href='chat_userinfo2.php?id=$tid1' target=_blank>$last1</a></td>
	<td class=rt>$row1[3]</td>
	<td class=rt>$ss</td>
	<td class=rt>$row1[1]</td>
	<td class=rt>$row1[2]</td></tr>";  

}
?>

</table>
</div>
</body>
