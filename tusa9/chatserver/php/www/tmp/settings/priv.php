<?
	session_start();
        import_request_variables("gp", "arg_");
	
	include "inc/conf.php";
	include "inc/db_conn.php";
	check_conn();
     if(isset($_SESSION['login']))
     {
     	$login=$_SESSION['login'];
	$uid=$_SESSION['uid'];
     }
     if(!isset($login))
     {
     	header("Location: /");
     }
  ?>
<html>
<head>
  <meta http-equiv="PRAGMA" content="no-cache">
  <meta http-equiv="Content-Type" content="text/html; charset=windows-1251">

  <title>��� "�������"</title>
  <link rel="stylesheet" type="text/css" href="/css/main.css">
  <script language="javascript" src="/css/mmove.js" type="text/javascript">
</script>
</head>

<script  language="javascript">
<!--




//-->
</script>

<body>

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
      <?
      	list($credits,$bought_invisibility)=mysql_select1row("select credit_summa,bought_invisibility from tbl_users where id=$uid");

 	if(isset($arg_todo))	
	{
		if(isset($arg_invis_add))
		{
		if($credits>$arg_invis_add)
		{
			mysql_query("update tbl_users set credit_summa=credit_summa-$arg_invis_add,bought_invisibility=bought_invisibility+$arg_invis_add where id=$uid") or die(mysql_error());
			$error="����� ��������� ���������";
      			list($credits,$bought_invisibility)=mysql_select1row("select credit_summa,bought_invisibility from tbl_users where id=$uid");
		}
		else $error="������������ ������� �� �����";
		}
		else $error="!isset(invis_add)";
	}
      ?>
      <!--START-->

        <table width="100%" border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td class="border" align="center"><b>��������� - ����������</b></td>
          </tr>

          <tr height="5">
            <td></td>
          </tr>

          <tr>
            <td>
              <div align="justify" valign="top">
                <fieldset>
                  <legend class="leg"><big><b>�������� ���������</b></big></legend><br>
                  <input type="button" value="�������" style="font-size: 10pt" onclick="location='/settings/status.php'"> 
		  <input type="button" value="���" style="font-size: 10pt" onclick="location='/settings/chat.php'"> 
		  <input type="button" value="�����" style="font-size: 10pt" onclick="location='/settings/colors.php'"> 
		  <input type="button" value="�������" style="font-size: 10pt" onclick="location='/settings/credits.php'"> 
		  <input class="bp" type="button" value="����������" style="font-size: 10pt"><br>
                  <br>
                </fieldset>

		<?
		if(isset($error))
                	echo "<center> <font class='yelmsg'>$error</font> </center><br>\n";
		?>
		<p>
                �� ������ �������� �� ������ ���������� �� ������� ������, ����� �� �����, � ����� ������ �����������.<br>

                <p>� ��� �� ����� <b><?=sprintf("%2.2f",$credits)?></b> ��������.<br>

                <br>

                <fieldset>
                  <legend class="leg"><big><b>�����������</b></big></legend>

                  <table width="100%" border="0" cellspacing="0" cellpadding="3">
                    <tr>
                      <td>
                        ����������� ����� �������� � �������������� �����������. �� ������� ���� �������� ��� ���� �������������, � ������� ����������� ������ ��� � ���. ����� �� ������ ������ ��
                        ����.<br>
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
                            <option value="200">
                              200
                            </option>
                            <option value="500">
                              500
                            </option>
                            <option value="1000">
                              1000
                            </option>
                          </select> ����<input type="submit" value='������!' style="font-weight: bold">
                        </form>
                      </td>
                    </tr>
                  </table>
                </fieldset><br>
                <br>
              </div>
            </td>
          </tr>
        </table>

      <!--END-->
      </td>

      <td></td>

      <td>
        <?
            include 'inc/user_list.php';
        ?>
      </td><!-- up to 22 may-->
    </tr>
  </table>

  <p align="left">�</p>
  <hr>

    <?
    include 'diz/bottom_table.php';
    ?>
    
</body>
</html>
