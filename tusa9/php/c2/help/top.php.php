<?
        session_start();
        include "$BASE_DIR/inc/db_conn.php";
     if(isset($_SESSION['login']))
     {
        $login=$_SESSION['login'];
        $uid=intval($_SESSION['uid']);
     }
  ?>

<html>
<head>
  <meta name="generator" content="HTML Tidy for Linux/x86 (vers 11 February 2007), see www.w3.org">
  <meta http-equiv="PRAGMA" content="no-cache">
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">

  <title>Чат "Тусовка"</title>
  <link rel="stylesheet" type="text/css" href="/css/main.css">
  <script language="javascript" src="/css/mmove.js" type="text/javascript">
</script>
</head>

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
        <!--START-->

        <table width="100%" border="0" cellspacing="0" cellpadding="0" style="border-left-width: 0px; border-right-width: 0px; border-bottom-width: 0px">
          <tr>
            <td class="border" align="center" style="border-bottom-style: none; border-bottom-width: medium"><b>Рейтинг лучших игроков</b></td>
          </tr>

          <tr height="5">
            <td style="border-style: none; border-width: medium"></td>
          </tr>

          <tr>
            <td align="center" style="border-style: none; border-width: medium">
              <div align="justify" valign="top">
                <table border="1" width="737" id="table2" style="border-width: 0px" bordercolorlight="#336699" cellspacing="0" bordercolordark="#336699">
                  <tr>
                    <td style="border-style: none; border-width: medium" colspan="8">
                      <table border="1" width="100%" id="table3" style="border-width: 0px">
                        <tr>
                          <td style="border-style: none; border-width: medium" width="397">
                            <p align="center"> </p>

                            <p align="center"><b>Викторина, 01-0<span lang="ru">4</span>-2008 - 01-0<span lang="ru">7</span>-2008</b></p>
                          </td>

                          <td style="border-style: none; border-width: medium">
                            <p align="center"> </p>

                            <p align="center"><b>Мафия, 01-0<span lang="ru">4</span>-2008 - 01-0<span lang="ru">7</span>-2008</b></p>
                          </td>
                        </tr>
                      </table>
                    </td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="58"> </td>

                    <td style="border-style: none; border-width: medium" width="56">
                      <p align="center"><font color="#FFCC00">Место</font></p>
                    </td>

                    <td style="border-style: none; border-width: medium" width="135">
                      <p align="left"><font color="#FFCC00">Ник</font></p>
                    </td>

                    <td style="border-style: none; border-width: medium" width="100">
                      <p align="center"><font color="#FFCC00">Кол-во очков</font></p>
                    </td>

                    <td style="border-style: none; border-width: medium" width="56"> </td>

                    <td style="border-style: none; border-width: medium" width="61">
                      <p align="center"><font color="#FFCC00">Место</font></p>
                    </td>

                    <td style="border-style: none; border-width: medium" width="144"><font color="#FFCC00">Ник</font></td>

                    <td style="border-style: none; border-width: medium" width="111">
                      <p align="center"><font color="#FFCC00">Кол-во очков</font></p>
                    </td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="58"> </td>

                    <td style="border-style: none; border-width: medium" width="56" align="center">1</td>

                    <td width="135" style="border-style: none; border-width: medium"><font color="#6699FF"><span lang="ru">вражина</span></font></td>

                    <td style="border-style: none; border-width: medium" width="100" align="center"><span lang="ru">13076</span></td>

                    <td style="border-style: none; border-width: medium" width="56"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">1</td>

                    <td style="border-style: none; border-width: medium" width="144"><font color="#6699FF">Тuгрёна</font></td>

                    <td style="border-style: none; border-width: medium" width="111" align="center">222225</td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="58"> </td>

                    <td style="border-style: none; border-width: medium" width="56" align="center">2</td>

                    <td width="135" style="border-style: none; border-width: medium"><font color="#6699FF">Jacky</font></td>

                    <td style="border-style: none; border-width: medium" width="100" align="center"><span lang="ru">9777</span></td>

                    <td style="border-style: none; border-width: medium" width="56"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">2</td>

                    <td style="border-style: none; border-width: medium" width="144"><font color="#6699FF"><span lang="ru">Мел</span></font></td>

                    <td style="border-style: none; border-width: medium" width="111" align="center">166666</td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="58"> </td>

                    <td style="border-style: none; border-width: medium" width="56" align="center">3</td>

                    <td width="135" style="border-style: none; border-width: medium"><font color="#6699FF">degrott</font></td>

                    <td style="border-style: none; border-width: medium" width="100" align="center"><span lang="ru">8714</span></td>

                    <td style="border-style: none; border-width: medium" width="56"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center" height="23">3</td>

                    <td style="border-style: none; border-width: medium" width="144" height="23"><font color="#6699FF"><span lang="ru">Эльф</span></font></td>

                    <td style="border-style: none; border-width: medium" width="111" height="23" align="center">132499</td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="58"> </td>

                    <td style="border-style: none; border-width: medium" width="56" align="center">4</td>

                    <td width="135" style="border-style: none; border-width: medium"><font color="#6699FF">Де_Ряба</font></td>

                    <td style="border-style: none; border-width: medium" width="100" align="center"><span lang="ru">7732</span></td>

                    <td style="border-style: none; border-width: medium" width="56"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">4</td>

                    <td style="border-style: none; border-width: medium" width="144"><font color="#6699FF"><span lang="ru">Сердолик</span></font></td>

                    <td style="border-style: none; border-width: medium" width="111" align="center">104520</td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="58"> </td>

                    <td style="border-style: none; border-width: medium" width="56" align="center">5</td>

                    <td width="135" style="border-style: none; border-width: medium"><font color="#6699FF">фигля</font></td>

                    <td style="border-style: none; border-width: medium" width="100" align="center"><span lang="ru">6779</span></td>

                    <td style="border-style: none; border-width: medium" width="56"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">5</td>

                    <td style="border-style: none; border-width: medium" width="144"><font color="#6699FF">3oppo</font></td>

                    <td style="border-style: none; border-width: medium" width="111" align="center">92207</td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="58"> </td>

                    <td style="border-style: none; border-width: medium" width="56" align="center">6</td>

                    <td width="135" style="border-style: none; border-width: medium"><font color="#6699FF">EMV</font></td>

                    <td style="border-style: none; border-width: medium" width="100" align="center"><span lang="ru">6350</span></td>

                    <td style="border-style: none; border-width: medium" width="56"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">6</td>

                    <td style="border-style: none; border-width: medium" width="144"><font color="#6699FF">Dst</font></td>

                    <td style="border-style: none; border-width: medium" width="111" align="center">88008</td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="58" height="24"> </td>

                    <td style="border-style: none; border-width: medium" width="56" height="24" align="center">7</td>

                    <td width="135" height="24" style="border-style: none; border-width: medium"><font color="#6699FF">Гамма</font></td>

                    <td style="border-style: none; border-width: medium" width="100" align="center" height="24"><span lang="ru">5223</span></td>

                    <td style="border-style: none; border-width: medium" width="56" height="24"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">7</td>

                    <td style="border-style: none; border-width: medium" width="144"><font color="#6699FF">Галечка</font></td>

                    <td style="border-style: none; border-width: medium" width="111" align="center">85826</td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="58"> </td>

                    <td style="border-style: none; border-width: medium" width="56" align="center">8</td>

                    <td width="135" style="border-style: none; border-width: medium"><font color="#6699FF">Юля_Зуева</font></td>

                    <td style="border-style: none; border-width: medium" width="100" align="center"><span lang="ru">5050</span></td>

                    <td style="border-style: none; border-width: medium" width="56"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">8</td>

                    <td style="border-style: none; border-width: medium" width="144"><font color="#6699FF">Casino</font></td>

                    <td style="border-style: none; border-width: medium" width="111" align="center">82948</td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="58"> </td>

                    <td style="border-style: none; border-width: medium" width="56" align="center">9</td>

                    <td width="135" style="border-style: none; border-width: medium"><font color="#6699FF">Хе*льга</font></td>

                    <td style="border-style: none; border-width: medium" width="100" align="center"><span lang="ru">4666</span></td>

                    <td style="border-style: none; border-width: medium" width="56"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">9</td>

                    <td style="border-style: none; border-width: medium" width="144"><font color="#6699FF">AizavaMaki</font></td>

                    <td style="border-style: none; border-width: medium" width="111" align="center">82695</td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="58"> </td>

                    <td style="border-style: none; border-width: medium" width="56" align="center">10</td>

                    <td width="135" style="border-style: none; border-width: medium"><font color="#6699FF">track</font></td>

                    <td style="border-style: none; border-width: medium" width="100" align="center"><span lang="ru">3900</span></td>

                    <td style="border-style: none; border-width: medium" width="56"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">10</td>

                    <td style="border-style: none; border-width: medium" width="144"><font color="#6699FF">Самолюбие</font></td>

                    <td style="border-style: none; border-width: medium" width="111" align="center">81273</td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="58"> </td>

                    <td style="border-style: none; border-width: medium" width="56" align="center"> </td>

                    <td width="135" style="border-style: none; border-width: medium">
                       

                      <p> </p>
                    </td>

                    <td style="border-style: none; border-width: medium" width="100" align="center"> </td>

                    <td style="border-style: none; border-width: medium" width="56"> </td>

                    <td style="border-style: none; border-width: medium" width="61"> </td>

                    <td style="border-style: none; border-width: medium" width="144"> </td>

                    <td style="border-style: none; border-width: medium" width="111"> </td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="353" colspan="4">
                      <p align="center"><b>Викторина, 01-01-2008 - 01-04-2008</b></p>
                    </td>

                    <td style="border-style: none; border-width: medium" width="378" colspan="4">
                      <p align="center"><b>Мафия, 01-01-2008 - 01-04-2008</b></p>
                    </td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="50"> </td>

                    <td style="border-style: none; border-width: medium" width="66">
                      <p align="center"><font color="#FFCC00">Место</font></p>
                    </td>

                    <td style="border-style: none; border-width: medium" width="179">
                      <p align="left"><font color="#FFCC00">Ник</font></p>
                    </td>

                    <td style="border-style: none; border-width: medium" width="98">
                      <p align="center"><font color="#FFCC00">Кол-во очков</font></p>
                    </td>

                    <td style="border-style: none; border-width: medium" width="69"> </td>

                    <td style="border-style: none; border-width: medium" width="61">
                      <p align="center"><font color="#FFCC00">Место</font></p>
                    </td>

                    <td style="border-style: none; border-width: medium" width="139"><font color="#FFCC00">Ник</font></td>

                    <td style="border-style: none; border-width: medium" width="98">
                      <p align="center"><font color="#FFCC00">Кол-во очков</font></p>
                    </td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="50"> </td>

                    <td style="border-style: none; border-width: medium" width="66" align="center">1</td>

                    <td width="179" style="border-style: none; border-width: medium"><font color="#6699FF">кЦ</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center">14502</td>

                    <td style="border-style: none; border-width: medium" width="69"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">1</td>

                    <td style="border-style: none; border-width: medium" width="139"><font color="#6699FF">МиKKa</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center"><span lang="en-us">250000</span></td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="50"> </td>

                    <td style="border-style: none; border-width: medium" width="66" align="center">2</td>

                    <td width="179" style="border-style: none; border-width: medium"><font color="#6699FF">lonny</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center">8393</td>

                    <td style="border-style: none; border-width: medium" width="69"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">2</td>

                    <td style="border-style: none; border-width: medium" width="139"><font color="#6699FF">Тuгрёна</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center"><span lang="en-us">204006</span></td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="50"> </td>

                    <td style="border-style: none; border-width: medium" width="66" align="center">3</td>

                    <td width="179" style="border-style: none; border-width: medium"><font color="#6699FF">фигля</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center">8356</td>

                    <td style="border-style: none; border-width: medium" width="69"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center" height="23">3</td>

                    <td style="border-style: none; border-width: medium" width="139" height="23"><font color="#6699FF">Басман</font></td>

                    <td style="border-style: none; border-width: medium" width="98" height="23" align="center"><span lang="en-us">123124</span></td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="50"> </td>

                    <td style="border-style: none; border-width: medium" width="66" align="center">4</td>

                    <td width="179" style="border-style: none; border-width: medium"><font color="#6699FF">Jacky</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center">7872</td>

                    <td style="border-style: none; border-width: medium" width="69"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">4</td>

                    <td style="border-style: none; border-width: medium" width="139"><font color="#6699FF"><span lang="en-us">Dst</span></font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center"><span lang="en-us">103548</span></td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="50"> </td>

                    <td style="border-style: none; border-width: medium" width="66" align="center">5</td>

                    <td width="179" style="border-style: none; border-width: medium"><font color="#6699FF">Deja-vu</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center">7773</td>

                    <td style="border-style: none; border-width: medium" width="69"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">5</td>

                    <td style="border-style: none; border-width: medium" width="139"><font color="#6699FF">Пошлость</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center"><span lang="en-us">100516</span></td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="50"> </td>

                    <td style="border-style: none; border-width: medium" width="66" align="center">6</td>

                    <td width="179" style="border-style: none; border-width: medium"><font color="#6699FF">ндец</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center">5979</td>

                    <td style="border-style: none; border-width: medium" width="69"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">6</td>

                    <td style="border-style: none; border-width: medium" width="139"><font color="#6699FF">АцтеГ</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center"><span lang="en-us">100368</span></td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="50" height="24"> </td>

                    <td style="border-style: none; border-width: medium" width="66" height="24" align="center">7</td>

                    <td width="179" height="24" style="border-style: none; border-width: medium"><font color="#6699FF">Хе*льга</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center" height="24">5355</td>

                    <td style="border-style: none; border-width: medium" width="69" height="24"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">7</td>

                    <td style="border-style: none; border-width: medium" width="139"><font color="#6699FF">PupSi_ЖенюсЯ</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center"><span lang="en-us">99662</span></td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="50"> </td>

                    <td style="border-style: none; border-width: medium" width="66" align="center">8</td>

                    <td width="179" style="border-style: none; border-width: medium"><font color="#6699FF">Lidija</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center">5193</td>

                    <td style="border-style: none; border-width: medium" width="69"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">8</td>

                    <td style="border-style: none; border-width: medium" width="139"><font color="#6699FF">прелестный</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center"><span lang="en-us">97930</span></td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="50"> </td>

                    <td style="border-style: none; border-width: medium" width="66" align="center">9</td>

                    <td width="179" style="border-style: none; border-width: medium"><font color="#6699FF">СОЛДАТ_ка</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center">4872</td>

                    <td style="border-style: none; border-width: medium" width="69"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">9</td>

                    <td style="border-style: none; border-width: medium" width="139"><font color="#6699FF">Галюсик</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center"><span lang="en-us">92448</span></td>
                  </tr>

                  <tr>
                    <td style="border-style: none; border-width: medium" width="50"> </td>

                    <td style="border-style: none; border-width: medium" width="66" align="center">10</td>

                    <td width="179" style="border-style: none; border-width: medium"><font color="#6699FF">Крейсер</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center">4492</td>

                    <td style="border-style: none; border-width: medium" width="69"> </td>

                    <td style="border-style: none; border-width: medium" width="61" align="center">10</td>

                    <td style="border-style: none; border-width: medium" width="139"><font color="#6699FF">Самолюбие</font></td>

                    <td style="border-style: none; border-width: medium" width="98" align="center"><span lang="en-us">92288</span></td>
                  </tr>
                </table>

                <p align="right"><br>
                <b>Топы игроков других периодов можно посмотреть <a href="oldtop.html">тут.</a></b><br>
                 </p>
              </div>
            </td>
          </tr>
        </table><!--END-->
      </td>

      <td></td>

      <td><?
                  include '$BASE_DIR/inc/user_list.php';
              ?>
      </td><!-- up to 22 may-->
    </tr>
  </table>

  <p align="left"> </p>
  <hr>
  <?
      include 'diz/bottom_table.php';
      ?>
  </body>
</html>
