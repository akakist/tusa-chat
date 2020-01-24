
<div class='first-line'>Фотки</div>
<?
list($main_foto_thumb_small,$main_foto_thumb_big,$has_main_foto)=mysql_select1row("select foto_thumb_small,foto_thumb_big,has_main_foto from tbl_users where id='$uid'");
?>
<fieldset>
	<legend>Фотки</legend> 
	<div style='float:left; width:300px'>
	<form method="post" name="form1" enctype="multipart/form-data">
		 <input type=hidden name='MAIN' value='1'>

		<table>
		<tr>
			<td>Oписание:</td>
			<td class=r><div id='desc'><input type=text name=descr></div></td>
		</tr>
		<tr>
			<td><input type=checkbox name='ismain' onchange='if(this.checked)$("#desc").hide();else $("#desc").show()'></td>
			<td class=r>как главную</td>
		</tr>

		<tr>
			<td colspan=2><input type='file' name='foto'></td>
		</tr>
		<tr>
			<td colspan=2><input type="submit" value="Загрузить" name="reg"></td>
		</tr>
		</table>
		 
	</form>
	</div>
		 
	<div style='left:100px'>
	<b>Главная фотка</b><p>
			<?
			if($has_main_foto)
			{
			?>
			<form method=post>
				<input type=hidden name='rmmain' value=1>
				<input type=submit value='Удалить главную'>
			</form>
			<?
			}
			?>
			
		<p>
		<div class="highslide-gallery">
			<a href="<?=$main_foto_thumb_big?>" class="highslide" onclick="return hs.expand(this)">
				<img src="<?=$main_foto_thumb_small?>" alt="Фотка" title="Нажмите посмареть" /> <!--"<??> "'-->
			</a>
			<div class="highslide-caption">	Моя главная фотка.</div>
		</div>
	</div>
	<div class='second-line' style='margin-top:10px'>другие фотки</div>
	 


	<p>
	<div class="highslide-gallery">
	<?
		$result=mysql_query("select id,url_thumb_small, url_scaled ,url_host,descr from photos where uid='$uid' order by id") or die(mysql_error());
		while($row=mysql_fetch_row($result))
		{
			$pid=$row[0];
			$url_thumb_small=$row[1];
			$url_scale=$row[2];
			$url_host=$row[3];
			$descr=mysql_escape_string($row[4]);
			$url_s=$url_host.$url_thumb_small;
			$url_e=$url_host.$url_scale;
			?>
				<div style='float: left;padding-bottom:5px;' id='ph<?=$pid?>' class=photolist>
				<a href='<?=$url_e?>' class='highslide' onclick="return hs.expand(this)">
					<img border=0 src='<?=$url_s?>' title="<?=$descr?>"> <!--'<??> '-->
				</a> 
				<div class="highslide-caption">	<?=$descr?></div>
				
				<span class='cross'>
					<a href='#' onclick='return move_to_trash(<?=$pid?>);'>
					<img class='rmimg' src='/pics/del.gif' alt='Удалить фотку' style='position: relative; left: -10px'>
					</a>
				</span> &nbsp;
				</div>
			<?
	
		}
	?>
	</div>

	 <div id='trash' style="width: 100%; display: none; clear:left;margin-top:5px;margin-bottom:5px;">
		 <form name='frem' method=post>
		 	
			 <input type=hidden name=remf>
			 <div class='second-line'> Помойка</div>
			 <p style='line-height:10px'></p>
			 <input type=submit value='Удалить фотки' onclick="return on_remove();"><p style='line-height:10px'></p>
		 </form>
	 </div>
</fieldset>
<?
	if(isset($_SESSION["rega"])) $title='Продолжить';
	else $title='Назад';
?>
<input type=button onclick='window.location="/c2/url_login.php"' value="<?=$title?>" class=b_l>
