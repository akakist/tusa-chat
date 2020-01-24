<?
	include 'inc/db_conn.php';
	include "inc/conf.php";
	include 'inc/cache_dir.php';
	include 'inc/build_thumbnail.php';
	check_conn();

function chkdir2($dir)
{
	echo "chkdir2 $dir\n";
	$pi=pathinfo($dir);
	echo "analize ".$pi["dirname"]."\n";
	{
		unlink($pi["dirname"]);
		if(!mkdir($pi["dirname"],0777,true))
		{
			echo("cannot mkdir ".$pi["dirname"]."\n");
		}
		else
		echo $pi["dirname"]." created sucess \n";
	}	
}
	$result=mysql_query("select id,foto_thumb_small,foto_thumb_big, has_main_foto,gender from tbl_users order by id") or die(mysql_error());
	while (list($id,$foto_thumb_small,$foto_thumb_big,$has_main_foto,$gender)=mysql_fetch_row($result))
	{
		unset($error);
		$small="/var/chat".$foto_thumb_small;
		$big="/var/chat".$foto_thumb_big;
		$psmall="/www".$foto_thumb_small;
		$pbig="/www".$foto_thumb_big;
		if(stat($psmall)) continue;
		if(stat($pbig)) continue;
		if(!stat($small) || !stat($big) || strlen($foto_thumb_small)==0 || strlen($foto_thumb_big)==0)
		{
		echo "rm -f $big $small\n";
                $thumb_big="";
                $thumb_small="";
                if($gender==2)
                {
                        $thumb_big="/pics/noimage-female-big.jpg";
                        $thumb_small="/pics/noimage-female-small.jpg";
                }
                else 
                {
                        $thumb_big="/pics/noimage-male-big.jpg";
                        $thumb_small="/pics/noimage-male-small.jpg";
                }
 			
																												 		
			mysql_query("update tbl_users set foto_thumb_small='$thumb_small',foto_thumb_big='$thumb_big',has_main_foto=0 where id='$id'") or die (mysql_error());
			
		}
	}
	
?>