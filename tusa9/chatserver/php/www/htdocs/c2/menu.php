<ul id="menu">
<li class="menu-title" >���������</li>
<?
$ip=$_SERVER["REMOTE_ADDR"];
list($time_cnt,$time_free,$descr)=mysql_select1row("select time_cnt,time_free,za from banned_ip where ip='$ip' and time_free>NOW()");
//  echo "IP $ip $time_cnt";
//  $errscr= "<script> document.start.login.focus();</script>";

if(isset($time_cnt))
  {
  $error="��� IP ����� ������� �� $descr �� $time_cnt, ���� ��������� $time_free";
  $errscr= "<script> document.start.login.focus();</script>";
  } 
								
else
    if(!isset($uid))
    {
?>
<li><a href="/c2/registration.php">�����������</a></li>
<?
    }
?>

<li><a href="/c2/index.php">�������</a></li>
<li><a href="/c2/stat.php">����������</a></li>
<li><a href="/c2/top.php">������ ������</a></li>
<li><a href="/c2/help/index.php">������</a></li>



<?
    if(isset($uid))
    {
?>
<li><a href="/c2/forum/forum.php">�����</a></li>
<li><a href="/c2/gallery.php">�������</a></li>
<?

?>
<li><a href="/c2/vote/vote.php">�����������</a></li>
<?
//if(isset($_SESSION['uid']) && ($uid==60610 || $uid==203509 || $uid==448226) )
if(isset($_SESSION['uid']) )
    {
?>
<li><a href="/c2/total/bookmaker.php">�����-�������</a></li>
<?
    }


?>
<li class="hl"><a class="hl_link" href="/c2/url_login.php">���� � ���</a></li>
<li><a href="/c2/logout.php">�����</a></li>

<?
    }
    if(isset($forum) && $_SESSION["level"]>399)
    {
?>
<li class="hl"><a class="hl_link" href="/c2/forum/forum.php?add=1">�������� ����</a></li>
<?
    }
?>
</ul>
