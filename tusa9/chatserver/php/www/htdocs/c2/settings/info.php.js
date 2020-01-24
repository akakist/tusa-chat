function on_subm()
{
	return false;
}
var country_id=0;
var region_id=0;
var city_id=0;
function select_region(f) {  
    	n = f.sel.selectedIndex;  
	country_id=f.sel.options[n].value;
	if(n){
	 	$("#location").load("/c2/aj/get_rg.php?c="+country_id);
	}
}  
function select_city(f) {  
        n = f.sel.selectedIndex;  
	region_id=f.sel.options[n].value;
	if(n){
	 	$("#location").load("/c2/aj/get_city.php?r="+region_id);
	}
}  
function do_another()
{
   	$("#location").html('<input type="text" maxlength="16" size="20" name="selother" value="">');
	$("#another").html('');
}
						    

