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
//	if(!stat($pi["dirname"]))
	{
		unlink($pi["dirname"]);
		if(!mkdir($pi["dirname"],0777,true))
		{
			echo("cannot mkdir ".$pi["dirname"]."\n");
		}
		else
		echo $pi["dirname"]." created sucess \n";
	}	
//	else echo "directory already exists\n";
	

}
	
	$result=mysql_query('select url_thumb_small,url_scaled,uid,id from photos order by id');
	while (list($url_thumb_small,$url_scaled,$uid,$id)=mysql_fetch_row($result))
	{
		unset($error);
		$url_thumb_small="/var/chat".$url_thumb_small;
		$url_scaled="/var/chat".$url_scaled;
		
		if(!stat($url_thumb_small))
		{
			
//			if(stat($url_scaled))
			{
				$im=&imagecreatefromjpeg($url_scaled);
				var_dump($im);
				if(!$im){ 
					$error="LOADIMAGE";
					echo "failed lodf image\n";
				}
				if(!isset($error))
				{
					chkdir2($url_thumb_small);
				
					$dst=build_thumbnail($im,85,110);
					if(!imagejpeg($dst,$url_thumb_small)){
						echo("caNNOT WRITE JPEG ".$url_thumb_small."\n");
						$error="aNNOT WRITE JPEG";
					}
					else echo "SUCCESS thumb created $url_thumb_small\n";
				

					echo "rescale ".$url_thumb_small."\n";
				}
				
			}
			/*else
			{
			$error="SOURCE FAIL $url_scaled";
				echo $error."\n";
			}*/
			if(isset($error))
			{
				echo "\n$error\n";
				echo "rm -f $url_thumb_small $url_scaled\n";
				echo "delete from photos where id='$id';\n";
			}
		}
	}
	
?>