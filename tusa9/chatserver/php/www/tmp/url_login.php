<?
	session_start();
        import_request_variables("gp", "arg_");
     if(isset($_SESSION['login']))
     {
     	$login=$_SESSION['login'];
	$uid=$_SESSION['uid'];
     }
         include 'inc/db_conn.php';
	check_conn();
?>

<html>
<head>
  <meta name="generator" content="HTML Tidy for Linux/x86 (vers 11 February 2007), see www.w3.org">
  <meta http-equiv="PRAGMA" content="no-cache">
  <meta http-equiv="Content-Type" content="text/html; charset='windows-1251'">

  <title>Чат "Тусовка" - Вход</title>
  <link href="/css/main.css" rel="stylesheet" type="text/css">
  <script type="text/javascript">
<!--

  var uf=0;
  function do_f(id)
  {
        var r=Math.random();
//        locat='/userphotos/'+id;
        sx=screen.width/3*2;
        sy=screen.height/5*4;
        if(!uf || uf.closed){
                uf=open("/registration/fotki.php",'uf','');
                uf.focus();
        }
        else{
                uf.focus();
                uf.location=locat;
        }       
  //      return true;
  }
  var uni=0;
  function do_nicks(id)
  {
        var r=Math.random();
        locat='/settings_nicks';
        sx=400;//screen.width/3*2;
        sy=200;//screen.height/5*4;
        if(!uni || uni.closed){
                uni=open(locat,'uni','toolbar=0,status=0,resizable=1,scrollbars=1,width='+sx+',height='+sy);
                uni.focus();
        }
        else{
                uni.focus();
                uni.location=locat;
        }       
  //      return true;
  }

  function AddNick()
  {
        nwin=open('/newnick.tse', 'NewNick', 'toolbar=0,status=0,resizable=0,scrollbars=0,width=350,height=160');
        nwin.focus();
        return false;
  }

  function remove_nick()
  {
        d=document.loginform;
        n=document.loginform.nick.selectedIndex;
        if(!confirm('Удалить ник "'+d.nick.options[n].text+'" ?')){
                return false;
        }
        document.tempform.nick.value=d.nick.options[n].value;
        document.tempform.removenick.value='yes';
        document.tempform.submit();
        return false;
  }

  function chk_f()
  {
    if(!document.loginform.nick){return true;}
        if(document.loginform.nick.options.length==0){
                alert('У Вас нету ников для входа в чат... Создайте себе хотя бы один ник!');
                return false;
        }
        return true;
  }

  function open_n(param)
  {
    w=780;
    h=500;
    if(param!=''){
        param='?'+param;
    }
        nwin=open('/notes.tse/frames.tse'+param, 'notes', 'toolbar=0,status=0,resizable=1,scrollbars=1,left=10,top=10,width='+w+',height='+h);
        nwin.focus();
        return false;
  }

  //-->
  </script>
  <script language="javascript" src="/css/mmove.js" type="text/javascript">
</script>
</head>

<body>
<?
if(isset($arg_DATA))
{
		    	include 'inc/http_request.php';
			$channel=0;if(isset($arg_channel))$channel=$arg_channel;
			$nick=""; if(isset($arg_nick)) $nick=$arg_nick;
			$encnick=mysql_escape_string($nick);
			$ininv=0; if(isset($arg_ininv)) $ininv=$arg_ininv=="on";
			$showadm=0; if(isset($arg_showadm))$showadm=$arg_showadm=="on";
			$eye=0;if(isset($arg_eye))$eye=$arg_eye;
			$strnick=mysql_escape_string(mysql_select1("select nick from nicks where uid='$uid' and id='$nick'"));
			mysql_query("update nicks set last_usage_date=NOW() where uid='$uid' and id='$nick'");
			$sql="update tbl_users set last_channel='$channel',last_nick_id='$nick',last_nick='$strnick',setting_show_eye='$showadm', setting_neye='$eye', last_invis_state='$ininv' where id='$uid'";

			
			mysql_query($sql);
			
			$ip=$_SERVER['REMOTE_ADDR'];
			mysql_query("update tbl_users set stat_last_ip='$ip', stat_v_count=stat_v_count+1, stat_last_date=NOW() where id='$uid'");
			
			echo "<script>window.top.location='/chat/';</script>";
			


}
else 
if(isset($login))
{

		list($fname,$lname,$setting_show_eye,$setting_neye)=mysql_select1row("select fname,lname,setting_show_eye,setting_neye from tbl_users where id='$uid'");
    
    
?>
  <table border="0" width="100%" cellspacing="0" cellpadding="0">
    <?
        include 'diz/head_row.php';
    ?>

    <tr height="5">
      <td colspan="5"></td>
    </tr>

    <tr valign="top">
      <?
          include 'diz/left_col.php';
      ?>

      <td></td>

      <td>
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td class="border" align="center"><b>Здравствуйте, <?echo "$fname $lname"?></b></td>
          </tr>

          <tr height="5">
            <td></td>
          </tr>

          <tr>
            <td>
              <div align="justify" valign="top">
                <center>
                  Рады снова видеть Вас в нашем чате ;)
                </center>Здесь Вы можете создать себе <a href="#" onclick="return AddNick();">новый ник</a>, либо выбрать комнату, в которой Вы будете общаться. Например, для знакомств лучше всего
                использовать "Кусты".<br>
                Так же Вы можете изменять свои "<a href="/settings/chat.php">Настройки</a>", где можете включить/отключить полезные советы, статистику и т.п. При желании сменить информацию о себе Вы можете в
                разделе "<a href="/registration/2.php">Сменить инфу</a>".<br>
                В разделе "<a href="#" onclick="return open_n('');">Записки</a>" Вы можете написать кому-либо, к примеру, Вы не успели с кем то договорить в чате.<br>
                Кнопка "<a href="/logout.php">Выход</a>" предназначена для того чтобы завершить сессию, это Вам понадобится, например, если Вы хотите зайти под другим логином.

                <p>При помощи <a href='/settings/credits.php' target="_new"><b>кредитов Тусовки</b></a> Вы можете прибрести новый более высокий уровень, а также сменить его наименование. Также можете
                стать невидимым для остальных пользователей.</p>

                <center>
                  <a href="javascript: do_f(<?=$uid?>);"><b>Мои фотки</b></a>
                </center>    

                <center>
                  <a href="javascript: do_nicks(<?=$uid?>);"><b>Мои ники</b></a>
                </center><br>
                <br>

                <table class="border" width="100%" border="0" cellspacing="0" cellpadding="0">
                  <tr>
                    <td class="tbg" align="center" style="border-top: 0px"><b>Вход</b></td>
                  </tr>

                  <tr>
                    <td>
                      <form action="/login.tse/settings.tse" name="tempform">
                        <input type="hidden" name="removenick" value=""> <input type="hidden" name="nick" value="">
                      </form>

                      <form  method="post"  name="loginform" onsubmit="return chk_f();">
		      <input type=hidden name='DATA' value="YES">
                        <table align="center" border="0">
                          <tr height="5">
                            <td></td>
                          </tr>

                          <tr>
                            <td>
                              

                              <table align="center" border="0" cellpadding="1" cellspacing="0">
                                <tr>
                                  <td align="right">Ник: </td>

                                  <td>
				  <?
		list($last_nick,$last_channel,$level,$unread_notes,$last_invis_state)=mysql_select1row("select last_nick,last_channel,level,unread_notes,last_invis_state from tbl_users where id='$uid'");
		$max_nicks=mysql_select1("select a.nicks_count from levels a, tbl_users b where b.id='$uid' and b.level=a.id");
		$inv=mysql_select1("select a.invisibility+b.bought_invisibility from levels a, tbl_users b  where b.id='$uid' and b.level=a.id");
				  ?>
				  <SELECT name="nick"  onchange='ch_nick();' class=sl>
				  <?

		
		$sql="select id,nick from nicks where uid='$uid'";
//		echo "<p>$sql</p>";
		$result=mysql_query($sql);
		$nick_count=mysql_num_rows($result);
    		while ($row=mysql_fetch_row($result)){
		    if(count($row)==2)
		    {
			echo "<OPTION VALUE=$row[0]";
			if($row[1]==$last_nick){ echo " SELECTED";}
			echo ">$row[1]\n";
		    }
		}	
				    
				  ?>
				  </SELECT>
				  </td>

                                  <td> 
				  <?
				    if($nick_count)
				    {
					?>
					<a href="#" onclick="return remove_nick();"><img src="/pics/del.gif" border="0" width="16" height="16" alt="Удалить ник"></a>
					<?
				    }
				    if($nick_count<$max_nicks)
				    {
					?>
					<input type="button" onclick="return AddNick();" value="Добавить ник" class="b_l">
					<?
				    }
				  ?>
                                  </td>
                                </tr>

                                <tr>
                                  <td align="right">Тусуемся в: </td>

                                  <td>
				  <SELECT name="channel" class=sl><?

		$sql="select id,name from channels order by id";
		//echo "<p>$sql</p>";
		$result=mysql_query($sql);
		$nick_count=mysql_num_rows($result);
    		while ($row=mysql_fetch_row($result)){
		    if(count($row)==2)
		    {
			echo "<OPTION VALUE='$row[0]'";
			if($row[0]==$last_channel){ echo " SELECTED";}
			echo ">$row[1]\n";
		    }
		}	
				    
				  ?></SELECT>
				  
				  </td>
                                </tr>
                              </table>
                            </td>
                          </tr>

                          <tr>
                            <td align="center">
                              <input type="submit" value="Войти в чат" class="button" name="subbtn"> 
			      <? 
			      if($level>=600)
			      {
			      ?><br>
                              <br>
                              <input type="button" value="Консоль админа" onclick=
                              "n=window.open('/admin','admpage','toolbar=0,status=0,scrollbars=0,width=450,height=500,resizable=1');n.focus();">
			      <?
			        }
			      ?>
			      <script type="text/javascript">
<!--
                              document.loginform.subbtn.focus();
                              //-->
                              </script><br>
                              <?
			        if($inv>0)
				{
			      
			       echo "<input type=checkbox class=c_b name=ininv ";
			       if($last_invis_state) echo "CHECKED";
			       echo ">Войти невидимым(ой)";
			       if($level>=900)
			       {
			       
			       ?><br><input type=checkbox class=c_b name=showadm <?=$setting_show_eye?"CHECKED":""?>>Показывать 
<SELECT name="eye" > 
<OPTION value="0" <?=$setting_neye==0?"selected":""?> >Голубой глаз
<OPTION value="1" <?=$setting_neye==1?"selected":""?>>Желтый глаз
<?if($level>=1000){?>
<OPTION value="2" <?=$setting_neye==2?"selected":""?>>Красный глаз
<OPTION value="3" <?=$setting_neye==3?"selected":""?>>Зелёный глаз
<OPTION value="4" <?=$setting_neye==4?"selected":""?>>Оранжевый глаз
<?}?>
</SELECT>  глаз
			       <?
			       }

			      
				}
			       ?>
			      <br>
			      <?
			    	if($unread_notes>0)
				{
				    ?>
					У вас <?=$unread_notes?>. <a href="/notes">Читать?</a><br>
				    <?
				}
			      ?>
			      
                            </td>
                          </tr>
                        </table>
                      </form>
                    </td>
                  </tr>
                </table>

              </div>
            </td>
          </tr>
        </table>
      </td>

      <td></td>

      <td></td>

      <td>
        <?
            include 'inc/user_list.php';
        ?>

        <!--table class="border" width="140" valign="top" cellspacing="0" cellpadding="0">
          <tr>
            <td class="blr" align="center"><b>Записки:</b></td>
          </tr>

          <tr>
            <td>
              ~folders~

              <table width="100%" border="0">
                <tr>
                  <td>~newn~<b>~enewn~Новых</b></td>

                  <td nowrap>~newn~<b>~enewn~~newnotes~</b></td>
                </tr>

                <tr height="5">
                  <td colspan="2"></td>
                </tr>

                <tr>
                  <td>Всего</td>

                  <td nowrap>~allnotes~</td>
                </tr>

                <tr>
                  <td colspan="2" align="center"><input type="button" value="Записки" class="b_l" onclick="open_n('')"></td>
                </tr>
              </table>
	      
            </td>
          </tr>
        </table--><br>
      </td>
    </tr>
  </table>
  <hr>
  <?
      include 'diz/bottom_table.php';
      }// if login
      else
      {
//      var_dump($_SESSION);
        echo "<script>window.top.location='/';</script>";
      }
  ?>
  </body>
</html>
