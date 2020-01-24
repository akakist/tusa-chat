#ifndef ST_RSA__H
#define ST_RSA__H
#include <string>
#include <openssl/rsa.h>
//struct RSA;
#include <vector>
using namespace std;

#ifndef _WIN32
#define _sprintf sprintf
#define _snprintf snprintf
#endif

struct enc_string
{
	string buf;
    int original_size;
	enc_string(){}
};
class st_rsa
{
    RSA *rsa;
    int bits;
    string pub_key;
    string priv_key;
public:
	string pub_key_get();
	void pub_key_set(const string &);
	string priv_key_get();
	void priv_key_set(const string&);
    st_rsa();
    ~st_rsa();
    int size();
    void generate_key(int b);
    string public_key();
    string private_key();
    void init_from_pub_key();
	void init_from_priv_key();
    enc_string encrypt(const string &m, int (*func)(int, const unsigned char*, unsigned char*, RSA*,int));
    enc_string private_encrypt(const string &m);
    enc_string public_encrypt(const string &m);
    string decrypt(const enc_string &m, int (*func)(int, const unsigned char*, unsigned char*, RSA*,int));
    string private_decrypt(const enc_string &m);
    string public_decrypt(const enc_string &m);
};
struct st_malloc
{
private:
		st_malloc(const st_malloc&);             // Not defined
		st_malloc& operator=(const st_malloc&);  // Not defined
public:
    void *buf;
    st_malloc(unsigned long size);
    ~st_malloc();
};


#endif



