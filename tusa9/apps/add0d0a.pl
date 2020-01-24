#!/usr/bin/perl

undef $/;
$b=<>;
@r=split /\n/,$b;
foreach $n(@r)
{
	open(F,$n)||next;
	my @out;

	while(<F>)
	{
		s/\x0a/\x0d\x0a/g;
		push @out,$_;
	}
	close(F);
	open(F,">$n");
	print F @out;
	close($f);

}
