<?
function http_post($addr,$port,$url,$post_content)
{
	$socket = fsockopen($addr,$port,$errno, $errstr);
	if(!$socket) {
		echo "$errstr ($errno)<br>\n";
		return "";
	}
	$len=strlen($post_content);
	$req="POST $url HTTP/1.1\r\n";
	$req.="Content-Length: $len\r\n";
	$req.="Server: PHP\r\n";
	$req.="\r\n";
	$req.=$post_content;
	fputs($socket,$req);
	$q="";
	$head=true;
	$resp="";
	while(!feof($socket)){
		if($head)
		{
		    $s=fgets($socket);
		    if($s=="\r\n")
		    {
			$head=false;
			
    		    }
		}
		else
		{
		    $s=fgetc($socket);
		    $resp.=$s;
		}
	}
	fclose($socket);
	return $resp;
}
function http_get($addr,$port,$url)
{
	$socket = fsockopen($addr,$port,$errno, $errstr);
	if(!$socket) {
		echo "$errstr ($errno)<br>\n";
		return "";
	}
	$req="GET $url HTTP/1.1\r\n";
	$req.="Server: PHP\r\n";
	$req.="\r\n";
	fputs($socket,$req);
	$q="";
	$head=true;
	$resp="";
	while(!feof($socket)){
		if($head)
		{
		    $s=fgets($socket);
		    if($s=="\r\n")
		    {
			$head=false;
			
    		    }
		}
		else
		{
		    $s=fgetc($socket);
		    $resp.=$s;
		}
	}
	fclose($socket);
	return $resp;
}
?>