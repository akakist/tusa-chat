var profile_buttons_count=4;

function toggle_profile_tab(clk_tab)
{
	ct=document.getElementById("pb"+clk_tab);
	if(ct.className=="main_menu_sel") return;
	for(var i=0; i<profile_buttons_count; i++){
		if(document.getElementById("pb"+i).className=="main_menu_sel"){
			document.getElementById("pb"+i).className="main_menu_unsel";
		}
	}
	ct.className="main_menu_sel";
	var cont=document.getElementById("profile_main_content");
	cont.innerHTML="<br><br><br><br><center><img src=/images/load_wblue.gif></center><br><br><br><br>"

	var aj=CreateAjax();

	if(clk_tab==1){
		aj.open("GET","/ajax/detailed_user_info.php?id=1",false);
		aj.send(null);
		cont.innerHTML=aj.responseText;
	}
}
