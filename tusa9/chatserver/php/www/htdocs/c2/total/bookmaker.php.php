<?
import_request_variables("gp", "arg_");
//include "inc/date.php";
//    if(!isset($_SESSION['uid']) || !isset($_SESSION['privs']['vote']) || !isset($arg_add_nick)) { header("Location: /c2/");die;}
//if( $_SESSION['uid']==113418 ) { die;}
//    if( $_SESSION['uid']!=60610 ) { die;}
//if( !$_SESSION['uid'] ) { die;}
//if( $_SESSION['uid']!=60610 && $_SESSION['uid']!=203509 && $_SESSION['uid']!=2356 && $_SESSION['uid']!=125848 && $_SESSION['uid']!=244940) { die;}
//if( $_SESSION['uid']!=60610 && $_SESSION['uid']!=203509 ) { echo "В отладке"; die;}
$main_id=$_SESSION['uid'];
$main_login=$_SESSION['login'];
if( $main_id==60610 || $main_id==20681 ) 	    {$adm_total=1;} else {$adm_total=0;}

$time_end_stav = 900;
$time_pred = 864000;
$cur_date = date('Y-m-d H:i');
$cur_see = date('Y-m-d H:i:s',time()-$time_pred);

$main_cred=mysql_select1("select credit_summa from tbl_users where id='$main_id'");

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
// Сделать ставку
//if( isset($arg_add_com1) && strlen($arg_add_com1)>0 && isset($arg_add_com2) && strlen($arg_add_com2)>0 && $main_id==60610 ) 

if( isset($arg_game_bonus) && $arg_game_bonus>=100 && $adm_total==1 ) 
    {
//$result=mysql_query("select id,command1,command2,date_game,result,activ,res from bookmaker") or die(mysql_error());
    list($com1,$com2,$status,$res)=mysql_select1row("select command1,command2,activ,res from bookmaker where id='$arg_game_bonus'");
    if( $status==2 )
	{
	$sta_r=mysql_query("select res,summa from bm_stavki where bid='$arg_game_bonus'") or die(mysql_error());
	$st_1=0; $st_2=0; $st_3=0; 
	while($rw=mysql_fetch_row($sta_r))
	    {
	    if ( $rw[0] == 1) { $st_1 += $rw[1]; }
	    else if( $rw[0] == 2) { $st_2 += $rw[1]; }
	    else if( $rw[0] == 3) { $st_3 += $rw[1]; }
	    }

	if ($res == 1) {	$koef = ($st_1+$st_2+$st_3)/$st_1; 	}
	else if ($res == 2) {	$koef = ($st_1+$st_2+$st_3)/$st_2; 	}
	else if ($res == 3) {	$koef = ($st_1+$st_2+$st_3)/$st_3; 	}
	echo $com1 ." - ",$com2 ." status=",$status ." res=", $res ." Koef=",$koef;

	$tema = "Выигрыш за матч ";	$tema .= $com1;	$tema .= " - ";	$tema .= $com2;

	$sta_r=mysql_query("select uid,summa from bm_stavki where res='$res' AND bid='$arg_game_bonus'") or die(mysql_error());
	while($rw=mysql_fetch_row($sta_r))
	    {
	    if ( $rw[1]>0 )
		{
		$bon=$rw[1]*$koef;
		$str = "Перечислено ";
		$str .= $bon;
		echo $tema,$str;
    		mysql_query("update tbl_users set credit_summa=credit_summa+'$bon' where id='$rw[0]'") or die(mysql_error());
    		mysql_query("update bookmaker set activ=3 where id='$arg_game_bonus'") or die(mysql_error()); 
		mysql_query("insert into ext_events (event,d1,d2) values ('cmd=systemnote uid=$rw[0]','$tema','$str')") or die(mysql_error().__FILE__.__LINE__);

		}
	    }
	
	}
    }



if(!empty($_POST['save_res']))
    {
    $ttt=2;
    mysql_query("update bookmaker set res='$arg_res' where id='$arg_match'") or die(mysql_error());
    mysql_query("update bookmaker set result='$arg_score' where id='$arg_match'") or die(mysql_error());
    mysql_query("update bookmaker set activ=2 where id='$arg_match'") or die(mysql_error());
    $strerr = "Результат записан";
    }

if(!empty($_POST['stav']))
    {
    mysql_select1("select credit_summa from tbl_users where id='$main_id'");
    if ( $arg_set_stav < 1 ) 	{	$strerr = "Ставка не может быть меньше 1 кредита";	}
    else if ($main_cred<$arg_set_stav  ) 	{	$strerr = "Недостаточно кредитов на счету";	}
    else if ( mysql_select1("select date_game from bookmaker where id='$arg_match'") > date('Y-m-d H:i:s',time()+$time_end_stav) )
	{
	mysql_query("insert into bm_stavki (bid,uid,res,summa) values ('$arg_match', '$main_id', '$arg_main_res', '$arg_set_stav') ") or die(mysql_error());
        mysql_query("update tbl_users set credit_summa=credit_summa-'$arg_set_stav' where id='$main_id'") or die(mysql_error());
	$strerr = "Ставка сделана";
	}
    else {     $strerr = "Ставки уже не принимаются"; }
    }
 


// Сделать ставку

//   add Game
if( isset($arg_add_com1) && strlen($arg_add_com1)>0 && isset($arg_add_com2) && strlen($arg_add_com2)>0 && $adm_total==1 ) 
    {
    mysql_query("insert into bookmaker (command1,command2,date_game,result,activ)
    				    values('$arg_add_com1', '$arg_add_com2', '$arg_game_date' ,'--:--',1)") or die(mysql_error());
    $strerr =  "Игра добавлена";
    } //add Game

/*
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
*/

if(isset($arg_game_del) && $adm_total==1 )
    {
    mysql_query("delete from bookmaker where id='$arg_game_del'") or die(mysql_error());
    mysql_query("delete from bm_stavki where bid='$arg_game_del'") or die(mysql_error());
    }

?>

<div class='first-line'><a href=/c2/total/bookmaker.php>Спорт-Прогноз</a></div>
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

echo "<center><b> <font class='yelmsg' size=4>Прием ставок завершается за 15 минут до начала матча!<br></font></b></center>";

//echo "<center><b> <font class='yelmsg' size=6>Отладка до 17 часов!!! просьба не делать ставок!!! Сейчас добью выигрышы...</font></b></center>";

if (!isset($strerr))	 {   $strerr="";	}
echo "<center><b> <font class='yelmsg'>".$strerr."</font></b></center>";
$strerr="";



$head="<tr>
<td><center>Матч</center></td>
<td><center>Время</center></td>
<td><center>Результат</center></td>
<td colspan=\"3\"><center>Мои ставки</td>
<td colspan=\"3\"><center>Все ставки</td>
<td><center>Выигрыш</center></td>"; 
if ( $adm_total==1 )    {  $head .= "<td><center>Удалить</center></td><td><center>Раздать</center></td>";  }
$head .="</tr>";
echo $head;

$result=mysql_query("select id,command1,command2,date_game,result,activ,res from bookmaker where date_game>'$cur_see'") or die(mysql_error());
while($row=mysql_fetch_row($result))
    {
    if ( $row[3] < date('Y-m-d H:i:s',time()+$time_end_stav) ) 
	{
    	if ($row[5]==1) { $row[5]=0;	mysql_query("update bookmaker set activ=0 where id='$row[0]'") or die(mysql_error()); }
	$str_tbl = "<tr> <td><center> $row[1] - $row[2]</center></td>"; 
	}
    else 
	{
	$str_tbl = "<tr> <td><center><a href='/c2/total/stavki.php?id=$row[0]'>$row[1] - $row[2]</a></center></td>"; 
	}

    $str_tbl .= "<td><center>".get_time($row[3]) ." " .get_rusdate($row[3]) ."</center></td>";  
    if ( $adm_total==1 )  { $str_tbl .= "<td><center><a href='/c2/total/res.php?id=$row[0]'>$row[4]</center></td>"; }
    else { $str_tbl .= "<td><center>$row[4]</center></td>"; }

    $sta_r=mysql_query("select res,summa from bm_stavki where uid='$main_id' AND bid='$row[0]'") or die(mysql_error());
    $st1=0; $st2=0; $st3=0; 
    while($rw=mysql_fetch_row($sta_r))
	{
	if ( $rw[0] == 1) { $st1 += $rw[1]; }
	else if( $rw[0] == 2) { $st2 += $rw[1]; }
	else if( $rw[0] == 3) { $st3 += $rw[1]; }
	}
    $str_tbl .= "<td><center>$st1</td><td><center>$st2</td><td><center>$st3</td>";

    $sta_r=mysql_query("select res,summa from bm_stavki where bid='$row[0]'") or die(mysql_error());
    $st_1=0; $st_2=0; $st_3=0; 
    while($rw=mysql_fetch_row($sta_r))
	{
	if ( $rw[0] == 1) { $st_1 += $rw[1]; }
	else if( $rw[0] == 2) { $st_2 += $rw[1]; }
	else if( $rw[0] == 3) { $st_3 += $rw[1]; }
	}
    $str_tbl .= "<td><center>$st_1</td><td><center>$st_2</td><td><center>$st_3</td>";

    if ( $row[5]==1)
	{
	$str_tbl .= "<td> <center>Прием ставок</td>";
	}
    else if( $row[5]==0)
	{
	$str_tbl .= "<td> <center>Идет игра</td>";
	}
    else if( $row[5]>1)
	{
	$summ_match=$st_1+$st_2+$st_3;
	$bonus=0;
	if ($summ_match==0) {$bonus=0;} // нет ставок
	else if ($row[6] == 1) {	$bonus= $st1*$summ_match/$st_1; 	}
	else if ($row[6] == 2) {	$bonus= $st2*$summ_match/$st_2; 	}
	else if ($row[6] == 3) {	$bonus= $st3*$summ_match/$st_3; 	}
	
//	else if ()
//	$bonus;
	if( $row[5]==2) {	$str_tbl .= "<td> <center>$bonus</td>"; }
	else if( $row[5]==3) {	$str_tbl .= "<td> <center><font class=vyes>$bonus</font></td>"; }
	}

    
    if ( $adm_total==1 )    
	{  
	$str_tbl .= "<td><center> <a href='bookmaker.php?game_del=$row[0]'><img src='/pics/del.gif' border=0> </td>";  
	
	
if ( $row[5] < 2 ) { $str_tbl .= "<td><center><img src='/pics/processing.gif' width=16 height=16 border=0></center></td>"; }
if ( $row[5] == 2 ) { $str_tbl .= "<td><center><a href='bookmaker.php?game_bonus=$row[0]'><img src='/pics/granted.gif' width=16 height=16 border=0></center></td>";       }
            	
	
	}
    echo $str_tbl ."<tr>";
    }
echo '</table>'; 

if( $adm_total==1 )
    {
//    echo $row[0],$row[1],$row[2],$row[3],$row[4],$row[5],$cur_date;
// method=post 	
//форма html делаешь action ставишь на страницу method='POST' ну и html input type submit, name ему задаешь, а дальше в скрипте ловишь if(!empty($_POST['buttonname']) { do_something(); }


?>
    <form method="POST" name=add_bookmaker_events action="/c2/total/bookmaker.php">    <br>
    <input type=textfield style='width: 130px' size='20' maxlength='20' name="add_com1">
    <input type=textfield style='width: 130px' size='20' maxlength='20' name="add_com2">	
    Дата <input type=textfield style='width: 130px' size='19' maxlength='19' name="game_date" value=<?=$cur_date?>>	
    <input type=submit value="Добавить матч" >
    </form>


<?
    }

?>
<p align="right"> Подробнее о ставках можно прочитать <a href="http://www.tusovka.tomsk.ru/c2/help/bookmaker.php"> здесь</a></p>
