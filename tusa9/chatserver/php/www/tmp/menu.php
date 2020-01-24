<ul id="menu">
<li class="menu-title">Навигация</li>

<li><a href="/c2">Главная</a></li>

<?
    if(!isset($uid))
    {
?>
<li><a href="/c2/registration">Регистрация</a></li>
<?
    }
?>

<li><a href="/c2/stats.php">Статистика</a></li>
<li><a href="/c2/help">Помощь</a></li>



<?
    if(isset($uid))
    {
?>
<li><a href="/c2/forum/forum.php">Форум</a></li>
<li><a href="/c2/gallery.php">Галерея</a></li>
<li><a href="/c2/vote.php">Голосование</a></li>
<li><a href="/c2/url_login.php">Вход в чат</a></li>
<li><a href="/c2/logout.php">Выход</a></li>

<?
    }
    if(isset($forum) && $_SESSION["level"]>399)
    {
?>
<li><a href="/c2/forum/forum.php?add=1">Добавить тему</a></li>
<?
    }
    
?>
</ul>
