#!/usr/bin/perl

#@r=<>;
my %m;
$a=`ldd /usr/local/bin/mc`;
    $m{"/usr/local/bin/mc"}=1;
@r=split(/\s/,$a);
foreach(@r)
{
    if(/^\//)    
    {
    $m{$_}=1;
	$aa=`ldd $_`;
	@rr=split(/\s/,$aa);
	foreach(@rr)
	{
	    $m{$_}=1 if(/^\//)    ;
	
	}

#    print;
    }
#    if($_[0] eq '/'){ print;}
}
print join("\n",keys %m);
#print values %m;