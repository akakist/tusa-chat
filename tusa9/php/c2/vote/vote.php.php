<form name='voting' method='POST' action='vote.php'>
<input id='vote_yes' type='hidden' name='vote_yes'>
</form>
<form name='voting_' method='post' action='vote.php'>
<input id='vote_no'  type='hidden' name='vote_no'>
</form>

<?
import_request_variables("gp", "arg_");
$main_id=$_SESSION['uid'];
$main_login=$_SESSION['login'];
$main_level=$_SESSION['level'];
$main_nick=mysql_select1("select last_nick from tbl_users where id='$main_id'");
$vote_balls=mysql_select1("select vote_balls from tbl_users where id=$main_id");
//if(isset($_SESSION['privs']['vote']) && $main_level!=1000) 	    {$max_lev=599;}	else {$max_lev=899;} // 599
$bl = intval($main_level/100)*100;
$main_cost = mysql_select1("select cost_eq from level_cost where id=$bl") /100 ;
$max_lev=599;
if ( $main_level>= 600 ) { $main_cost == 10000; $max_lev=1899; }
if ( isset($_SESSION['privs']['vote']) ) { $main_cost = 0; }

$time_vote = 604800;
$time_delete = 864000;



function send_note( $v_res,$v_id )
    {
    $v_uid=0;
    $v_uid=mysql_select1("select uid from grant_vote where id='$v_id'");
    if($v_uid==0)     {	echo "Логин не найден";	return 0; }
                                        
    $tmp = mysql_query("select from_nick,msg,add_date,show_nick  from grant_messages where gid=$v_id order by add_date" ) or die(mysql_error());
    $str="";
    while ( $v_m=mysql_fetch_row($tmp) )
	{
	$str .= get_rusdate($v_m[2])." ".get_time($v_m[2])."<br>";
        if ($v_m[3]==1) { $str .= " $v_m[0]<br>"; }
        $str .="$v_m[1]<br><br>";
	}
    if ($v_res==1)  	{$tema="Поздравляем с успешным завершением голосования";}
    else		{$tema="К сожалению голосование закончилось отрицательно";}
    mysql_query("insert into ext_events (event,d1,d2) values ('cmd=systemnote uid=$v_uid','$tema','$str')") or die(mysql_error().__FILE__.__LINE__);
    return 1;
    }                                                                                   



if(isset($arg_add_nick))
    {
    $pr_id=intval(mysql_select1("select uid from nicks where nick='$arg_add_nick'"));
//    if( $pr_id <=0 || strlen($arg_add_nick) == 0)
    if( $pr_id <=0 || strlen($arg_add_nick) == 0)
        {
        $strerr = "Ник ".$arg_add_nick." не найден";
        }
    else
        {
        $v_id=mysql_select1row("select id  from grant_vote where uid='$pr_id'");
        list($pr_level)=mysql_select1row("select level  from tbl_users where id='$pr_id'");
        if ($v_id>0) 	{    		$strerr = "Пользователь ".$arg_add_nick." уже стоит на голосовании";    		}
        else
          {
          if ($main_cost>mysql_select1("select credit_summa from tbl_users where id=$main_id")) 
		{$strerr = "Недостаточно кредитов для постановки";}
	  else if ( $pr_level == $arg_level_tar )		{$strerr = "Текущий уровень не изменен";}
	  else
	    {
    	    $d = date('Y.m.d H:i:s');
    	    mysql_query("insert into grant_vote (nick,llevel,nlevel,uid,add_date,add_by,status)
            	    values('$arg_add_nick','$pr_level','$arg_level_tar','$pr_id','$d','$main_id',0)") or die(mysql_error());
	    list($v_id)=mysql_select1row("select id  from grant_vote where uid='$pr_id'");
	    $ip=$_SERVER["REMOTE_ADDR"];
    	    mysql_query("insert into grant_messages (gid,from_nick,ip,msg,add_date,show_nick)
        				    values('$v_id', '$main_nick', '$ip' ,'$arg_msg','$d',1)") or die(mysql_error());
    	    mysql_query("update tbl_users set credit_summa=credit_summa-'$main_cost' where id='$main_id'") or die(mysql_error());
    	    $strerr =  "Пользователь " .$arg_add_nick ." поставлен на голосование";

            }
          }
    	}
        unset($arg_add_nick);         unset($arg_msg); 		unset($arg_level_tar); 
    } //add vote

if(isset($arg_vote_del))
    {
    $del_uid=mysql_select1("select id from grant_vote where uid='$arg_vote_del'");
    if ( $del_uid != 0 )
	{
	mysql_query("delete from grant_agrees where gid='$del_uid'") or die(mysql_error());
	mysql_query("delete from grant_messages where gid='$del_uid'") or die(mysql_error());
	mysql_query("delete from grant_vote where id='$del_uid'") or die(mysql_error());
	unset($arg_vote_del);         unset($del_uid);
	}
    }

if(isset($arg_vote_yes))
    {
    $yes_uid=mysql_select1("select id from grant_vote where uid='$arg_vote_yes'") or die(mysql_error());
    if ( mysql_select1("select id from grant_agrees where uid='$main_id' and gid='$yes_uid'") == 0 )
	{
	mysql_query("insert into grant_agrees (gid,uid,yes) values ('$yes_uid','$main_id','$vote_balls')") or die(mysql_error());
        unset($arg_vote_yes);         unset($yes_uid);
	}
	$d = date('Y.m.d H:i:s');
         $tmp = "Проголосовал с IP $ip ";
        mysql_query("insert into adm_events (login,date_events,type_events,events) values('$main_login','$d','VOTE','$tmp')") or die(mysql_error());
                
    }

if(isset($arg_vote_no))
    {
    $no_uid=mysql_select1("select id from grant_vote where uid='$arg_vote_no'") or die(mysql_error());
    if ( mysql_select1("select id from grant_agrees where uid='$main_id' and gid='$no_uid'") == 0 )
	{
	mysql_query("insert into grant_agrees (gid,uid,no) values ('$no_uid','$main_id','$vote_balls')") or die(mysql_error());
        unset($arg_vote_no);         unset($no_uid);
        }
    }

?>
<div class='first-line'><a href=/c2/vote/vote.php>Голосование</a></div>
<div style='text-align:center; padding:10px'>	</div>
<table width=100% border=1 cellspacing=0 cellpadding=3 class=border>
<script>
function opwin(l,w,h)
    {
    var ow=open(l,'owusr','toolbar=0,status=0,resizable=1,scrollbars=1,width='+w+',height='+h);
    ow.focus();
    }
</script>
<?
//strlen($strerr)>0
//if(isset($_SESSION['uid']) && isset($_SESSION['privs']['vote']))
//    {
//    echo "<center><b> <font class='yelmsg'></font></b></center>";
//    }

if (!isset($strerr))	 {   $strerr="";	}
echo "<center><b> <font class='yelmsg'>".$strerr."</font></b></center>";
$strerr="";

$head="<tr>
<td><center></center></td>
<td><center>Претендент</center></td>
<td><center>Его уровень</center></td>
<td><center>На какой уровень</center></td>
<td><center>Дата постановки</center></td>
<td><center> За </center></td>
<td><center>Против</center></td>";
if ( $vote_balls > 0 ) { $head .= "<td colspan=\"2\"><center> Голоса </td><td>Инф</center></td>"; }
if(isset($_SESSION['uid']) && isset($_SESSION['privs']['vote']))
	{
	$head .= "<td><center> Stop </center></td>";
	}
$head .="</tr>";
echo $head;

list($sum_perc) = mysql_select1row("select SUM(vote_balls) from tbl_users");
$result=mysql_query("select uid,llevel,nlevel,add_date,status,id from grant_vote order by add_date") or die(mysql_error());
while($row=mysql_fetch_row($result))
    {
    if ( $row[3] < date('Y-m-d H:i:s',time()-$time_delete) ) 
	{
	mysql_query("delete from grant_agrees where gid='$row[5]'") or die(mysql_error());
	mysql_query("delete from grant_messages where gid='$row[5]'") or die(mysql_error());
	mysql_query("delete from grant_vote where id='$row[5]'") or die(mysql_error());
	}
    else
      {
    list($last_nick,$gender)=mysql_select1row("select last_nick,gender from tbl_users where id=$row[0]");
    list($level)=mysql_select1row("select name from level_names where id=$row[1] and gender=$gender");
    list($new_level)=mysql_select1row("select name from level_names where id=$row[2] and gender=$gender");
    $tmp = mysql_query("select yes,no  from grant_agrees where gid=$row[5]") or die(mysql_error());
    for ( $yes=$no=0; $tmp1=mysql_fetch_row($tmp);)	
	{	
	$yes += $tmp1[0];	$no += $tmp1[1];	
	}
    $yes /= 0.01*$sum_perc;
    $no /= 0.01*$sum_perc;
    if ( $row[4] == 0 )
	{
	if ( $row[3] < date('Y-m-d H:i:s',time()-$time_vote) ) 
	    {
	    $row[4] = 2;
    	    mysql_query("update grant_vote set status=2 where id='$row[5]'") or die(mysql_error());
	    send_note( 0,$row[5] );	// Записка не прошел
	    }
	if( $yes>=75 )
	    {
    	    $row[4] = 1;
    	    mysql_query("update grant_vote set status=1 where id='$row[5]'") or die(mysql_error());
    	    mysql_query("update tbl_users set level='$row[2]',poweshen=-2 where id='$row[0]'") or die(mysql_error());
	    send_note( 1,$row[5] );	// Записка прошел
    	    }
	if( isset($arg_vote_stop) || $no>33 )
	    {
	    $row[4] = 2;
    	    mysql_query("update grant_vote set status=2 where id='$row[5]'") or die(mysql_error());
	    send_note( 0,$row[5] );	// Записка не прошел
	    }
	}
    $str_yes = sprintf("%2.1f", $yes);
    $str_no = sprintf("%2.1f", $no);
    $sum = $yes+$no;
    $str_sum = sprintf("%2.1f", $sum);

    if ( $row[4] == 2 ) { $pp4 = "<img src='/pics/del.gif' width=16 height=16 border=0>"; 	    }
    if ( $row[4] == 1 ) { $pp4 = "<img src='/pics/granted.gif' width=16 height=16 border=0>"; 	    }
    if ( $row[4] == 0 ) { $pp4 = "<img src='/pics/processing.gif' width=16 height=16 border=0>"; }

    if ( $vote_balls > 0 ) { $level .= "($row[1])"; $new_level .= "($row[2])"; }

				    $str_tbl= "<tr>	<td><center>$pp4</center></td>
				    <td><center><a href='/c2/chat_userinfo2.php?id=$row[0]' target=_blank>$last_nick</a></center></td>
				    <td><center>$level</center></td>
				    <td><center>$new_level</center></td>
				    <td><center>" .get_rusdate($row[3]) ." " .get_time($row[3]) ."</center></td>";
//				    <td><center>" .get_rusdate($row[3]) ."</center></td>";
				    if ( $row[4] == 0 ) { $str_tbl .= "<td colspan=\"2\"><center> $str_sum% </center></td>"; }
    else { $str_tbl .= "<td><center><font class='vyes'>$str_yes%</font></center></td> <td><center><font class='vno'>$str_no%</center></td>"; }
//    else { $str_tbl .= "<td><center><font class='vyes'>$str_yes%</font></center></td> <td><center><font class='vno'>$str_no%</center></td>"; }





    if ( $vote_balls > 0 ) 
	{
	$t_vote = mysql_query("select yes,no  from grant_agrees where gid=$row[5] and uid=$main_id") or die(mysql_error());
	if ( $main_vote=mysql_fetch_row($t_vote) )
	    {
	    if($main_vote[0]>0) {$str_tbl .= "<td colspan=\"2\"><center> ЗА </center></td>";}
	    else {$str_tbl .= "<td colspan=\"2\"><center> Против </center></td>";}
	    }
	else
	    {
	    if ( $row[4] != 0 )	{$str_tbl .= "<td colspan=\"2\"><center> СПАЛ  </center></td>"; }
	    else 
	    {
		    $str_tbl .="<td><a href=\"javascript:voting('vote_yes','$row[0]')\"><img src=/pics/granted.gif border=0></td>";
	//	$str_tbl .= "<td><a href='vote.php?vote_yes=$row[0]'><img src='/pics/granted.gif' border=0></a></td>";
		$str_tbl .= "<td><a href=\"javascript:voting('vote_no','$row[0]')\"><img src='/pics/del.gif' border=0></a></td>";
//		$str_tbl .= "<td><a href='vote.php?vote_no=$row[0]'><img src='/pics/del.gif' border=0></a></td>";
		}
	    }
	$read=0;
	$read=mysql_select1("select readden from grant_readden where uid='$main_id' and gid='$row[5]'");
	if ( $read == 1 )
	    {
    	    $str_tbl .= "<td><div style='margin-left: 5px; float:left'><a href=\"javascript: opwin('/c2/vote/disput.php?id=$row[0]',550,500)\"><img src=\"/pics/hint16.gif\" width=18 height=16 border=0 alt='Login info'></a></div></td>";
	    }
	else
	    {
    	    $str_tbl .= "<td><div style='margin-left: 5px; float:left'><a href=\"javascript: opwin('/c2/vote/disput.php?id=$row[0]',550,500)\"><center><img src=\"/pics/hint16y.gif\" width=18 height=16 border=0 alt='Login info'></center></a></div></td>";
	    }
	if(isset($_SESSION['uid']) && isset($_SESSION['privs']['vote']))
	    {
    	    $str_tbl .= "<td><center><a href='vote.php?vote_del=$row[0]'><img src='/pics/del.gif' border=0></a></center></td>";
	    }
	}
    echo $str_tbl ."<tr>";
      }
    }
echo '</table>'; 

if(isset($_SESSION['uid']) && isset($_SESSION['privs']['vote']) || $main_level<1000 )
//if(isset($_SESSION['uid']) && isset($_SESSION['privs']['vote']) )
    {
// method=post 	
?>
    <form method="POST" name=add_vote action="/c2/vote/vote.php">
    <br>



<?
// method="POST"
    if( isset($_SESSION['privs']['vote']) )
	{
        $fl=1;
?>	
	Поставить на голосование <br>
	<input type=textfield style='width: 105px' size='17' maxlength='17' name="add_nick">	
<?
	}
    else
	{
	list($tmv)=mysql_select1row("select id from grant_vote where uid=$main_id");
	if ($tmv>0)	    { ?>  Вы уже стоите на голосовании <? $fl=0;	    }
	else
	    {
	    $fl=1;
	    if ($main_cost>mysql_select1("select credit_summa from tbl_users where id=$main_id")) { ?> Вы не можете встать на голосование поскольку у Вас меньше <?=sprintf("%4.2f", $main_cost);?> кредитов 
		<? $fl=0; } // 0 при недостатке кредов
	    }
	if ($fl==1)
	    {
?>	
	    Поставить на голосование себя любимого (Стоимость <?=sprintf("%4.2f", $main_cost);?> кредитов)<br>
	    <input type="hidden" name="add_nick" value="<?=$main_nick?>">
<?
	    }
	}
    if ($fl==1)
        {

?>	
	<br>
	На уровень <br>
	<select name='level_tar'>
<?
	$res=mysql_query("select a.id,b.name from levels a, level_names b where a.id=b.id and b.gender=1 and a.id<($max_lev)
             order by 1") or die(mysql_error().__FILE__.__LINE__);
                                                                                                                                                                                         
	while($row=mysql_fetch_row($res))
    	    {
    	    $selected=$main_level==$row[0]?"SELECTED": "";
    	    echo "<option value=$row[0] $selected>$row[0] $row[1]\n";
    	    }
    	
?>
    </select>    <br><br>
    Обоснование:<br>
    <textarea style='width: 400px' rows=8 cols=40 name="msg" maxlength=1024></textarea><br><br>
    <input type=submit value="Поставить на голосование" >
    </form>
<?
	}
    }

?>
<p align="right"> Подробнее о голосовании можно прочитать <a href="http://www.tusovka.tomsk.ru/c2/help/voting.php"> здесь</a></p>
