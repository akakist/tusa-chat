<?

	$line="JKHJHKL klj <P> KJHGKJHG<P>";





function __repl($matches)
{
	switch($matches[0])
	{
case "%u0401": return "¨";
case "%u0451": return "¸";
case "%u0410": return "À";
case "%u0411": return "Á";
case "%u0412": return "Â";
case "%u0413": return "Ã";
case "%u0414": return "Ä";
case "%u0415": return "Å";
case "%u0416": return "Æ";
case "%u0417": return "Ç";
case "%u0418": return "È";
case "%u0419": return "É";
case "%u041A": return "Ê";
case "%u041B": return "Ë";
case "%u041C": return "Ì";
case "%u041D": return "Í";
case "%u041E": return "Î";
case "%u041F": return "Ï";
case "%u0420": return "Ğ";
case "%u0421": return "Ñ";
case "%u0422": return "Ò";
case "%u0423": return "Ó";
case "%u0424": return "Ô";
case "%u0425": return "Õ";
case "%u0426": return "Ö";
case "%u0427": return "×";
case "%u0428": return "Ø";
case "%u0429": return "Ù";
case "%u042A": return "Ú";
case "%u042B": return "Û";
case "%u042C": return "Ü";
case "%u042D": return "İ";
case "%u042E": return "Ş";
case "%u042F": return "ß";
case "%u0430": return "à";
case "%u0431": return "á";
case "%u0432": return "â";
case "%u0433": return "ã";
case "%u0434": return "ä";
case "%u0435": return "å";
case "%u0436": return "æ";
case "%u0437": return "ç";
case "%u0438": return "è";
case "%u0439": return "é";
case "%u043A": return "ê";
case "%u043B": return "ë";
case "%u043C": return "ì";
case "%u043D": return "í";
case "%u043E": return "î";
case "%u043F": return "ï";
case "%u0440": return "ğ";
case "%u0441": return "ñ";
case "%u0442": return "ò";
case "%u0443": return "ó";
case "%u0444": return "ô";
case "%u0445": return "õ";
case "%u0446": return "ö";
case "%u0447": return "÷";
case "%u0448": return "ø";
case "%u0449": return "ù";
case "%u044A": return "ú";
case "%u044B": return "û";
case "%u044C": return "ü";
case "%u044D": return "ı";
case "%u044E": return "ş";
case "%u044F": return "ÿ";

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