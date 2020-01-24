function move_to_trash(pid)
{
	document.frem.remf.value+="_"+pid;
	document.getElementById('trash').innerHTML+=document.getElementById('ph'+pid).innerHTML;
	document.getElementById('ph'+pid).innerHTML="";
	$("#trash > .cross").empty();
	$("#trash").show();
	return false;
}
function on_remove()
{
	return true;
}
function on_subm()
{
	return false;
}

