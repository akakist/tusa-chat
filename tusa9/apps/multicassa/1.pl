#!/usr/bin/perl
$t=time;
for($i=0;$i<200;$i++)
{
    print `./multipay.exe`."\n";
}
print time -$t . " ". $t;