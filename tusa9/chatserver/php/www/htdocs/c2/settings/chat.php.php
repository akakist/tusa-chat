
<div class='first-line'>��������� - ���</div>

<?
function checked($c)
{
	if($c>0) return "CHECKED";
	return "";
}
function ison($c)
{
	
	if(isset($c) && $c=='on') return 1;
	return 0;
}
	if(isset($arg_DATA1))
	{
		mysql_query(sprintf("update tbl_users set 
			setting_autochange='%d',
			setting_show_level='%d',
			setting_show_credits='%d',
			setting_show_nicks='%d',
			hide_family_status='%d',
			setting_invite_sound='%d',
			setting_full_buttons='%d',
			contact_mode='%d'
			where id='$uid'",
			isset($arg_setting_autochange),
			isset($arg_setting_show_level),
			isset($arg_setting_show_credits),
			isset($arg_setting_show_nicks),
			isset($arg_hide_family_status),
			isset($arg_setting_invite_sound),
			isset($arg_setting_full_buttons),isset($arg_in_contact)+2*isset($arg_out_contact))) or die(mysql_error().__FILE__.__LINE__);
			mysql_query("insert into ext_events (event) values ('cmd=flush obj=tbl_users uid=$uid')") or die(mysql_error().__FILE__.__LINE__);
	}

 	       list($setting_show_level,$setting_show_credits,$setting_show_nicks,$hide_family_status,$setting_invite_sound,$setting_full_buttons,$contact_mode)=
mysql_select1row("select setting_show_level,setting_show_credits,setting_show_nicks,hide_family_status,setting_invite_sound,setting_full_buttons,contact_mode from tbl_users where id='$uid'");
	
	?>
<form method=post>
<div id='datalist'>
<fieldset>
<legend>��������� ����</legend>
<TABLE width="100%" border=0 cellspacing=0 cellpadding=3>
	<TR>
	    <TD style='width: 180px'>���������� �������<INPUT TYPE=checkbox name="setting_show_level" <?=checked($setting_show_level)?> class=c_b></TD>
	    <TD>���� ������� �� ����� �� ��� ������� � ���� ������ �� ����� ������������, ������ ����������� ������ ������� � ��� ���������.</TD>
	</TR>
	<TR>
	    <TD>���������� �������<INPUT TYPE=checkbox name="setting_show_credits" <?=checked($setting_show_credits)?> class=c_b></TD>
	    <TD>���� ������� ����� �� ��� ���� �������� ����� ��������� � ����� ����.</TD>
	</TR>
	<TR>
	    <TD>���������� ��� ����<INPUT TYPE=checkbox name="setting_show_nicks" <?=checked($setting_show_nicks)?> class=c_b></TD>
	    <TD>� ��� � ���� ����� ��������� ��� ���� ����.</TD>
	</TR>
	<TR>
	    <TD>�������� �������� ���������<INPUT TYPE=checkbox name="hide_family_status" <?=checked($hide_family_status)?>  class=c_b></TD>
	    <TD>&nbsp;</TD>
	</TR>
	<TR>
	    <TD>���� ��� "�������"<INPUT TYPE=checkbox name="setting_invite_sound" <?=checked($setting_invite_sound)?> class=c_b></TD>
	    <TD>���� ����� ������� - �� ����� ��� "�����", ����� ���������� �������� ������.</TD>
	</TR>
	<TR>
	    <TD>���������� ��� ������<INPUT TYPE=checkbox name="setting_full_buttons" <?=checked($setting_full_buttons)?> class=c_b></TD>
	    <TD>��� ������� ������� � ������ ������������� ���� ����� ������������ ��� ������, ����� ��� "�����" � ��� ������� "�������", ��� ����������� ����� ��� ����� �������� �������.</TD>
	</TR>
	<TR>
	    <TD>�� �������� ��������<input type=checkbox name="in_contact" class=c_b <?=checked($contact_mode==3 || $contact_mode==1)?> ></TD>
	    <TD>������� ��� �������� ������������� ����������� � ��� �������-����</TD>
        </TR>
	<TR>
	    <TD>�� ��������� ��������<input type=checkbox name="out_contact" class=c_b <?=checked($contact_mode==2 || $contact_mode==3 )?> ></TD>
	    <TD>��� ���� �� ������ �������� ������������� ����������� � ��� �������-����</TD>
	</TR>
	
</TABLE>
</fieldset>
</div>
&nbsp;<p>
<center>
                        <input type="hidden" name="DATA1" value="yes"> 
			<input type=submit value="��������" class=b_l>
			<input type=button onclick='window.location="/c2/url_login.php"' value="�����" class=b_l>
</center>

</form>




