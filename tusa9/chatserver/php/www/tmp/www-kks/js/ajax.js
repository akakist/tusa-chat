var trans = [];
for (var i = 0x410; i <= 0x44F; i++) trans[i] = i - 0x350; // А-Яа-я

trans[0x401] = 0xA8;    // Ё
trans[0x451] = 0xB8;    // ё
  
// Сохраняем стандартную функцию escape()
var escapeOrig = window.escape;
  
// Переопределяем функцию escape()
window.escape = function(str)
{
	var ret = [];
	// Составляем массив кодов символов, попутно переводим кириллицу
	for (var i = 0; i < str.length; i++){
		var n = str.charCodeAt(i);
		if (typeof trans[n] != 'undefined') n = trans[n];
		if (n <= 0xFF)
			ret.push(n);
	}
	return escapeOrig(String.fromCharCode.apply(null, ret));
}


function CreateAjax()
{
	var request=null;
	if(!request) try {
		request=new ActiveXObject('Msxml2.XMLHTTP');
	}catch (e) {}

	if(!request) try {
		request=new ActiveXObject('Microsoft.XMLHTTP');
	} catch (e){}

	if(!request) try {
		request=new XMLHttpRequest();
	} catch (e){}

	if(!request) return null;
	else return request;
}

var aj=null;

function show_reg()
{
	var rr=document.getElementById("index_info");
	rr.vAlign="middle";
	rr.align="center";
	rr.innerHTML="<img src=/images/load_wblue.gif><br><br>Загрузка...";
	
	aj=CreateAjax();
	aj.open("GET","/ajax/reg_form.php",false);
	aj.send(null);
	rr.vAlign="top";
	rr.align="left";
	rr.innerHTML=aj.responseText;
}
