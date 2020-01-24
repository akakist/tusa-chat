<?
	session_start();
        import_request_variables("gp", "arg_");
	
	include "inc/conf.php";
	include "inc/db_conn.php";
	include "inc/date.php";
	include "inc/split_long.php";
	include "inc/remove_maty.php";
	include "inc/remove_tags.php";
	include "inc/set_font.php";
	include "inc/replace_links.php";
	check_conn();
	$forum=1;
     if(isset($_SESSION['login']))
     {
     	$login=$_SESSION['login'];
	$uid=$_SESSION['uid'];
	
     }
     if(!isset($login))
     {
     	header("Location: /");
	exit(0);
     }
     if(isset($arg_add) && isset($arg_data))
     {
		$nid=intval($arg_nick);
		$nick=mysql_select1("select nick from nicks where id='$nid'");
	     	$ip=$_SERVER['REMOTE_ADDR'];
		$msgc=0;
		if(strlen($arg_msg))$msgc=1;

            	$arg_ta=remove_maty(split_long($arg_ta));
           	if(!isset($_SESSION['privs']['tags'])) $arg_ta=remove_tags($arg_ta);
            	$arg_ta=replace_links($arg_ta);
		$arg_ta=preg_replace("/[\n\r]+/","",$arg_ta);


     	mysql_query("insert into Forum_themes (author,name,nid,uid,ip,add_date,create_date,msgcnt,last_by,last_by_id)
                                 values('$nick','$arg_ta','$nid','$uid','$ip',NOW(),NOW(),'$msgc','$nick','$nid')") or die(mysql_error());
	 $tid=mysql_select1("select last_insert_id()");

            	$arg_msg=remove_maty(split_long($arg_msg));
           	if(!isset($_SESSION['privs']['tags'])) $arg_msg=remove_tags($arg_msg);
            	$arg_msg=replace_links($arg_msg);
		$arg_msg=preg_replace("/[\n\r]+/","<BR>",$arg_msg);
		$_SESSION['last_nick']=$nick;
		$_SESSION['last_nick_id']=$nid;
		if($tid)
		{
			$nick=mysql_escape_string($nick);
			$arg_msg=mysql_escape_string($arg_msg);
			$ip=$_SERVER['REMOTE_ADDR'];
			$sql="insert into Forum_messages (author,subj,tid,nid,uid,ip,add_date,msg) values('$nick','','$tid','$nid','$uid','$ip',NOW(),'$arg_msg') ";
                        mysql_query($sql) or die(mysql_error());

                }

	header("Location: /forum/forum.php");

     }

// 	if(isset($arg_addmsg) && isset($arg_t))
 //	{
//		$arg_t=intval($arg_t);
  // 	    header("Location: /forum/forum.php?t=$arg_t");
//	    exit();
 //	}

	
	if(isset($_SESSION['privs']['forum']))
	{
		$adm=1;
	}
	if(isset($arg_rmth) && isset($arg_t))
	{
		$arg_t=intval($arg_t);
            mysql_query(sprintf("delete from Forum_messages where tid='%d'",$arg_t)) or die(mysql_error());
            mysql_query(sprintf("delete from Forum_themes where id='%d'",$arg_t)) or die(mysql_error());
     	    header("Location: /forum/forum.php");
	
	}
	if(isset($arg_addmsg) && isset($arg_t))
	{
		$arg_t=intval($arg_t);
            	$arg_msg=remove_maty(split_long($arg_msg));
            	$arg_subj=remove_maty(split_long($arg_subj));
            	
            	if(!isset($_SESSION['privs']['tags'])) $arg_msg=remove_tags($arg_msg);
            	if(!isset($_SESSION['privs']['tags'])) $arg_subj=remove_tags($arg_subj);
            	$arg_msg=set_font($arg_msg);
            	$arg_msg=replace_links($arg_msg);
		$arg_msg=preg_replace("/[\n\r]+/","<BR>",$arg_msg);
		$nid=intval($arg_nick);
		$nick=mysql_select1("select nick from nicks where id='$nid'");
		$_SESSION['last_nick']=$nick;
		$_SESSION['last_nick_id']=$nid;
		$arg_t=intval($arg_t);
		$tid=mysql_select1("select id from Forum_themes where id='$arg_t'");
		if($tid)
		{
			$nick=mysql_escape_string($nick);
			$arg_subj=mysql_escape_string($arg_subj);
			$arg_msg=mysql_escape_string($arg_msg);
			$ip=$_SERVER['REMOTE_ADDR'];
			$sql="insert into Forum_messages (author,subj,tid,nid,uid,ip,add_date,msg) values('$nick','$arg_subj','$arg_t','$nid','$uid','$ip',NOW(),'$arg_msg') ";
                        mysql_query($sql);
                        mysql_query(sprintf("update Forum_themes set msgcnt=msgcnt+1, add_date=NOW(),last_by='$nick' where id='%d'",$arg_t));
                }
   	    header("Location: /forum/forum.php?t=$arg_t");
	    exit();
	}


  ?>
<html>
<head>
  <meta http-equiv="PRAGMA" content="no-cache">
  <meta http-equiv="Content-Type" content="text/html; charset='windows-1251'">

  <title>Чат "Тусовка"</title>
  <link rel="stylesheet" type="text/css" href="/css/main.css">
	<script language="javascript" src="/css/mmove.js" type="text/javascript"></script>
	<script type="text/javascript" src="/js/jquery.pack.js"></script>
  
</head>
<?
	if(!isset($arg_rmth) && !isset($arg_addmsg))
	{
?>

<script>
js2=false;
</script>
<script language="JavaScript1.2">
js2=true;
</script>

<script  language="javascript">
<!--
function chk_f()
{
	if(document.f.msg.value==""){
		alert('Введите сообщение');
		document.f.msg.focus();
		return false;
	}
	document.f.smt.disabled=true;
	return true;
}

function d_r(n)
{
	if(js2){
		s=document.getElementById('b'+n).innerHTML;
//
		re=/<BR>/g;	s=s.replace(re,'\r\n');
		re=/<\/A>/g;	s=s.replace(re,'');
		re=/<\/FONT>/g;	s=s.replace(re,'');
		re=/<[A,F].{1,}>/g;	s=s.replace(re,'');
		re=/&lt;/g;		s=s.replace(re,'<');
		re=/&gt;/g;		s=s.replace(re,'>');
//				alert(s);
		arr=s.split('\r\n');
		var os='';
		if(arr.length>1){
			for(i=0;i<arr.length-1;i++){
				os+='>'+arr[i]+'\r\n';
			}	
		}else{
			os='>'+s;
		}
//		alert(os);
        document.f.msg.value=os;
	}
	ms=document.getElementById('s'+n).value;
	if(ms.substr(0,3)!='Re:'){
		document.f.subj.value='Re: '+ms;
	}else{
		document.f.subj.value=ms;
	}
	document.location="#add";
	return false;
}

<?
	if(isset($adm))
	{
?>
		function remove_msg(n)
		{
			$('#d'+n).load("/forum/_remove_msg.php?n="+n);
			if(jQuery.browser.msie) location.reload();
			return false;
		}
<?
	}
?>	

//-->
</script>
<script>
<!--
uinfo=0;
function ui(ni)
{
	locat='/info/by_nick?'+ni;
	uinfo=open(locat,'fuinfo','toolbar=0,status=0,resizable=1,scrollbars=1,width=505,height=415');
	uinfo.focus();
	return false;
}
//-->
</script>

<body>

  <table border="0" width="100%" cellspacing="0" cellpadding="0">
  <?
    include 'diz/head_row.php';
  ?>

    <tr height="5">
      <td colspan="5"></td>
    </tr>

    <tr valign="top">
	<?
	    include 'diz/left_col.php';
    	?>

      <td></td>

      <td>
      <!--START-->
      <?
      if(isset($arg_add))
      {
		if(isset($error))echo "<center><font class=yelmsg><b>$error</b></font>";
      	?>
</center>
<script>
function chk_add()
{
    if (document.f.nt.value==''){
    	alert('Вы забыли ввести тему...');
        document.f.nt.focus();
        return false;
    }
    if (document.f.msg.value==''){
    	if (confirm('Вы не ввели первое сообщение. Продолжить?')) return true;
        document.f.msg.focus();
        return false;
    }
	return true;
}
</script>
<form method=post onsubmit="return chk_add();" name=f>
От:<br>
				<select name="nick">
				<?
					$nid=mysql_select1("select last_nick_id from tbl_users where id='$uid'");
					$res=mysql_query("select id,nick from nicks where uid='$uid'");
					while($r=mysql_fetch_row($res))
					{
						$id=$r[0];
						$n=$r[1];
						if($nid==$id)
						echo "<option value=$id selected> $n\n";
						else
						echo "<option value=$id> $n\n";
					}

				?>
				</select>



<br>
Тема:<br>
<input type=textfield class=ta maxlength=64 name="ta">
<input type=hidden name="add" value="1">
<input type=hidden name="data" value="1">
<br><br>
Первое сообшение:<br>
<textarea class=ta rows=8 cols=40 name="msg" maxlength=10240></textarea><br>
<input type=submit value="Добавить тему">
</form>
		
	<?
      }
      else{
      
      ?>
	<table width="100%" border="0" cellspacing="0" cellpadding="0">
	<?
	$out="";
	?>
        <?
			function select_page($t,$tsize,$page,$FORUM_MSG_PER_PAGE)
			{
				$sp="<select onchange=\"psel=this; pg=psel.options[psel.selectedIndex].value;window.location.href='/forum/forum.php?";
					  if($t) $sp.="t=$t&";
					  $sp.="s='+(pg-1)*$FORUM_MSG_PER_PAGE;\">";
					  $p=0;
					  for($i=0;$i<$tsize;$i+=$FORUM_MSG_PER_PAGE)
					  {
					  	if($i<$tsize)
						{
					  	$p++;
					  	$sp.="<option value=$p ";
						if($p-1==$page) $sp.=" SELECTED ";
						$sp.=">$p\n";
						}
					  }
				  $sp.="</select>";
				  return $sp;
				
			}
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
			$arg_s=intval($arg_s);
			$page=floor($arg_s/$FORUM_MSG_PER_PAGE);
		}

		$select_page_down=select_page(isset($arg_t)?$arg_t:0,$tsize,$page,$FORUM_MSG_PER_PAGE);

			if(isset($arg_t))
			{
				$arg_t=intval($arg_t);
				$fresh=-1;
				if($start>0)$fresh=$start-$FORUM_MSG_PER_PAGE;
				if($fresh<0)$fresh=0;
				$old=-1;
				if($start+$FORUM_MSG_PER_PAGE<$tsize)$old=$start+$FORUM_MSG_PER_PAGE;
				$fresh_t="";
				$old_t="";
				if($fresh>=0 && $start!=0)$fresh_t="<a href='/forum/forum.php?t=$arg_t&s=$fresh'>&lt;&lt;Свежие сообщения</a>";
				if($old>=0)$old_t="<a href='/forum/forum.php?$=$arg_t&s=$old'>Старые сообщения&gt;&gt;</a>";
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
				if($fresh>=0 && $start!=0)$fresh_t="<a href='/forum/forum.php?s=$fresh'>&lt;&lt;Свежие темы</a>";
				if($old>=0)$old_t="<a href='/forum/forum.php?s=$old'>Старые темы&gt;&gt;</a>";
				$npages=floor($tsize/$FORUM_MSG_PER_PAGE);
			
			}	
				  

		?>
          <tr>
            <td class="border" align="center" colspan=3><b>Форум </b></td> </tr>
	  
	  <tr><td colspan=3 align="center"><div style="padding: 5px">
	  <b><a href=/forum/forum.php>Форум</a>
	    <?
	    	if(isset($arg_t)) echo "/ <a href='/forum/forum.php?t=$arg_t'>$tname</a>";
	    ?>
	    </b></div>
	    </td></tr>

          <tr height="5"> <td colspan=3></td> </tr>
          <tr height="5"> 
                  <td width="33%" align="left"><?=$fresh_t?> 	      
		  <td width="33%">	Страница <?=$select_page_down?> из <?=$npages+1?></td>
                  <td width="33%" align="right"><?=$old_t?></td>
	  </tr>
          <tr height="15"> <td colspan=3></td> </tr>

          <tr>
            <td colspan=3>
              <center>
		
              </center>
	      
	      <?
	      
	      	if(!isset($arg_t))
		{
		      	$result=mysql_query("select add_date,id,name,msgcnt,last_by,author from Forum_themes order by add_date desc limit $start,$FORUM_MSG_PER_PAGE");
			if(mysql_num_rows($result))
			{
				echo '<table cellspacing=2 cellpadding=1 border=0 width="100%">';
		    		while ($row=mysql_fetch_row($result)){
					$add_date=$row[0];
					$tid=$row[1];
					$name=$row[2];
					$cnt=$row[3];
					$last_by=$row[4];
					$author=$row[5];
					?>
					<tr>	
						<td width=100% class=trd><a href=/forum/forum.php?t=<?=$tid?> > <?=$name?></a> <small>(<?=$cnt?> - 
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
		      	$result=mysql_query("select id,ip,add_date,author,subj,msg,nid,uid from Forum_messages where tid='$arg_t' order by add_date desc limit $start,$FORUM_MSG_PER_PAGE");
			if(mysql_num_rows($result))
			{
			
		    		while ($row=mysql_fetch_row($result)){
					$mid=$row[0];
					$mip=$row[1];
					$add_date=$row[2];
					$author=$row[3];
					$subject=$row[4];
					$msg=$row[5];
				echo "<div id='d$mid'>";
					?>
					
					<a name=<?=$mid?>>
					<table cellspacing=1 cellpadding=0 width=100% class=border>
					<tr><td>
						<table cellspacing=0 cellpadding=0 width=100%>
						<tr>
							<td class=trd width=100%><i><?=get_rusdate($add_date)." ".get_time($add_date)?></i><?if(isset($_SESSION['privs']['forum']))echo " <small>($mip)<small>"?></td>
							<td class=trd align=right width="30%" nowrap><a href=# onclick="return d_r(<?=$mid?>)">
								<img src=/pics/reply.gif border=0 width=16 height=16 alt='Ответить'></a> 
								<?
								if(isset($_SESSION['privs']['forum']))
								echo 	"<a href='#' onclick=\" if(confirm('Точно удалить?'))remove_msg($mid);return false;\">
									<img src=/pics/del.gif width=16 height=16 border=0 alt='Удалить сообщение' >
									</a>";
								?>
							</td>
						</tr>
						<tr>
							<td class=trd colspan=2><a href=# onclick="return ui('<?=$author?>')"><!--'<??> '--><font class=nick><?=$author?></font></a>: <b><?=$subject?></b>
							<input type=hidden name="s<?=$mid?>" value="<?=$subject?>"> <!--"<??> "-->
							<br><br>
							<div id="b<?=$mid?>" class=trd><?=$msg?></div> <!--"<??> "-->
							</td>
						</tr>
						</table>
					</td></tr>
					</table>
					<br>
					<!--/div-->
					
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
				От: 
				<select name="nick">
				<?
					$nid=mysql_select1("select last_nick_id from tbl_users where id='$uid'");
					$res=mysql_query("select id,nick from nicks where uid='$uid'");
					while($r=mysql_fetch_row($res))
					{
						$id=$r[0];
						$n=$r[1];
						if($nid==$id)
						echo "<option value=$id selected> $n\n";
						else
						echo "<option value=$id> $n\n";
					}

				?>
				</select>
			<br>

			<br>
			Тема:<br>
			<input class=ta type=textfield name="subj" maxlength=100><br>
			<textarea class=ta rows=8 cols=40 maxlength=10000 name="msg"></textarea><br>
			<input type=submit value="Добавить сообшение" name=smt>
			</form>
			<?
			if(isset($adm))
			{
				echo "<div align=right><a href=\"/forum/forum.php?t=$arg_t&rmth=1\" onclick=\"return confirm('Точно удалить тему?')\">Удалить тему</a>";
			}
			?>
	  	<?
		}
	      ?>

              <table cellspacing="2" cellpadding="1" border="0" width="100%"></table><br>

              <table cellspacing="0" cellpadding="0" border="0" width="100%">
                <tr>
			
                  <td width="33%" align="left"><?=$fresh_t?> 	      
		  <td width="33%">	Страница <?=$select_page_down?> из <?=$npages+1?></td>
                  <td width="33%" align="right"><?=$old_t?></td>
                </tr>
              <!--/table-->
            </td>
          </tr>
        </table>

      <!--END-->
      <?
      }
      ?>
      </td>

      <td></td>

      <td>
      </td><!-- up to 22 may-->
    </tr>
  </table>

  <p align="left"> </p>
  <hr>

    <?
    include 'diz/bottom_table.php';
    ?>
    
</body>
	<?
	}
	?>
</html>
