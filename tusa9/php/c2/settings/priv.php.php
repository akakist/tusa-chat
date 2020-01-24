<div class='first-line'>Покупка привилегий</div>

<form method=post>
<div id='datalist'>
      <?
      	list($gender,$level,$credits,$bought_invisibility)=mysql_select1row("select gender,level,credit_summa,bought_invisibility from tbl_users where id='$uid'");
	$base_level=$level/100; settype ($base_level,"integer"); $base_level_up=$base_level+1;	$base_level *=100; $base_level_up *=100; 
	list($cost_eq,$cost_up)=mysql_select1row("select cost_eq,cost_up  from level_cost where id='".mysql_escape_string($base_level)."'");
	
 	if(isset($arg_todo))	
	{
		if(isset($arg_invis_add))
		{
		if($credits>$arg_invis_add)
		{
			mysql_query("update tbl_users set credit_summa=credit_summa-".mysql_escape_string($arg_invis_add).",bought_invisibility=bought_invisibility+".mysql_escape_string($arg_invis_add)." where id='$uid'") or die(mysql_error().__FILE__.__LINE__);
			$error="Инвиз нормально прикуплен";
      			list($credits,$bought_invisibility)=mysql_select1row("select credit_summa,bought_invisibility from tbl_users where id='$uid'");
		}
		else $error="Недостаточно средств на счете";
		}
		else $error="!isset(invis_add)";
	}

 	if(isset($arg_todo1))	
	{
		if(isset($arg_level_up))
		{
		if($credits>$cost_up)
		{
			mysql_query("update tbl_users set credit_summa=credit_summa-$cost_up,level=".mysql_escape_string($arg_level_up).",poweshen=-1 where id='$uid'") or die(mysql_error().__FILE__.__LINE__);
			$error="Уровень повышен";
     			list($credits,$level)=mysql_select1row("select credit_summa,level from tbl_users where id='$uid'");
			$base_level=$level/100; settype ($base_level,"integer"); $base_level_up=$base_level+1;	$base_level *=100; $base_level_up *=100; 
			list($cost_eq,$cost_up)=mysql_select1row("select cost_eq,cost_up  from level_cost where id='".mysql_escape_string($base_level)."'");
		}
		else $error="Недостаточно средств на счете";
		}
		else $error="!isset(level_up)";
	}

 	if(isset($arg_todo2))	
	{
		if(isset($arg_level_eq))
		{
		if($credits>$cost_eq)
		{
		if($level!=$arg_level_eq)
		{
			mysql_query("update tbl_users set credit_summa=credit_summa-".mysql_escape_string($cost_eq).",level=".mysql_escape_string($arg_level_eq).",poweshen=-1 where id='$uid'") or die(mysql_error().__FILE__.__LINE__);
			$error="Уровень изменен";
     			list($credits,$level)=mysql_select1row("select credit_summa,level from tbl_users where id='$uid'");

		}
		else $error="Вы не выбрали уровень для изменения";
		}
		else $error="Недостаточно средств на счете";
		}
		else $error="!isset(level_eq)";
	}

      ?>
		<?
		if(isset($error))
                	echo "<center> <font class='yelmsg'>$error</font> </center><br>\n";
		?>
                На данной странице Вы можете приобрести за кредиты уровни, место на диске, а также статус невидимость.<br>		
		<p>


                <p>У Вас на счете <b><?=sprintf("%2.2f",$credits)?></b> кредитов.<br>

                <br>
                <fieldset>
                  <legend class="leg"> Покупка уровня </legend>			<p>
                        <form method="post" name=lev_inc">
                <?
        if ($level<400)
          {
                ?>
                        <input type="hidden" name='todo1' value='buy_level_up'> Повысить свой уровень до
			<select name=level_up>
			<?
			$base_level_up=intval($base_level_up);
			$res=mysql_query("select a.id,b.name 
			             from levels a, level_names b 
			             where a.id=b.id and b.gender=$gender and a.id>=$base_level_up and a.id<($base_level_up+99)
			             order by 1") or die(mysql_error().__FILE__.__LINE__);
	
			while($row=mysql_fetch_row($res))
			{	    echo "<option value=$row[0]> $row[1]\n";	}
			?>
                        </select>     <input type="submit" value='Повысить!' style="font-weight: bold">
                          за <b><?=sprintf("%2.2f",$cost_up)?></b> кредитов.<br>
            <?
            }
        else  {   ?> Уровни выше тусовщика не продаются.  <?     }     
            ?>
                        </form>
			<p>
                </fieldset><br>

                <fieldset>
                  <legend class="leg"> Изменение уровня на равнозначный</legend>
			<p>
                        <form method="post" name="lev_eq">
                <?
        if ($level<800)
          {
                ?>
                        <input type="hidden" name='todo2' value='buy_level_eq'> Изменить свой уровень на
			  <select name='level_eq'>
			<?
			$base_level=intval($base_level);
			$res=mysql_query("select a.id,b.name 
			             from levels a, level_names b 
			             where a.id=b.id and b.gender=".mysql_escape_string($gender)." and a.id>=$base_level and a.id<($base_level+99)
			             order by 1") or die(mysql_error().__FILE__.__LINE__);
	
			while($row=mysql_fetch_row($res))
			{	    
			$selected=$level==$row[0]?"SELECTED": "";
	    			
			echo "<option value=$row[0] $selected> $row[1]\n";	
			}
			?>
                          </select>     <input type="submit" value='Изменить!' style="font-weight: bold">
                          за <b><?=sprintf("%2.2f",$cost_eq)?></b> кредитов.<br>
            <?
            }
        else  {    ?> Уровни изменяются только по согласованию с администрацией.  <? }    
            ?>
                        </form>

			<p>
                </fieldset><br>

                <fieldset>
                  <legend class="leg">Невидимость</legend>
			<p>
                        Невидимость можно покупать в неограниченных количествах. Вы сможете быть невидимы для всех пользователей, у которых невидимости меньше чем у вас. Также вы будете видеть их
                        всех.<p>
                        Количество невидимости у вас: <?=$bought_invisibility?><br>
                        <form method="post" name="invis">
                              <input type="hidden" name='todo' value='buy_invis'> Увеличить свою невидимость на 
			  <select name='invis_add'>
                            <option value="1">1</option>
                            <option value="5">5</option>
                            <option value="10">10</option>
                            <option value="20">20</option>
                            <option value="50">50</option>
                            <option value="100">100</option>
                            <option value="200">200</option>
                            <option value="500">500</option>
                            <option value="1000">1000</option>
                          </select>     <input type="submit" value='Купить!' style="font-weight: bold">
                        </form>

                </fieldset><br>

</div>
&nbsp;<p>
<center>
                        <input type="hidden" name="DATA1" value="yes"> 
			<input type=button onclick='window.location="/c2/url_login.php"' value="Назад" class=b_l>
</center>

</form>




