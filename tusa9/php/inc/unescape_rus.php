<?

	$line="JKHJHKL klj <P> KJHGKJHG<P>";





function __repl($matches)
{
	switch($matches[0])
	{
case "%u0401": return "�";
case "%u0451": return "�";
case "%u0410": return "�";
case "%u0411": return "�";
case "%u0412": return "�";
case "%u0413": return "�";
case "%u0414": return "�";
case "%u0415": return "�";
case "%u0416": return "�";
case "%u0417": return "�";
case "%u0418": return "�";
case "%u0419": return "�";
case "%u041A": return "�";
case "%u041B": return "�";
case "%u041C": return "�";
case "%u041D": return "�";
case "%u041E": return "�";
case "%u041F": return "�";
case "%u0420": return "�";
case "%u0421": return "�";
case "%u0422": return "�";
case "%u0423": return "�";
case "%u0424": return "�";
case "%u0425": return "�";
case "%u0426": return "�";
case "%u0427": return "�";
case "%u0428": return "�";
case "%u0429": return "�";
case "%u042A": return "�";
case "%u042B": return "�";
case "%u042C": return "�";
case "%u042D": return "�";
case "%u042E": return "�";
case "%u042F": return "�";
case "%u0430": return "�";
case "%u0431": return "�";
case "%u0432": return "�";
case "%u0433": return "�";
case "%u0434": return "�";
case "%u0435": return "�";
case "%u0436": return "�";
case "%u0437": return "�";
case "%u0438": return "�";
case "%u0439": return "�";
case "%u043A": return "�";
case "%u043B": return "�";
case "%u043C": return "�";
case "%u043D": return "�";
case "%u043E": return "�";
case "%u043F": return "�";
case "%u0440": return "�";
case "%u0441": return "�";
case "%u0442": return "�";
case "%u0443": return "�";
case "%u0444": return "�";
case "%u0445": return "�";
case "%u0446": return "�";
case "%u0447": return "�";
case "%u0448": return "�";
case "%u0449": return "�";
case "%u044A": return "�";
case "%u044B": return "�";
case "%u044C": return "�";
case "%u044D": return "�";
case "%u044E": return "�";
case "%u044F": return "�";

default: return $matches[0];
	}
}
function __r2($n)
{
	 switch($n[0])
	 {
case "%20": return " ";
case "%21": return "!";
case "%22": return "\"";
case "%23": return "#";
case "%24": return "$";
case "%25": return "%";
case "%26": return "&";
case "%27": return "'";
case "%28": return "(";
case "%29": return ")";
case "%2A": return "*";
case "%2B": return "+";
case "%2C": return ",";
case "%2D": return "-";
case "%2E": return ".";
case "%2F": return "/";
case "%3A": return ":";
case "%3B": return ";";
case "%3C": return "<";
case "%3D": return "=";
case "%3E": return ">";
case "%3F": return "?";
case "%40": return "@";
case "%7B": return "{";
case "%7C": return "|";
case "%7D": return "}";
case "%7E": return "~";
case "%5B": return "[";
case "%5C": return "\\";
case "%5D": return "]";
case "%5E": return "^";
case "%5F": return "_";
case "%60": return "`";

		
		default: return $n[0];
	 }
}
//     $line="%u044Fsdfgsdfg%u0443%u0444%u0445%u0446%u0447%u0448%u0449";


     	function unescape_rus($line)
     	{

     		$r=preg_replace_callback('/\%u[0-9A-H]{4}/','__repl',$line);

     		$r2=preg_replace_callback('/\%[0-9A-H]{2}/','__r2',$r);
		return $r2;
	}	
?>