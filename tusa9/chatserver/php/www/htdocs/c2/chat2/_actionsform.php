<?
	session_start();
	header("Content-Type: text/html; charset=\"windows-1251\"");
        import_request_variables("gp", "arg_");
	
	include "inc/db_conn.php";
	include "inc/str_nick.php";
	include "inc/unescape_rus.php";
	check_conn();
     if(isset($_SESSION['uid']))
     {
	$uid=intval($_SESSION['uid']);
     }
     
     if(!isset($uid))
     {
     	header("Location: /");die;
     }
     $arg_nid=intval($arg_nid);
     $arg_channel=intval($arg_channel);
     list($znick,$zuid)=mysql_select1row("select nick,uid from nicks where id='$arg_nid'");
     list($level,$ul_mode_hide_female,$ul_mode_hide_male,$ul_mode_contacts_only)=mysql_select1row("select level,ul_mode_hide_female,ul_mode_hide_male,ul_mode_contacts_only from tbl_users where id='$uid'");
     list($chname,$chext,$chname2,$moderated)=mysql_select1row("select name,ext,name2,moderated from channels where id='$arg_channel'");
		echo "<form method=post name='actform'>";
	$channel_out="";
//	echo $_SESSION["level"];
	if(isset($_SESSION["privs"]["topic"]) || $_SESSION["level"]>=500)
	{
		
		
		$channel_out.= "
		<b>�����: </b><input name='top' type=text> 
		<input type=button onclick='
        	$.post(\"/set_topic.tse\",{
                    msg: escape(document.actform.top.value),
                    r: Math.random() 
       	           },
		   function(data){
		   	append_messages(\"<br>\"+data+\"<br>\");
			$(\"#actionsform\").toggle();
		    });' value='�������'>";

		
				
	
	
	}
	if($_SESSION["level"]>=900)
	{
		

	$checked=$moderated?"CHECKED":"";
	$channel_out.="<p><input type=checkbox name=moderated onclick='return toggle_moderated();' class=c_b $checked> ������������ (+m)";

	}
	if(strlen($channel_out))
	{
		echo "����� $chname2:<p>$channel_out<hr>";
	}
	if(isset($zuid))
	{
	?>
		<p><b>�������� � ������ <?=$znick?></b><br>

		<input type=button value='�����' onclick="IgnoreUser(<?=$zuid?>);$('#actionsform').hide();return false;" title='��������/��������� ����� ������ �� ��������� � ����� ������������'>
		
		<?
		if($level>=900)
		{
		?>
			<input type=button value='����� (+v)' onclick="ch_voice();$('#actionsform').hide(); return false;"  title="����/������� ������������ ����������� ������. (+v)">
		<?
		}
		?>
		
		<?
		if($level>=600)
		{
		?>
			<input type=button value='��� ����' onclick="KickUserZa(<?=$zuid?>,'����');$('#actionsform').hide(); return false;"  title="������� �� ����">
			<input type=button value='��� ����' onclick="KickUserZa(<?=$zuid?>,'����');$('#actionsform').hide(); return false;"  title="������� �� ����">
		<?
		}
		?>

	
	<?
	}
	?>
	<p>����� �������-�����<br>
	<input class=c_b type=checkbox id='contacts_only' <?if($ul_mode_contacts_only) echo 'checked';?>  onclick='$.post("/change_contact_mode.tse",{r:Math.random()}, function(data){reload_chat();}); return true;'><label for='contacts_only' >���������� ������ �� ������� �����</label><br>
	<input class=c_b type=checkbox id='hide_female' <?if($ul_mode_hide_female) echo 'checked';?>  onchange='$.post("/change_female_mode.tse",{r:Math.random()}, function(data){reload_chat(); });return true;'><label for='hide_female' >�������� �������</label><br>
	<input class=c_b type=checkbox id='hide_male' <?if($ul_mode_hide_male) echo 'checked';?>  onchange='$.post("/change_male_mode.tse",{r:Math.random()},function(data){reload_chat();});return true;'><label for='hide_male' >�������� ������</label><br>

	
	<p><input type=button value='�������' onclick="$('#actionsform').hide();">
	</form>
