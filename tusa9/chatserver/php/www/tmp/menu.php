<ul id="menu">
<li class="menu-title">���������</li>

<li><a href="/c2">�������</a></li>

<?
    if(!isset($uid))
    {
?>
<li><a href="/c2/registration">�����������</a></li>
<?
    }
?>

<li><a href="/c2/stats.php">����������</a></li>
<li><a href="/c2/help">������</a></li>



<?
    if(isset($uid))
    {
?>
<li><a href="/c2/forum/forum.php">�����</a></li>
<li><a href="/c2/gallery.php">�������</a></li>
<li><a href="/c2/vote.php">�����������</a></li>
<li><a href="/c2/url_login.php">���� � ���</a></li>
<li><a href="/c2/logout.php">�����</a></li>

<?
    }
    if(isset($forum) && $_SESSION["level"]>399)
    {
?>
<li><a href="/c2/forum/forum.php?add=1">�������� ����</a></li>
<?
    }
    
?>
</ul>
