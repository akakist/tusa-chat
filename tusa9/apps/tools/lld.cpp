#include <iconv.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "str_lib.h"
#include "file_set.h"
#include <cerrno>
using namespace std;
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("\nusage: lld file\n");
		exit(1);
	}
	
	string fn=argv[1];
	
	vector<string> v=splitTOK(".",argv[1]);
	char *f="cp1251";
	char *t="utf8";
	string toname;
	if(v.size())
	{
		if(v[v.size()-1]=="utf")
		{
			f="utf8";
			t="cp1251";
			vector<string>w;
			for(unsigned i=0;i<v.size()-1;i++)
			 w.push_back(v[i]);
			 
			toname=join(".",w);
		}
		else toname=fn+".utf";
		
	}
	if(toname=="") toname=fn+".utf";
	char s[300];
	sprintf(s,"iconv --from-code=%s --to-code=%s %s > %s",f,t,fn.c_str(),toname.c_str());
	printf("%s\n",s);
	system(s);
/*	iconv_t it=iconv_open(t, f);
	string inbuf;
	if(load_1_file(inbuf,fn)==-1)
	{
		printf("error loading %s\n",fn.c_str());
		abort();
	}
	char *in=(char*)inbuf.data();
	char *out_orig=new char(inbuf.size()*2);
	char *out=out_orig;
	size_t inl=inbuf.size();
	size_t outl=inbuf.size()*2;
	while(inl)
	{
		printf("KALL\n");
		int err=iconv(it,&in,&inl,&out,&outl);
		if(err==-1)
		{
			printf("errno %d\n",errno);
		}
	}
	string res=string(out_orig,inbuf.size()*2-outl);
	FILE *fl=fopen(toname.c_str(),"wb");
	fwrite(res.data(),1,res.size(),fl);
	fclose(fl);
	*/

}