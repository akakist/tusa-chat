#ifndef MCASSA_SERVER__H
#define MCASSA_SERVER__H
#define PORT 4354
string repl_percent(const string & s);
std::vector < std::string > splitTOK(const char *seps, const std::string & src);
int load_1_file(string & res, const string & fn); // -1 error
string Base64Encode(const string &str);
string Base64Decode(const string &str);
std::string itostring(int i);
string bin2hex(const string & in, int /* n */ );
string hex2bin(const string &s);

struct enc_string
{
	string buf;
    int original_size;
	enc_string(){}
};
class st_rsa
{
//	_mutex Mutex;
    RSA *rsa_xxx;
    int bits;
    string pub_key;
    string priv_key;
public:
    string public_key();
    string private_key();
	string pub_key_get();
	void pub_key_set(const string &);
	string priv_key_get();
	void priv_key_set(const string&);
    st_rsa();
    ~st_rsa();
    int size();
    void generate_key(int b);
    void init_from_pub_key();
	void init_from_priv_key();
    enc_string encrypt(const string &m, int (*func)(int, const unsigned char*, unsigned char*, RSA*,int));
    enc_string private_encrypt(const string &m);
    enc_string public_encrypt(const string &m);
    string decrypt(const enc_string &m, int (*func)(int, const unsigned char*, unsigned char*, RSA*,int));
    string private_decrypt(const enc_string &m);
    string public_decrypt(const enc_string &m);
};

#endif
