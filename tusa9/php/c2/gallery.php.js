
function move_to_trash(pid)
{
	document.frem.remf.value+="_"+pid;
	document.getElementById('trash').innerHTML+=document.getElementById('ph'+pid).innerHTML;
	document.getElementById('ph'+pid).innerHTML="";
	$("#trash > .cross").empty();
	$("#trash").show();
	return false;
}

function opwin(l,w,h)
{
	var ow=open(l,'owusr','toolbar=0,status=0,resizable=1,scrollbars=1,width='+w+',height='+h);
	ow.focus();
}

