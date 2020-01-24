#include <stdio.h>
#include <time.h>
#include <set>
#include <string>
#include <openssl/rsa.h>

using namespace std;
#include "st_rsa_client.h"

int main(int argc, char **argv)
//main()
{
	if(argc!=3)
	{
		printf("Usage %s N prefix\n",argv[0]);
		exit(1);
	}
	st_rsa rsa;
	int N=atoi(argv[1]);
	string prefix=argv[2];
	rsa.generate_key(N);
	FILE *f1=fopen(string(prefix+"_rsa_pub.cpp").c_str(),"wb");
	FILE *f2=fopen(string(prefix+"_rsa_priv.cpp").c_str(),"wb");
	string pub=rsa.pub_key_get();
	string priv=rsa.priv_key_get();
	unsigned char *s=(unsigned char *)pub.data();
	fprintf(f1,"static char %s_rsa_pub_key[]={",prefix.c_str());
	for(int i=0;i<pub.size();i++)
	{	
		if(i!=0)fprintf(f1,",");
		fprintf(f1,"0x%x",s[i]);
	}
	fprintf(f1,"};\n");
	fprintf(f1,"static int %s_rsa_pub_key_size=%d;",prefix.c_str(),pub.size());
	{
	unsigned char *s=(unsigned char *)priv.data();
	fprintf(f2,"static char %s_rsa_priv_key[]={",prefix.c_str());
	for(int i=0;i<priv.size();i++)
	{	
		if(i!=0)fprintf(f2,",");
		fprintf(f2,"0x%x",s[i]);
	}
	fprintf(f2,"};\n");
	fprintf(f2,"static int %s_rsa_priv_key_size=%d;",prefix.c_str(),priv.size());
	}
	fclose(f1);
	fclose(f2);
	
}
