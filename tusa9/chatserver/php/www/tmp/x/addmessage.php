<div id='addmenu' style='width: 1000px;'>
	<form method=post name='sendform' onsubmit="return DoSend();" style='border:none'>
	<input style="" type="text" size="80" maxlength='<?=$msglen?>' name="msgbox" value="" >
	<!--onKeyDown="return on_key(event.keyCode);" -->
	<input type="submit" style="" value="OK">
	<input type=text  style='width: 60px;' maxlength=12 name="fornick" value="����">
	<a title="���������� ��������� ��� ����" href="#" onMouseOver="window.status='';" onClick="return on_to_all_click();">����</a>
	<select name="status" OnChange="change_status();" class=sl>
	<?

	$sm=array(2=>"���������",3=>"��������",4=>"���� ����������",5=>"������",6=>"�����",7=>"�� �������!",8=>"����������");
	$sf=array(2=>"���������",3=>"��������",4=>"���� ����������",5=>"������",6=>"������",7=>"�� �������!",8=>"����������");


	if($_SESSION['gender']==1)
	{
		foreach($sm as $key=>$val)
		{
			echo "<OPTION value=$key";
			if($last_status_id==$key) echo " selected";
			echo "> $val\n";
		}
	}
	else
	{
		foreach($sf as $key=>$val)
		{
			echo "<OPTION value=$key";
			if($last_status_id==$key) echo " selected";
			echo "> $val\n";
		}
	
	}

		$sql="select id,name from user_status where uid='$uid' order by 1";
		$result=mysql_query($sql) or die(mysql_error());
    		while ($row=mysql_fetch_row($result)){
		    if(count($row)==2)
		    {
			$stid=$row[0];
			$nm=$row[1];
			echo "<OPTION value=$stid";
			if($last_status_id==$stid) echo " selected";
			echo "> $nm\n";
		    }
		}	
        
	?>

	</select>

	<p>
<input  title='����������� F7 ��� ������������ ������' type="checkbox" class=c_b name="privbox" onClick="document.sendform.msgbox.focus(); return true;"><span title='����������� F7 ��� ������������ ������'>������</span>&nbsp;
<input  title='����������� F8 ��� ������������ ������' type="checkbox" class=c_b name="makeitbox" onClick="document.sendform.msgbox.focus(); return true;"><span title='����������� F8 ��� ������������ ������'>��������</span>&nbsp;

<?
	if($level>899)
	{
?>

<input type="checkbox" class=c_b name="sysbox" onclick="document.sendform.msgbox.focus(); return true;">���������
<?
	}
?>
<input type="checkbox" class=c_b name="scrollbox" checked onclick="set_scroll(this.checked); return true;">���������&nbsp;
	<?
	if($_SESSION['level']>=900){
	$checked=$moderated?"CHECKED":"";
	echo("<small><input type=checkbox name=moderated onclick='return toggle_moderated();' class=c_b $checked> ������������ (+m)</small>");
	}
	?>
	<input type=button value="XMM2RUS" onclick="XMM2RUS(this)" title="��������������">

	<input type=button onclick='
		$("#actionsform").toggle();$("#actionsform").css("top",$(window).height()-$("#addmessage").height()-$("#actionsform").height());
		$("#formnickname").html(selected_nick);
		' value='>>'>

	</form>
	
	
		
	<div id='actionsform' style='display: none; position:absolute; left:20px;top:0px;width:400px;height:300px; background-color: #004470;padding:10px;'>
		<?
//		if($level>499)
		{
		?>
		<form method=post name='formtop'>
		<b>������� ����� �����:</b><p>
		<input name='top' type=text> 
		<input type=button onclick='
        	$.post("_change_topic.php",{
                    top: escape(document.formtop.top.value),
       	            chan: channel,
                    r: Math.random() 
       	           },
		   function(data){
		   	append_messages("<br>"+data+"<br>");
			$("#actionsform").toggle();
		    });' value='�������'>
		
		
		<p><b>�������� � ������ <span id='formnickname'></span></b><br>
		<input type=button value="���� ����� (+v)" onclick=" ch_voice();
		$('#actionsform').toggle();" 
		title="����/������� ������������ ����������� ������. (+v)"  style="width: 125">
		</form>
		<?
		}
		?>
		

	</div>
	

	
	<?
	if($_SESSION['level']>=900){
//	echo('<input type=button value="���� ����� (+v)" onclick="return ch_voice()" title="����/������� ������������ ����������� ������. (+v)"  style="width: 125">&nbsp;');
	}
	?>
	
</div>
