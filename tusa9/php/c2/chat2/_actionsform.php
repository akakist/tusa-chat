<?
	session_start();
	header("Content-Type: text/html; charset=\"UTF-8\"");
        import_request_variables("gp", "arg_");
	
	include "$BASE_DIR/inc/db_conn.php";
	include "$BASE_DIR/inc/str_nick.php";
	include "$BASE_DIR/inc/unescape_rus.php";
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
     list($znick,$zuid)=mysql_select1row("select nick,uid from nicks where id='".mysql_escape_string($arg_nid)."'");
     list($level,$ul_mode_hide_female,$ul_mode_hide_male,$ul_mode_contacts_only)=mysql_select1row("select level,ul_mode_hide_female,ul_mode_hide_male,ul_mode_contacts_only from tbl_users where id='$uid'");
     list($chname,$chext,$chname2,$moderated)=mysql_select1row("select name,ext,name2,moderated from channels where id='".mysql_escape_string($arg_channel)."'");
		echo "<form method=post name='actform'>";
	$channel_out="";
//	echo $_SESSION["level"];
	if(isset($_SESSION["privs"]["topic"]) || $_SESSION["level"]>=500)
	{
		
		
		$channel_out.= "
		<b>Топик: </b><input name='top' type=text> 
		<input type=button onclick='
        	$.post(\"/set_topic.tse\",{
                    msg: escape(document.actform.top.value),
                    r: Math.random() 
       	           },
		   function(data){
		   	append_messages(\"<br>\"+data+\"<br>\");
			$(\"#actionsform\").toggle();
		    });' value='Сменить'>";

		
				
	
	
	}
	if($_SESSION["level"]>=900)
	{
		

	$checked=$moderated?"CHECKED":"";
	$channel_out.="<p><input type=checkbox name=moderated onclick='return toggle_moderated();' class=c_b $checked> Модерируемый (+m)";

	}
	if(strlen($channel_out))
	{
		echo "Канал $chname2:<p>$channel_out<hr>";
	}
	if(isset($zuid))
	{
	?>
		<p><b>Операции с юзером <?=$znick?></b><br>

		<input type=button value='Игнор' onclick="IgnoreUser(<?=$zuid?>);$('#actionsform').hide();return false;" title='Включить/выключить режим игнора по отношению к этому пользователю'>
		
		<?
		if($level>=900)
		{
		?>
			<input type=button value='Голос (+v)' onclick="ch_voice();$('#actionsform').hide(); return false;"  title="Дать/забрать пользователю возможность писать. (+v)">
		<?
		}
		?>
		
		<?
		if($level>=600)
		{
		?>
			<input type=button value='Кик флуд' onclick="KickUserZa(<?=$zuid?>,'флуд');$('#actionsform').hide(); return false;"  title="Кикнуть за флуд">
			<input type=button value='Кик маты' onclick="KickUserZa(<?=$zuid?>,'маты');$('#actionsform').hide(); return false;"  title="Кикнуть за маты">
		<?
		}
		?>

	
	<?
	}
	?>
	<p>Опции контакт-листа<br>
	<input class=c_b type=checkbox id='contacts_only' <?if($ul_mode_contacts_only) echo 'checked';?>  onclick='$.post("/change_contact_mode.tse",{r:Math.random()}, function(data){reload_chat();}); return true;'><label for='contacts_only' >Показывать только из контакт листа</label><br>
	<input class=c_b type=checkbox id='hide_female' <?if($ul_mode_hide_female) echo 'checked';?>  onchange='$.post("/change_female_mode.tse",{r:Math.random()}, function(data){reload_chat(); });return true;'><label for='hide_female' >Скрывать девушек</label><br>
	<input class=c_b type=checkbox id='hide_male' <?if($ul_mode_hide_male) echo 'checked';?>  onchange='$.post("/change_male_mode.tse",{r:Math.random()},function(data){reload_chat();});return true;'><label for='hide_male' >Скрывать парней</label><br>

	
	<p><input type=button value='Закрыть' onclick="$('#actionsform').hide();">
	</form>
