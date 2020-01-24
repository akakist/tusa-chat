#!/usr/bin/perl
while(<>)
{
#    $a=$_;
    @r=split/\s+\@\s+/g;
    if(@r==2)
    {
	$q=$r[0];
	$a=$r[1];
	$q=~s/\"/\\\"/g;
	$q=~s/\'/\\\'/g;
	$a=~s/\"/\\\"/g;
	$a=~s/\'/\\\'/g;

	$q=~s/\n//g;
	$a=~s/\n//g;
	$q=~s/\r//g;
	$a=~s/\r//g;

	print "insert into questions (question,answer) values ('$q','$a');\n";
    }

}