function InviteUser(fn,u)
{
	if (u==''){return false;}
	var z=prompt('Послание для '+fn+':','');
	if (z==null){return false;}
        $.post("/invite_user.tse",{
		msg: escape(z),
		id: escape(u),
              	r: Math.random()
        });
	return false;
}
