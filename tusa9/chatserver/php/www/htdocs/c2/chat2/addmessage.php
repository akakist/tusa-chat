
<div id='addmenu' style='width: 1000px;overflow:hidden;'>
	<form  method=post name='sendform' onsubmit="return DoSend();" style='border:none;padding:0; margin:0'>
		<input style="" type="text" size="80" maxlength='<?=$msglen?>' name="msgbox" value="" >
		<input type="submit" style="" value="OK">
		<input type=text  style='width: 60px;' name="fornick" value="����">
		<a class=nick title="���������� ��������� ��� ����" href="#" onMouseOver="window.status='';" onClick="return on_to_all_click();">����</a>
		<input  title='����������� F7 ��� ������������ ������' type="checkbox" class=c_b name="privbox" id="privbox"  onClick="document.sendform.msgbox.focus(); return true;"><span class=checktitle title='����������� F7 ��� ������������ ������'><label for="privbox">������</label></span>&nbsp;		
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

			$result=mysql_query("select id,name from user_status where uid='$uid' order by 1") or die(mysql_error());
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

		<br>
		
		<input  title='����������� F8 ��� ������������ ������' type="checkbox" class=c_b name="makeitbox" id="makeitbox" onClick="document.sendform.msgbox.focus(); return true;"><span class=checktitle title='����������� F8 ��� ������������ ������'><label for="makeitbox">��������</label></span>&nbsp;


<?
		if($level>899)
		{
?>
			<input type="checkbox" class=c_b name="sysbox" id="sysbox" onclick="document.sendform.msgbox.focus(); return true;"><span class=checktitle title='��������� ��������� ������������'><label for="sysbox">���������</label></span>
<?
		}
?>
		<input type="checkbox" class=c_b name="scrollbox" id="scrollbox" checked onclick="set_scroll(this.checked); return true;"><span class=checktitle title='����� ��������� ���� ����'><label for="scrollbox">���������</label></span>&nbsp;
		<input type=button value="XMM2RUS" onclick="XMM2RUS(this)" title="��������������">

		<input type=button title='����������� ��������' onclick='
			$("#actionsform:hidden").load("_actionsform.php?channel="+document.buttonsform.channel.options[channel].value+"&nid="+selected_nick_id);
			$("#actionsform").toggle();
			' value='>>'>


	</form>
	
	
		
	<div id='actionsform'>
	</div>
	
</div>



<script>
window.status='';
</script>