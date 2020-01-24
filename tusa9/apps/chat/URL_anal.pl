#!/usr/bin/perl
my %u;
my %ips;
while(<>)
{
    @r=split /\s/;
    if(length(@r)>0)
    {
	$u{$r[0]}++;
	
	$ips{$r[length(@r)-1]}++;
    }
}
foreach(sort keys %u)
{
    unless (/\/photos\// || /\/attach\// || /\/attachs\//)
    {
    print "$_ $u{$_}\n";
    }
}
#printf "TOTAL IP COUNT %d\n",length(ips));
foreach(sort keys %ips)
{
    print "$_ $ips{$_}\n";

}
