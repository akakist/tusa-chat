
#include <stdio.h>
#include "st_stuff.h"
#include "str_lib.h"
#include "mysql_extens.h"
#include <time.h>
#include "copy_file.h"
#include "st_rsa.h"
#include "file_set.h"
#include "oscar_buffer.h"
//#include "html_out.h"
//string ss;
out_oscar_buffer b;
//oscar_buffer b2;
//vector<unsigned int> V;
char *sss[]={
"kall1",
"kall2",
"kall3",
"kall4",
"kall5",
"kall6",
"kall7",
"kall8",
"kall9",
"kalla",
"kallb1",
"kalldd1",
"kall1ert",
"kallwert1",
"kall4351",
"kall2421",
};
int main(int argc, char **argv)
{
    srand(0);
    for(unsigned int i=0;i<100;i++)
    {
	if(rand()%2)
	{
	    int k=rand()%(sizeof(sss)/sizeof(char*));
	    b<<(int)1;
	    b<<sss[k];
	    printf("%s\n",sss[k]);
	}
	else
	{
	    b<<(int)2;
	    int k=rand();
	    b<<k;
	    printf("%d\n",k);
	}
    }
    FILE *f=fopen("zzz","wb");
    fwrite(b.data(),b.size(),1,f);
    fclose(f);
    printf("----------\n");
    oscar_buffer bb(b.data(),b.size());
    for(unsigned int i=0;i<100;i++)
    {
	int c;
	bb>>c;
	if(c==1)
	{
	    string s;
	    bb>>s;
	    printf("%s\n",s.c_str());
	}
	else
	{
	    int n;
	    bb>>n;
	    printf("%d\n",n);
	}
	
    }
}
