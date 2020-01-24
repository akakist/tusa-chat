#include <sys/types.h>
#include <ctime>
#include <time.h>
#include <ctype.h>
#include <string>
#include "st_rsa.h"
#include "st_stuff.h"
#include <iostream>
using namespace std;

string
randstr ()
{
  srand (time (NULL));
  int len = rand () % 512;
  char b[1024];
  for (int i = 0; i < 1024; i++)
    {
      b[i] = rand () & 0xff;
    }
  for (int i = 0, j = 0; i < 1024; i++)
    {
      if (isalnum (b[i]))
	{
	  b[j] = b[i];
	  j++;
	}
    }
  b[len] = 0;
  return b;
}
bool cert_auth_get_data(string& signer_name,string& passwd,string&  passwd1,
					string&  org, string& prefix,int &bits)
{
			cout<<"Enter your name:";
			getline(cin,signer_name);
			cout<<"Enter passwd:";
			getline(cin,passwd);
			cout<<"Confirm passwd:";
			getline(cin,passwd1);
			cout<<"Enter organization:";
			getline(cin,org);
			cout<<"Key prefix:";
			getline(cin,prefix);
			string b;
			cout<<"Bits:";
			getline(cin,b);
			bits=atoi(b);
return true;
}
void do_cert_auth()

{

			string signer_name,passwd, passwd1, org, prefix;
			int  bits;
			start:
			if(cert_auth_get_data(signer_name,passwd, passwd1, org, prefix,bits))
			{
					if(passwd!=passwd1)
					{
						cerr<<"password not matched"<<endl;
						exit(1);
					}

						st_rsa rsa;
						rsa.generate_key(bits);
						string CA;
						CA+="/SIGNER_NAME="+signer_name+"\n";
						CA+=(string)"/SIGNER_ORGANIZATION="+org+"\n";
						CA+=(string)"/KEY_LEN="+itostring(bits)+"\n";
						CA+=(string)"/KEY_ID="+prefix+"\n";
						string 	priv_str=bin2hex(rsa.priv_key_get(),0),
								pub_str=bin2hex(rsa.pub_key_get(),0);
						
						string pubCA=CA,privCA=CA;
						pubCA+="/PUBLIC_KEY="+pub_str+"\n";
						privCA+="/PRIVATE_KEY="+priv_str+"\n";
						string md5pubCA=MD5(pubCA);
						string md5privCA=MD5(privCA);
						string md5passwd=MD5(passwd);
						string out_priv_CA_bin=randstr()+"\n"+
											"/BEGIN_CERTIFICATE_AUTHORITY\n"+
											privCA+
											"/END_CERTIFICATE_AUTHORITY\n"+
											"/MD5_CHECK_SUM="+bin2hex(md5privCA,0);
						string out_pub_CA_bin="/BEGIN_CERTIFICATE_AUTHORITY\n"+
											pubCA+
											"/END_CERTIFICATE_AUTHORITY\n"+
											"/MD5_CHECK_SUM="+bin2hex(md5pubCA,0);
						string out_priv_CA_bin_encoded;
						
						for(int i=0;i<out_priv_CA_bin.size();i++)
						{
							out_priv_CA_bin_encoded+=out_priv_CA_bin[i]^md5passwd[i%MD5_DIGEST_LENGTH];
						}					
//						st_malloc out_priv_CA_bin_encoded_64(out_priv_CA_bin.size()*2);
						
						string out_priv_CA_bin_encoded_64=
							Base64Encode(out_priv_CA_bin_encoded);
						
						{
							string  fname=prefix+".priv_CA";
							st_FILE f(fname,"wb");
							f.write(out_priv_CA_bin_encoded_64.data(),out_priv_CA_bin_encoded_64.size());
						}
						{
							string fname=prefix+".pub_CA";
							st_FILE f(fname,"wb");
							f.write(out_pub_CA_bin.c_str(),out_pub_CA_bin.size());
						}
						{
							string fname=prefix+".priv_CA.decoded";
							st_FILE f(fname,"wb");
							f.write(out_priv_CA_bin.c_str(),out_priv_CA_bin.size());
						}
//						SuccessDlg(lc);
						exit(0);
						return ;
			
			}
}
////////////////////////////
main()
{
	do_cert_auth();
}