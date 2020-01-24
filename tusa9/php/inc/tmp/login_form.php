          <tr>
            <td align="center" class="borderg"><span lang="ru"><b>Авторизация</b></span></td>
          </tr>

          <tr>
            <td>
	    
	<form  method=POST name="start">
          <input type=hidden name="scr" value="">
          <script>
	    s=screen;
	    document.start.scr.value=s.width+'x'+s.height+'x'+s.colorDepth;
	    </script>
          <table border=0 width=100%>
            <tr>
              <td align=right width=50%><table border=0 cellpadding=1 cellspacing=0>
                <tr>
                  <td align=right>Логин:&nbsp;</td>
                  <td><input type="textfield" name="login" value="" maxlength=16 size=16>
                  </td>
                </tr>
                <tr>
                  <td align="right">Пароль:&nbsp;</td>
                  <td><input type="password" name="pass" maxlength=16 size=16>
                  </td>
                </tr>
              </table>
	      </td>
              <td width=35%>&nbsp;
                      <input name="submit" type="submit" value="Войти" onclick="if(document.start.pass.value==''){alert('Нужно ввести пароль');return false;}"></td>
              <script>
	    	document.start.login.focus();
	    </script>
            </table>
        </form>

	    
            </td>
          </tr>


