<tr height=7><td></td></tr>
<tr height=16><td class=tb onmouseover="mOvr(this);" onmouseout="mOut(this);" onclick="mClk(this);">&nbsp;<a class=ab href="/">�������</a></td></tr>
<?
    if(!isset($login))
    {
?>
<tr height=7><td></td></tr>
<tr height=16><td class=tb onmouseover="mOvr(this);" onmouseout="mOut(this);" onclick="mClk(this);">&nbsp;<a class=ab href="/registration">�����������</a></td></tr>
<?
    }
?>
<tr height=7><td></td></tr>
<tr height=16><td class=tb onmouseover="mOvr(this);" onmouseout="mOut(this);" onclick="mClk(this);">&nbsp;<a class=ab href="/forum/forum.php">�����</a></td></tr>
<tr height=7><td></td></tr>
<tr height=16><td class=tb onmouseover="mOvr(this);" onmouseout="mOut(this);" onclick="mClk(this);">&nbsp;<a class=ab href="/help">������</a></td></tr>
<tr height=7><td></td></tr>
<tr height=16><td class=tb onmouseover="mOvr(this);" onmouseout="mOut(this);" onclick="mClk(this);">&nbsp;<a class=ab href="/vote.php">�����������</a></td></tr>
<tr height=7><td></td></tr>
<tr height=16><td class=tb onmouseover="mOvr(this);" onmouseout="mOut(this);" onclick="mClk(this);">&nbsp;<a class=ab href="/gallery.php">�������</a></td></tr>
<tr height=7><td></td></tr>
<tr height=16><td class=tb onmouseover="mOvr(this);" onmouseout="mOut(this);" onclick="mClk(this);">&nbsp;<a class=ab href="/stat.php">����������</a></td></tr>
<?
    if(isset($login))
    {
?>
<tr height=14><td>&nbsp;</td></tr>
<tr height=16><td class=tbg onmouseover="mOvr(this,2);" onmouseout="mOut(this,2);" onclick="mClk(this,2);">&nbsp;<a class=ab href="/url_login.php">���� � ���</a></td></tr>
<tr height=14><td>&nbsp;</td></tr>
<tr height=16><td class=tb onmouseover="mOvr(this);" onmouseout="mOut(this);" onclick="mClk(this);">&nbsp;<a class=ab href="/logout.php">�����</a></td></tr>
<?
    }
    else if(0)
    {
?>
    <tr height=12><td></td></tr>
    <tr> <td>
    <!--    -->    
	<form  method=POST name="start">
          <input type=hidden name="scr" value="">
          <script>
	    s=screen;
	    document.start.scr.value=s.width+'x'+s.height+'x'+s.colorDepth;
	    </script>
                <tr><td align=center class=borderg>�����</td></tr>
                <tr><td align=center><input type="textfield" name="login" value="" maxlength=16 size=20> </td></tr>
		<tr height=5><td></td></tr>
		
                  <tr><td align="center" class=borderg>������</td></td>
                 <tr><td><input type="password" name="pass" maxlength=16 size=20></td></td>
              <tr><td width=100%%> <input name="submit" type="submit" value="�����" onclick="if(document.start.pass.value==''){alert('����� ������ ������');return false;}"></td></tr>
              <script>
	    	document.start.login.focus();
	    </script>
        </form>

    
    <!-- -->
    </td>
    
    </tr>
<?
    }
?>
