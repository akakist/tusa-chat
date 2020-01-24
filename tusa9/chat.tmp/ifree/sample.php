#!/usr/bin/php

<?
/* 
    opcode=credit credits added format of content
	login=strLogin;added=strAdded;remainder=strReminder
    opcode=leader	
	login=strLogin;channel=strChannel
*/
// if status==0
function MazarError($data)
{
    return "Oshibka w zaprose $data";
}
function MazarResponse($opcode,$content)
{

    $r=split(';',$content);
//     $m['zz']='333';
    if($opcode=='credit')
    {
	$added;
	$login;
	$reminder;
	for($i=0;$i<count($r);$i++)
	{
	    $rr=split('=',$r[$i]);
	    if(count($rr)==2)
	    {
		if($rr[0]=='added') $added=$rr[1];
		if($rr[0]=='login') $login=$rr[1];
		if($rr[0]=='remainder') $remainder=$rr[1];
	    }
	}
	return "za4isleno $added kreditov na login '$login', ostatok na s4etu $remainder";
    }
    else if($opcode=='leader')
    {
	$login;
	$channel;
	for($i=0;$i<count($r);$i++)
	{
	    $rr=split('=',$r[$i]);
	    if(count($rr)==2)
	    {
		if($rr[0]=='channel') $channel=$rr[1];
		if($rr[0]=='login') $login=$rr[1];
	    }
	}
	return "Login '$login' stal liderom na kanale '$channel'";
    }
}
    
echo MazarResponse("credit","login=ser_bel;added=1022.00;remainder=23500.99")."\n";
echo MazarResponse("leader","login=ser_bel;channel=tusovka")."\n";
?>