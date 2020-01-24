#include <sys/types.h>
#include <ctime>
#include <time.h>
#include <ctype.h>
#include <string>
#include "st_rsa.h"
#include "st_stuff.h"
#include <iostream>
#include <sys/stat.h>
using namespace std;
string auth_pn;
void do_cert_sign();

string get_value (string s)
{
  char *pos = strchr (s.c_str (), '=');
  if (pos)
    {
      string ret = &pos[1];
	  cerr<< ret<<endl;
      return ret;
    }
  return "";
}

main(int argc, char *argv[])
{
	if(argc!=2) cerr<<"Usage: certsign authfile"<<endl,exit(1);
	auth_pn=argv[1];
	do_cert_sign();
}
int cert_sign_get_data(string&privCApathname,string&passwd,string&org, 
		string&ip,string&hostname,string&valid_from,string&valid_to,string&outfn)
{
	privCApathname=auth_pn;

			cout<<"Enter auth passwd:";
			getline(cin,passwd);
			cout<<passwd;
			cout<<"ORG:";
			getline(cin,org);
			cout<<"IP:";
			getline(cin,ip);
			cout<<"valid from:";
			getline(cin,valid_from);
			cout<<"valid to:";
			getline(cin,valid_to);
			cout<<"out file pref:";
			getline(cin,outfn);
return true;
	
}
void do_cert_sign()
{
	try {
		string privCApathname, passwd, org, ip, hostname, valid_from, valid_to, outfn;
		int bits;
	      start:
		if (cert_sign_get_data(privCApathname, passwd, org, ip, hostname, valid_from, valid_to, outfn)) {

			struct stat st;
			char *prrr = (char *)privCApathname.c_str();
/*					if(stat(to_mac_enc(privCApathname).c_str(),&st))
					{
						ErrorDlg(lc,privCApathname+" Does not exists");goto start;
					}	
*/
			string body;
			FILE *f = fopen(privCApathname.c_str(), "rb");
			if(f)
			{
			while (!feof(f)) {
				char s[100];
				int n = fread(s, 1, 100, f);
				body += string(s, n);
			}
				fclose(f);
			}
			else cerr<<"fopen ["<<privCApathname<<"] failed"<< endl,exit(1);
/*					st_macFile f;
					f.openFS(privCApathname);
					int size=f.size();
					st_malloc b(size+1000);
					f.read(b.buf,size);
					st_malloc b1(size*3);
					int dec_len=ap_base64decode_binary((unsigned char*)b1.buf,(char*)b.buf);
					*/
			string decMD5buf = Base64Decode(body);
//                                      unsigned char md5passwd[MD5_DIGEST_LENGTH];
//                                      MD5((unsigned char*)passwd.c_str(),passwd.size(),md5passwd);
			string md5pass = MD5(passwd);

			//unsigned char *p=(unsigned char*)b1.buf;
			string dec_pass_buff;
			for (unsigned int i = 0; i < decMD5buf.size(); i++) {
//                                              char c=
				dec_pass_buff += decMD5buf[i] ^ md5pass[i % MD5_DIGEST_LENGTH];
			}
			cout<<dec_pass_buff<<endl;
//                                      p[dec_len]=0;
			vector < string > strings = splitTOK("\n", (char *)dec_pass_buff.c_str());
			int bb = -1, ee = -1;
			for (unsigned int i = 0; i < strings.size(); i++) {
				if (strings[i] == "/BEGIN_CERTIFICATE_AUTHORITY")
					bb = i;
				if (strings[i] == "/END_CERTIFICATE_AUTHORITY")
					ee = i;
			}
			if (bb == -1 || ee == -1) {
				cerr << "FORMAT OR PASSWORD INVALID";
				exit(1);
				return;	// ERROR FORMAT OR PASSWD INVALID 
			}
			cerr<<"format valid"<<endl;
			string CA;
			string signer_name, signer_organization, key_len, key_id, private_key;
			string _signer_name = "/SIGNER_NAME", _signer_organization = "/SIGNER_ORGANIZATION", _key_len = "/KEY_LEN", _key_id = "/KEY_ID", _private_key = "/PRIVATE_KEY";
			for (int i = bb + 1; i < ee; i++) {
				CA += strings[i] + "\n";
				if (strings[i].substr(0, _signer_name.size()) == _signer_name)
					signer_name = get_value(strings[i]);
				else if (strings[i].substr(0, _signer_organization.size()) == _signer_organization)
					signer_organization = get_value(strings[i]);
				else if (strings[i].substr(0, _key_len.size()) == _key_len)
					key_len = get_value(strings[i]);
				else if (strings[i].substr(0, _key_id.size()) == _key_id)
					key_id = get_value(strings[i]);
				else if (strings[i].substr(0, _private_key.size()) == _private_key)
					private_key = get_value(strings[i]);

			}
			string md5_check_sum = "/MD5_CHECK_SUM";
			for (unsigned int i = 0; i < strings.size(); i++) {
				if (strings[i].substr(0, md5_check_sum.size()) == md5_check_sum) {
					string md5hex_recv = get_value(strings[i]);
					string md5hex_new = bin2hex(MD5(CA), 0);
					if (md5hex_recv != md5hex_new) {
						cerr << "MD5 failed - broken certificate authority";
						exit(1);
						return;

					}
				}
			}

			string CERT1;
			CERT1 += (string) "/CA_KEY_ID=" + key_id + "\n";
			CERT1 += (string) "/ORGANIZATION=" + org + "\n";
			CERT1 += (string) "/HOST_NAME=" + hostname + "\n";
			CERT1 += (string) "/VALID_FROM=" + valid_from + "\n";
			CERT1 += (string) "/VALID_TO=" + valid_to + "\n";
			unsigned char md5CERT[MD5_DIGEST_LENGTH * 10] = { 0 };
			MD5((unsigned char *)CERT1.c_str(), CERT1.size(), md5CERT);

			string priv_key = hex2bin(private_key);
			unsigned char *pp = (unsigned char *)priv_key.data();

			RSA *rsa = d2i_RSAPrivateKey(NULL, &pp, (long)priv_key.size());
			if (rsa == NULL) {

				cerr << "RSA failed";
				exit(1);
			}
			int rsa_len = RSA_size(rsa);
			int tot_len;
			for (int i = 0; i < MD5_DIGEST_LENGTH; i += rsa_len) {
				int ll = RSA_private_encrypt(rsa_len, &md5CERT[i], &md5CERT[i], rsa, RSA_NO_PADDING);
				tot_len = i + rsa_len;
			}
			string SIGN = bin2hex((char *)md5CERT, tot_len);
			string CONT;
			CONT += "/BEGIN_CERTIFICATE\n";
			CONT += CERT1;
			CONT += "/END_CERTIFICATE\n";
			CONT += "/SIGN=" + SIGN + "\n";



			{

				{
					st_FILE f(outfn.c_str(), "wb");
					f.write(CONT.c_str(), CONT.size());

				}

			}
		}
		cerr << "Certificate successfully created"<< endl;

		exit(0);
	}
	catch(string s) {

		cerr << "Error:" << s<< endl;

	}
	catch(...) {
		cerr<< "Unknown Error"<< endl;

	}
}
