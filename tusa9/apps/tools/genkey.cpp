#include <stdio.h>
#include "str_lib.h"
#include "st_stuff.h"
main()
{
	srand(time(NULL)+getpid());
	unsigned long  k1=rand();
	unsigned long  k2=rand();
	unsigned long  k3=rand();
	string s1((char*)&k1,4);
	string s2((char*)&k2,4);
	string s3((char*)&k3,4);
	
	string s=Base64Encode(s1+s2+s3);
	string o;
	int j=0;
	for(unsigned int i=0;i<s.size()&&j<8;i++)
	{
		if(s[i]!='/'&&s[i]!=','&&s[i]!='='&&s[i]!='+'){o+=s[i];j++;}
	}
	
	printf("o=%s\n",o.c_str());
	st_FILE f("/root/des.key","wb");
	f<<o;
	printf("\n%u\n",0xffffffff/3600);
}
