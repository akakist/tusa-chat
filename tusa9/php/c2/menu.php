<ul id="menu">
<li class="menu-title" >Навигация</li>
<?
$ip=$_SERVER["REMOTE_ADDR"];
list($time_cnt,$time_free,$descr)=mysql_select1row("select time_cnt,time_free,za from banned_ip where ip='".mysql_escape_string($ip)."' and time_free>NOW()");
//  echo "IP $ip $time_cnt";
//  $errscr= "<script> document.start.login.focus();</script>";

if(isset($time_cnt))
  {
  $error="Ваш IP адрес забанен за $descr на $time_cnt, дата окончания $time_free";
  $errscr= "<script> document.start.login.focus();</script>";
  } 
								
else
    if(!isset($uid))
    {
?>
<li><a href="/c2/registration.php">Регистрация</a></li>
<?
    }
?>

<li><a href="/c2/index.php">Главная</a></li>
<li><a href="/c2/stat.php">Статистика</a></li>
<li><a href="/c2/top.php">Лучшие игроки</a></li>
<li><a href="/c2/help/index.php">Помощь</a></li>



<?
    if(isset($uid))
    {
?>
<li><a href="/c2/forum/forum.php">Форум</a></li>
<li><a href="/c2/gallery.php">Галерея</a></li>
<?

?>
<li><a href="/c2/vote/vote.php">Голосование</a></li>
<?
if(isset($_SESSION['uid']) )
    {
?>
<li><a href="/c2/total/bookmaker.php">Спорт-Прогноз</a></li>
<?
    }


?>
<li class="hl"><a class="hl_link" href="/c2/url_login.php">Вход в чат</a></li>
<li><a href="/c2/logout.php">Выход</a></li>

<?
    }
    if(isset($forum) && $_SESSION["level"]>399)
    {
?>
<li class="hl"><a class="hl_link" href="/c2/forum/forum.php?add=1">Добавить тему</a></li>
<?
    }
?>
</ul>
