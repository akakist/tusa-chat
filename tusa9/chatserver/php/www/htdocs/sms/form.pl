#!/usr/bin/perl
while(<>)
{
    @r=split /;/;
    $n=@r;
    if($n>5)
    {
	my $ll;
	sprintf($ll,"%2.2f",$r[4]);
	print "<tr><td>$r[0]</td><td>$r[1]</td><td>$r[2]</td><td>$r[3]</td><td>$ll</td></tr>\n";
    }
}