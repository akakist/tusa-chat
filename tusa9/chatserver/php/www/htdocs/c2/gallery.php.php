<div class='first-line'>Галерея</div>
<style>
/*p{text-height:20px}*/
</style>
	<p>&nbsp;</p>
	<form method=get   name=f>

		Поиск по нику: (введите весь или несколько букв от требуемого ника, ищется максимум 100 ников)<br>
		<p style='text-height:20px'>&nbsp;</p>
		<?
			$ds="";
			if(isset($arg_s)) $ds=$arg_s;
			else if(isset($arg_n))
			{
			$arg_n = intval($arg_n);
				$ds=mysql_select1("select nick from nicks where id='$arg_n'");
			}
		?>
		<input type=textfield name="s" maxlength=16 size=16 value="<?=$ds?>">  
		&nbsp;<input type=submit value="Искать"></td></tr>
 <!--"<??> " -->

	</form>


<br>
<div>
<?
	$adm=$_SESSION['level']>=800;
        include "inc/date.php";
	include "inc/make_user_info.php";
	require_once('inc/str_nick.php');

	if(isset($arg_s))
	{
	    $l=0;
	    if(isset($arg_l))$l=$arg_l;
	    $sql="select a.id,a.uid,a.nick from nicks a, tbl_users b  where a.nick like '$arg_s%' and a.banned=0 and a.uid<>0 and b.id=a.uid order by a.str_nick limit 100";
	    $res=mysql_query($sql);
	    if(!$res){  echo mysql_error();}
	    $nrows=mysql_num_rows($res);
	    echo "<center>Найдено: $nrows<p><div style='height:20px'></div>";
    	    $d="";
	    if($nrows>0)
	    {
	            $r=1;
        	    while($row=mysql_fetch_row($res))
	            {
        	            if ($r==1){
	                        $d.="<tr>";
        	            }
                	    $id=$row[0];
	                    $nick=$row[2];
                	    $d.="<td height=20 align=center><a href='/c2/gallery.php?n=$id' class=nia>$nick</a></td>\n";
	                    if ($r==3){
			    	$r=0;
 //       	                $d."</tr>";
	                    }   	
                	    $r++;
        	    
	            }
	    }

		$d=     "<table border=0 width=30%>".$d."</table>";
		echo $d;
	    
	}
	
	if(isset($arg_n))
	{
		$arg_n = preg_replace ("/[^0-9]/", "", $arg_n);
		$arg_n = (isset($arg_n)) ? intval($arg_n) : 0;
		$nout="";
		echo "<tr><td><table>\n".make_user_info($arg_n,$adm)."</table></td></tr>\n";
	//	$d="".make_user_info($arg_n,$adm)."";
		$zid=mysql_select1("select uid from nicks where id=$arg_n");
//		echo $d;
	}
?>
</div>

<?
	if(isset($d))
	{
//		echo "<table border=0 width=100%>";
//		echo $d;
//		echo "</table>";
	}
?>

<?
if(isset($arg_n))
{
	$arg_n = preg_replace ("/[^0-9]/", "", $arg_n);
	$arg_n = (isset($arg_n)) ? intval($arg_n) : 0;
//	$arg_n = intval($arg_n);
	?>
	<div id='phot'>
	<center>
	<div class="highslide-gallery">
	

	<?
		$result=mysql_query("select id,url_thumb_small, url_scaled ,url_host,descr from photos where uid='$zid' order by id") or die(mysql_error());
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
				
				<?
				if(isset($_SESSION['privs']['photo']))
				{
				?>
				<span class='cross'>
					<a href='#' onclick='return move_to_trash(<?=$pid?>);'>
					<img class='rmimg' src='/pics/del.gif' alt='Удалить фотку' title='Удалить фотку' style='position: relative; left: -10px'>
					</a>
				</span> &nbsp;
				<?
				}
				?>
				</div>
			<?
	
		}
	?>
	</div>
	<?
	if(isset($_SESSION['privs']['photo']))
	{
	?>

	 <div id='trash' style="width: 100%; display: none; clear:left;margin-top:5px;margin-bottom:5px;">
		 <form name='frem' method=post>
		 	
			 <input type=hidden name=remf>
			 <input type=hidden name=zid value=<?=intval($zid)?> >
			 <input type=hidden name=n value=<?=intval($arg_n)?> >
			 <div class='second-line'> Помойка</div>
			 <p style='line-height:10px'></p>
			 
			 <input type=submit value='Удалить фотки'><p style='line-height:10px'></p>
		 </form>
	 </div>
	<?
	}
	?>
	
	</center>
	</div>
	<?
}
?>
