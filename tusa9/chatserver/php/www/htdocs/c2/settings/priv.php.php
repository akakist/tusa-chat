<div class='first-line'>������� ����������</div>

<form method=post>
<div id='datalist'>
      <?
      	list($gender,$level,$credits,$bought_invisibility)=mysql_select1row("select gender,level,credit_summa,bought_invisibility from tbl_users where id='$uid'");
	$base_level=$level/100; settype ($base_level,"integer"); $base_level_up=$base_level+1;	$base_level *=100; $base_level_up *=100; 
	list($cost_eq,$cost_up)=mysql_select1row("select cost_eq,cost_up  from level_cost where id='$base_level'");
	
 	if(isset($arg_todo))	
	{
		if(isset($arg_invis_add))
		{
		if($credits>$arg_invis_add)
		{
			mysql_query("update tbl_users set credit_summa=credit_summa-$arg_invis_add,bought_invisibility=bought_invisibility+$arg_invis_add where id='$uid'") or die(mysql_error().__FILE__.__LINE__);
			$error="����� ��������� ���������";
      			list($credits,$bought_invisibility)=mysql_select1row("select credit_summa,bought_invisibility from tbl_users where id='$uid'");
		}
		else $error="������������ ������� �� �����";
		}
		else $error="!isset(invis_add)";
	}

 	if(isset($arg_todo1))	
	{
		if(isset($arg_level_up))
		{
		if($credits>$cost_up)
		{
			mysql_query("update tbl_users set credit_summa=credit_summa-$cost_up,level=$arg_level_up,poweshen=-1 where id='$uid'") or die(mysql_error().__FILE__.__LINE__);
			$error="������� �������";
     			list($credits,$level)=mysql_select1row("select credit_summa,level from tbl_users where id='$uid'");
			$base_level=$level/100; settype ($base_level,"integer"); $base_level_up=$base_level+1;	$base_level *=100; $base_level_up *=100; 
			list($cost_eq,$cost_up)=mysql_select1row("select cost_eq,cost_up  from level_cost where id='$base_level'");
		}
		else $error="������������ ������� �� �����";
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
			mysql_query("update tbl_users set credit_summa=credit_summa-$cost_eq,level=$arg_level_eq,poweshen=-1 where id='$uid'") or die(mysql_error().__FILE__.__LINE__);
			$error="������� �������";
     			list($credits,$level)=mysql_select1row("select credit_summa,level from tbl_users where id='$uid'");

		}
		else $error="�� �� ������� ������� ��� ���������";
		}
		else $error="������������ ������� �� �����";
		}
		else $error="!isset(level_eq)";
	}

      ?>
		<?
		if(isset($error))
                	echo "<center> <font class='yelmsg'>$error</font> </center><br>\n";
		?>
                �� ������ �������� �� ������ ���������� �� ������� ������, ����� �� �����, � ����� ������ �����������.<br>		
		<p>


                <p>� ��� �� ����� <b><?=sprintf("%2.2f",$credits)?></b> ��������.<br>

                <br>
                <fieldset>
                  <legend class="leg"> ������� ������ </legend>			<p>
                        <form method="post" name=lev_inc">
                <?
        if ($level<400)
          {
                ?>
                        <input type="hidden" name='todo1' value='buy_level_up'> �������� ���� ������� ��
			<select name=level_up>
			<?
			$res=mysql_query("select a.id,b.name 
			             from levels a, level_names b 
			             where a.id=b.id and b.gender=$gender and a.id>=$base_level_up and a.id<($base_level_up+99)
			             order by 1") or die(mysql_error().__FILE__.__LINE__);
	
			while($row=mysql_fetch_row($res))
			{	    echo "<option value=$row[0]> $row[1]\n";	}
			?>
                        </select> ����<input type="submit" value='��������!' style="font-weight: bold">
                          �� <b><?=sprintf("%2.2f",$cost_up)?></b> ��������.<br>
            <?
            }
        else  {   ?> ������ ���� ��������� �� ���������.  <?     }     
            ?>
                        </form>
			<p>
                </fieldset><br>

                <fieldset>
                  <legend class="leg"> ��������� ������ �� ������������</legend>
			<p>
                        <form method="post" name="lev_eq">
                <?
        if ($level<800)
          {
                ?>
                        <input type="hidden" name='todo2' value='buy_level_eq'> �������� ���� ������� ��
			  <select name='level_eq'>
			<?
			$res=mysql_query("select a.id,b.name 
			             from levels a, level_names b 
			             where a.id=b.id and b.gender=$gender and a.id>=$base_level and a.id<($base_level+99)
			             order by 1") or die(mysql_error().__FILE__.__LINE__);
	
			while($row=mysql_fetch_row($res))
			{	    
			$selected=$level==$row[0]?"SELECTED": "";
	    			
			echo "<option value=$row[0] $selected> $row[1]\n";	
			}
			?>
                          </select> ����<input type="submit" value='��������!' style="font-weight: bold">
                          �� <b><?=sprintf("%2.2f",$cost_eq)?></b> ��������.<br>
            <?
            }
        else  {    ?> ������ ���������� ������ �� ������������ � ��������������.  <? }    
            ?>
                        </form>

			<p>
                </fieldset><br>

                <fieldset>
                  <legend class="leg">�����������</legend>
			<p>
                        ����������� ����� �������� � �������������� �����������. �� ������� ���� �������� ��� ���� �������������, � ������� ����������� ������ ��� � ���. ����� �� ������ ������ ��
                        ����.<p>
                        ���������� ����������� � ���: <?=$bought_invisibility?><br>
                        <form method="post" name="invis">
                              <input type="hidden" name='todo' value='buy_invis'> ��������� ���� ����������� �� 
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
                          </select> ����<input type="submit" value='������!' style="font-weight: bold">
                        </form>

                </fieldset><br>

</div>
&nbsp;<p>
<center>
                        <input type="hidden" name="DATA1" value="yes"> 
			<input type=button onclick='window.location="/c2/url_login.php"' value="�����" class=b_l>
</center>

</form>




