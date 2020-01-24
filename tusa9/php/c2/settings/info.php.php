<div class='first-line'>Регистрация</div>

<?
		if(isset($error))
		{
			?>
			<div class=error><?=$error?></div>
			<?
		}
		else
		{	
		}
?>		
	
<form method="post" name="form1">
<fieldset>
	<legend>Заполните по желанию данные о себе</legend> 
	<table border="0" cellspacing="0" cellpadding="5">
	<tr>
		<td>Ваше имя:</td>
		 <td class=r><input type="text" maxlength="16" size="20" name="name" value='<?=$name?>' > <!--'<??> '--> </td>
		 <td class=r><input id=hide_name type=checkbox name=hide_name class=c_b <?if($hide_name) echo "CHECKED" ?> > <label for=hide_name>скрыть имя</label></td>
	</tr>
	<tr>
		<td align="right">Ваш пол</td>
		<td class=r>  	

				<select name=gn>
				<?
					if($gn==0) $gn=1;
					if($gn==1)
					  {
					    echo "<OPTION value=1 SELECTED> мужской";
 					    echo "<OPTION value=2> женский";
					  }
					else
					  {
					    echo "<OPTION value=1> мужской";
 					    echo "<OPTION value=2 SELECTED> женский";
					  }
				?>

				</select>


	<tr>
		<td align="right">Дата рождения</td>
		<td class=r>  	
		 		<select name=bd>
				<?
					for($i=1;$i<=31;$i++)
					{
						if($i==$bd)
						echo "<OPTION value=$i SELECTED> ".sprintf("%02d",$i)."\n";
						else
						echo "<OPTION value=$i> ".sprintf("%02d",$i)."\n";
					}
				?>
				</select>

				<select name=bm>
				<?

					if($bm==1)	  {    echo "<OPTION value=1 SELECTED> января";   }
					else		  {    echo "<OPTION value=1> января";		  }
					if($bm==2)	  {    echo "<OPTION value=2 SELECTED> февраля";   }
					else		  {    echo "<OPTION value=3> февраля";		  }
					if($bm==3)	  {    echo "<OPTION value=3 SELECTED> марта";   }
					else		  {    echo "<OPTION value=3> марта";		  }
					if($bm==4)	  {    echo "<OPTION value=4 SELECTED> апреля";   }
					else		  {    echo "<OPTION value=4> апреля";		  }
					if($bm==5)	  {    echo "<OPTION value=5 SELECTED> мая";   }
					else		  {    echo "<OPTION value=5> мая";		  }
					if($bm==6)	  {    echo "<OPTION value=6 SELECTED> июня";   }
					else		  {    echo "<OPTION value=6> июня";		  }
					if($bm==7)	  {    echo "<OPTION value=7 SELECTED> июля";   }
					else		  {    echo "<OPTION value=7> июля";		  }
					if($bm==8)	  {    echo "<OPTION value=8 SELECTED> августа";   }
					else		  {    echo "<OPTION value=8> августа";		  }
					if($bm==9)	  {    echo "<OPTION value=9 SELECTED> сентября";   }
					else		  {    echo "<OPTION value=9> сентября";	  }
					if($bm==10)	  {    echo "<OPTION value=10 SELECTED> октября";   }
					else		  {    echo "<OPTION value=10> октября";		  }
					if($bm==11)	  {    echo "<OPTION value=11 SELECTED> ноября";   }
					else		  {    echo "<OPTION value=11> ноября";		  }
					if($bm==12)	  {    echo "<OPTION value=12 SELECTED> декабря";   }
					else		  {    echo "<OPTION value=12> декабря";		  }

				?>

				</select>

				<select name=by>
				<?
					if(!isset($by)) $by=1985;
					for($i=1900;$i<2009;$i++)
					{
						if($i==$by)
							echo "<OPTION value=$i SELECTED> $i\n";
						else 
							echo "<OPTION value=$i> $i\n";
					}
				?>
				</select>
			 
		</td>
		 <td class=r><input type=checkbox id=hide_bd name=hide_bd class=c_b <?if($hide_bdate) echo 'CHECKED'?> > <label for=hide_bd>скрыть дату рождения</label></td>
	 </tr>
	<tr>
		<td>Мой город</td>
 	        <td class=r><input type="text" maxlength="16" size="20" name="city" value='<?=$city?>' > <!--'<??> '--> </td>
	</tr>
	 </table>	
<div style='padding-left:50px'>
<p style='height: 3px'></p>
	Немного о себе: 
<p style='height: 3px'></p>
	 <textarea cols=50 rows=10 name=info style='font-size:10px'><?=$info?></textarea>
</div>	 
	 <br>
<center>
<p style='height: 3px'></p>
<input type="hidden" name="DATA1" value="yes"> 
			<input type="submit" value="Изменить" name="reg">
<?
	if(!isset($_SESSION["rega"]))
	{
		?>
			<input type=button onclick='window.location="/c2/url_login.php"' value="Назад" class=b_l>			
		<?
	}
	else
	{
	?>
		<input type=button onclick='window.location="/c2/settings/fotki.php"' value="Продолжить" class=b_l>			
	<?
	}
?>
</center>
			 
</fieldset>
</form>
