function swap_div(name)
{
	if(document.getElementById(name).style.display=='none')
	{
		document.getElementById(name).style.display='';
	}
	else
	{
		document.getElementById(name).style.display='none';
	}
	
}

function swap_div_url(name,url)
{
	if(document.getElementById(name).style.display=='none')
	{
		$("#"+name).load(url);
		document.getElementById(name).style.display='';
	}
	else
	{
		document.getElementById(name).style.display='none';
	}
	
}
