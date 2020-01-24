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
	FILE *f1=fopen(string(prefix+"_rsa_pub.bin").c_str(),"wb");
	FILE *f2=fopen(string(prefix+"_rsa_priv.bin").c_str(),"wb");
	string pub=rsa.pub_key_get();
	string priv=rsa.priv_key_get();
	fwrite(pub.data(),pub.size(),1,f1);
	fwrite(priv.data(),priv.size(),1,f2);
	fclose(f1);
	fclose(f2);
	
}
