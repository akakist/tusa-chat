<div class='first-line'>�����������</div>

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
	<legend>��������� �� ������� ������ � ����</legend> 
	<table border="0" cellspacing="0" cellpadding="5">
	<tr>
		<td>���� ���:</td>
		 <td class=r><input type="text" maxlength="16" size="20" name="name" value='<?=$name?>' > <!--'<??> '--> </td>
		 <td class=r><input id=hide_name type=checkbox name=hide_name class=c_b <?if($hide_name) echo "CHECKED" ?> > <label for=hide_name>������ ���</label></td>
	</tr>
	<tr>
		<td align="right">��� ���</td>
		<td class=r>  	

				<select name=gn>
				<?
					if($gn==0) $gn=1;
					if($gn==1)
					  {
					    echo "<OPTION value=1 SELECTED> �������";
 					    echo "<OPTION value=2> �������";
					  }
					else
					  {
					    echo "<OPTION value=1> �������";
 					    echo "<OPTION value=2 SELECTED> �������";
					  }
				?>

				</select>


	<tr>
		<td align="right">���� ��������</td>
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

					if($bm==1)	  {    echo "<OPTION value=1 SELECTED> ������";   }
					else		  {    echo "<OPTION value=1> ������";		  }
					if($bm==2)	  {    echo "<OPTION value=2 SELECTED> �������";   }
					else		  {    echo "<OPTION value=3> �������";		  }
					if($bm==3)	  {    echo "<OPTION value=3 SELECTED> �����";   }
					else		  {    echo "<OPTION value=3> �����";		  }
					if($bm==4)	  {    echo "<OPTION value=4 SELECTED> ������";   }
					else		  {    echo "<OPTION value=4> ������";		  }
					if($bm==5)	  {    echo "<OPTION value=5 SELECTED> ���";   }
					else		  {    echo "<OPTION value=5> ���";		  }
					if($bm==6)	  {    echo "<OPTION value=6 SELECTED> ����";   }
					else		  {    echo "<OPTION value=6> ����";		  }
					if($bm==7)	  {    echo "<OPTION value=7 SELECTED> ����";   }
					else		  {    echo "<OPTION value=7> ����";		  }
					if($bm==8)	  {    echo "<OPTION value=8 SELECTED> �������";   }
					else		  {    echo "<OPTION value=8> �������";		  }
					if($bm==9)	  {    echo "<OPTION value=9 SELECTED> ��������";   }
					else		  {    echo "<OPTION value=9> ��������";	  }
					if($bm==10)	  {    echo "<OPTION value=10 SELECTED> �������";   }
					else		  {    echo "<OPTION value=10> �������";		  }
					if($bm==11)	  {    echo "<OPTION value=11 SELECTED> ������";   }
					else		  {    echo "<OPTION value=11> ������";		  }
					if($bm==12)	  {    echo "<OPTION value=12 SELECTED> �������";   }
					else		  {    echo "<OPTION value=12> �������";		  }

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
		 <td class=r><input type=checkbox id=hide_bd name=hide_bd class=c_b <?if($hide_bdate) echo 'CHECKED'?> > <label for=hide_bd>������ ���� ��������</label></td>
	 </tr>
	<tr>
		<td>��� �����</td>
 	        <td class=r><input type="text" maxlength="16" size="20" name="city" value='<?=$city?>' > <!--'<??> '--> </td>
	</tr>
	 </table>	
<div style='padding-left:50px'>
<p style='height: 3px'></p>
	������� � ����: 
<p style='height: 3px'></p>
	 <textarea cols=50 rows=10 name=info style='font-size:10px'><?=$info?></textarea>
</div>	 
	 <br>
<center>
<p style='height: 3px'></p>
<input type="hidden" name="DATA1" value="yes"> 
			<input type="submit" value="��������" name="reg">
<?
	if(!isset($_SESSION["rega"]))
	{
		?>
			<input type=button onclick='window.location="/c2/url_login.php"' value="�����" class=b_l>			
		<?
	}
	else
	{
	?>
		<input type=button onclick='window.location="/c2/settings/fotki.php"' value="����������" class=b_l>			
	<?
	}
?>
</center>
			 
</fieldset>
</form>
