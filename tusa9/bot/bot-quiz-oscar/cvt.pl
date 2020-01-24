#!/usr/bin/perl
while(<>)
{
    @r=split /\@/,$_;
    $q=$r[0];
    $a=$r[1];
    $a=~s/[\r\n]//g;
    $q=~s/\'/\\\'/g;
    $q=~s/\"/\\\"/g;
    $a=~s/\'/\\\'/g;
    $a=~s/\"/\\\"/g;
    $a=~s/;//g;
    $q=~s/;//g;
    print "insert into questions (question,answer) values ('$q','$a');\n";
}