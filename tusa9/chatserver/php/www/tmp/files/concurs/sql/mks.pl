#!/usr/bin/perl
while(<>)
{
	@r=split /\s+/;
	print "insert into concurs_ucha values ('$r[0]','$r[1]','$r[2]');\n";
}