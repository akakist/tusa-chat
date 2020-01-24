
<?
if(isset($arg_add))
{
?>

	<div class='first-line'><a href=/c2/forum/forum.php>Форум</a>/Добавить тему</div>
	<?
	if(isset($error))echo "<div class='error'>$error</div>";
	?>
	<form method=post onsubmit="return chk_add();" name=f>
	От:<br>
	<?=nick_select($uid);?>
	<br>
	Тема:<br>
	<input type=textfield style='width: 400px' maxlength=64 name="ta">
	<input type=hidden name="add" value="1">
	<input type=hidden name="data" value="1">
	<br><br>
	Первое сообшение:<br>
	<textarea style='width: 400px' rows=8 cols=40 name="msg" maxlength=10240></textarea><br>
	<input type=submit value="Добавить тему">
	</form>
		
	<?
//	die;
} //arg_add
else
{
 
 ?>
	<!--table width="100%" border="0" cellspacing="0" cellpadding="0"-->
	<?
	$out="";
	?>
 <?
 		$start=0;
		
		if(isset($arg_s)) $start=intval($arg_s);
		if(!isset($arg_t))
		{
			$tsize=mysql_select1("select count(*) from Forum_themes");
		}
		else
		{
			$arg_t=intval($arg_t);
			list($tsize,$tname)=mysql_select1row("select msgcnt,name from Forum_themes where id='$arg_t'");
		}	
		$page=0;
		$npages=ceil($tsize/$FORUM_MSG_PER_PAGE);
		if(isset($arg_s))
		{
//			$arg_s=intval($arg_s);
			$page=floor($arg_s/$FORUM_MSG_PER_PAGE);
		}

		$select_page_down=select_page(isset($arg_t)?$arg_t:0,$tsize,$page,$FORUM_MSG_PER_PAGE);

		if(isset($arg_t))
		{
//			$arg_t=intval($arg_t);
			$fresh=-1;
			if($start>0)$fresh=$start-$FORUM_MSG_PER_PAGE;
			if($fresh<0)$fresh=0;
			$old=-1;
			if($start+$FORUM_MSG_PER_PAGE<$tsize)$old=$start+$FORUM_MSG_PER_PAGE;
			$fresh_t="";
			$old_t="";
			if($fresh>=0 && $start!=0)$fresh_t="<a href='/c2/forum/forum.php?t=$arg_t&s=$fresh'>&lt;&lt;Свежие сообщения</a>";
			if($old>=0)$old_t="<a href='/c2/forum/forum.php?t=$arg_t&s=$old'>Старые сообщения&gt;&gt;</a>";
			$npages=floor($tsize/$FORUM_MSG_PER_PAGE);
		}
		else
		{
			$fresh=-1;
			if($start>0)$fresh=$start-$FORUM_MSG_PER_PAGE;
			if($fresh<0)$fresh=0;
			$old=-1;
			if($start+$FORUM_MSG_PER_PAGE<$tsize)$old=$start+$FORUM_MSG_PER_PAGE;
			$fresh_t="";
			$old_t="";
			if($fresh>=0 && $start!=0)$fresh_t="<a href='/c2/forum/forum.php?s=$fresh'>&lt;&lt;Свежие темы</a>";
			if($old>=0)$old_t="<a href='/c2/forum/forum.php?s=$old'>Старые темы&gt;&gt;</a>";
			$npages=floor($tsize/$FORUM_MSG_PER_PAGE);
		}	
				 

		?>
	<div class='first-line'><a href=/c2/forum/forum.php>Форум</a> <?if(isset($arg_t)) echo "/ <a href='/c2/forum/forum.php?t=$arg_t'>$tname</a>";?>	</div>
	<div style='text-align:center; padding:10px'>
		<div style='float:left'><?=$fresh_t?></div><span style='text-align:center;width:200px'>Страница <?=$select_page_down?> из <?=$npages+1?></span><div style='float:right'><?=$old_t?></div>
	</div>
		
	 

	 
	 <?
	 
	 	if(!isset($arg_t))
		{
		 	$result=mysql_query("select add_date,id,name,msgcnt,last_by,author from Forum_themes order by add_date desc limit $start,$FORUM_MSG_PER_PAGE") or die(mysql_error());
			
			if(mysql_num_rows($result))
			{

				echo '<table class="tbl-themes" cellspacing=2 cellpadding=1 border=0 width="100%">';
		 		while (list($add_date,$tid,$name,$cnt,$last_by,$author)=mysql_fetch_row($result)){
					?>
					<tr>	
						<td width=100% class=trd><a href=/c2/forum/forum.php?t=<?=$tid?> > <?=$name?></a> <small>(<?=$cnt?> - 
							<a class=nick href=# onclick="return ui('<?=$last_by?>');"><?=$last_by?></a> <?=get_rusdate($add_date)." ".get_time($add_date)?>)</small></td> 
						<td width=150 class=trd><a class=nick href=# onclick="return ui('<?=$author?>')"><small><?=$author?></small></a></td> <!--'<??> '-->
					</tr>
					<?
				}
				echo '</table>';
			}
			else
			{
			?>
				<h1>Тем нету. Создавайте..</h1>
			<?
			}
			
		}
		else // arg_t
		{
			$arg_t=intval($arg_t);
		 	$result=mysql_query("select id,ip,add_date,author,subj,msg,nid,uid from Forum_messages where tid='$arg_t' order by add_date desc limit $start,$FORUM_MSG_PER_PAGE") or die(mysql_error());
			if(mysql_num_rows($result))
			{
			
		 		while (list($mid,$mip,$add_date,$author,$subject,$msg)=mysql_fetch_row($result)){
					
				echo "<div id='d$mid'>";
					?>
					
					<a name=<?=$mid?>></a>
					<div style="float:left">
					<i><?=get_rusdate($add_date)." ".get_time($add_date)?></i>
								<?if(isset($_SESSION['privs']['forum']))echo " <small>($mip)</small>"?>
					</div>		
					<div style='float:right'>
					<a title='Ответить' href=# onclick="return d_r(<?=$mid?>)">
								<img src=/pics/reply.gif border=0 width=16 height=16 alt='Ответить'></a> 
								<?
								if(isset($_SESSION['privs']['forum']))
								echo 	"<a  title='Удалить' href='#' onclick=\" if(confirm('Точно удалить?'))remove_msg($mid);return false;\">
									<img src=/pics/del.gif width=16 height=16 border=0 alt='Удалить сообщение' >
									</a>";
								?>								
					</div>
					<p>
					<div style='clear: right'>
						<a href=# onclick="return ui('<?=$author?>')"><!--'<??> '--><font class=nick id='au<?=$mid?>'><?=$author?></font></a>: <b><span id=s<?=$mid?>> <?=$subject?></span></b>
						
					</div>
					<div id="b<?=$mid?>" class='forum-msg'><?=format_msg($msg)?></div> <!--"<??> "-->
					<div id="bex<?=$mid?>" style='display: none'><?=$msg?></div>
					

					<?
				echo '</div>';
				}
				
			}
			else
			{
			?>
				<!--h1>Сообщений нет. Создавайте..</h1-->
			<?
			}
			?>
			<hr>
			<a name="add"></a>
			Добавить сообшение:<br>
			<form method=post name=f onsubmit="return chk_f()">
				<input type=hidden name="addmsg" value="1">
				<input type=hidden name="tid" value="$tid">
				От: <br>
				<?=nick_select($uid)?>
			<br>

			<br>
			Тема:<br>
			<input style='width: 400px' type=text name="subj" maxlength=100><br>
			<textarea style='width: 400px' rows=8 cols=40 maxlength=10000 name="msg"></textarea><br>
			<input type=submit value="Добавить сообшение" name=smt>
			</form>
			<?
			if(isset($adm))
			{
				?>
				<div style="float:right"><a href="/c2/forum/forum.php?t=<?=$arg_t?>&rmth=1" onclick="return confirm('Точно удалить тему?')">Удалить тему</a></div>
				<?
				
			}
			?>
	 	<?
		}
	 ?>
<?
}
?>