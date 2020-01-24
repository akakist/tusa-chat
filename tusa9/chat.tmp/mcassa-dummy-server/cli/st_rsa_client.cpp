//#ifdef WIN32

//#endif
#include <string>
#include <map>
#include "st_rsa_client.h"
#include <vector>
#include <openssl/rsa.h>
#include <stdio.h>
#include <string>
#ifndef WIN32
#include <netdb.h>
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>   
#include <sys/types.h>  
#include <sys/stat.h>   
#include <unistd.h>     
#endif
#ifdef WIN32
#include <winsock.h>
#endif
#ifdef WIN32
#pragma warning( disable:4309)
#pragma warning( disable:4267)
#endif

using namespace std;



static char    six2pr[64] = {
                                'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
                            };

static unsigned char pr2six[256];

static int
Ns_HtuuEncode(unsigned char *bufin, unsigned int nbytes, char * bufcoded)
{

    /* ENC is the basic 1 character encoding function to make a char printing */
#define ENC(c) six2pr[c]

    register char  *outptr = bufcoded;
    unsigned int    i;

    for (i = 0; i < nbytes; i += 3) {
        /* c1 */
        *(outptr++) = ENC(*bufin >> 2);
        /* c2 */
        *(outptr++) = ENC(((*bufin << 4) & 060) | ((bufin[1] >> 4) & 017));
        /* c3 */
        *(outptr++) = ENC(((bufin[1] << 2) & 074) | ((bufin[2] >> 6) & 03));
        /* c4 */
        *(outptr++) = ENC(bufin[2] & 077);

        bufin += 3;
    }

    /*
     * If nbytes was not a multiple of 3, then we have encoded too many
     * characters.  Adjust appropriately.
     */
    if (i == nbytes + 1) {
        /* There were only 2 bytes in that last group */
        outptr[-1] = '=';
    } else if (i == nbytes + 2) {
        /* There was only 1 byte in that last group */
        outptr[-1] = '=';
        outptr[-2] = '=';
    }
    *outptr = '\0';
    return (outptr - bufcoded);
}


static int
Ns_HtuuDecode(char * bufcoded, unsigned char * bufplain, int outbufsize)
{

    /* single character decode */
#define DEC(c) pr2six[(int)c]
#define MAXVAL 63

    static int      first = 1;

    int             nbytesdecoded, j;
    register char  *bufin = bufcoded;
    register unsigned char *bufout = bufplain;
    register int    nprbytes;

    /*
     * If this is the first call, initialize the mapping table. This code
     * should work even on non-ASCII machines.
     */
    if (first) {
        first = 0;
        for (j = 0; j < 256; j++)
            pr2six[j] = MAXVAL + 1;

        for (j = 0; j < 64; j++)
            pr2six[(int) six2pr[j]] = (unsigned char) j;
    }

    /* Strip leading whitespace. */

    while (*bufcoded == ' ' || *bufcoded == '\t')
        bufcoded++;

    /*
     * Figure out how many characters are in the input buffer. If this would
     * decode into more bytes than would fit into the output buffer, adjust
     * the number of input bytes downwards.
     */
    bufin = bufcoded;
while (pr2six[(int) *(bufin++)] <= MAXVAL){};
    nprbytes = bufin - bufcoded - 1;
    nbytesdecoded = ((nprbytes + 3) / 4) * 3;
    if (nbytesdecoded > outbufsize) {
        nprbytes = (outbufsize * 4) / 3;
    }
    bufin = bufcoded;

    while (nprbytes > 0) {
        *(bufout++) = (unsigned char) (DEC(*bufin) << 2 | DEC(bufin[1]) >> 4);
        *(bufout++) = (unsigned char) (DEC(bufin[1]) << 4 |
                                       DEC(bufin[2]) >> 2);
        *(bufout++) = (unsigned char) (DEC(bufin[2]) << 6 | DEC(bufin[3]));
        bufin += 4;
        nprbytes -= 4;
    }

    if (nprbytes & 03) {
        if (pr2six[(int) bufin[-2]] > MAXVAL) {
            nbytesdecoded -= 2;
        } else {
            nbytesdecoded -= 1;
        }
    }
    return (nbytesdecoded);
}


string Base64Encode(const string &str)
{
    int len=str.size()*2;
    char *out=(char*)malloc(len+10);
    ::memset(out,0,len+2);
    int outlen=Ns_HtuuEncode((unsigned char*)str.data(),str.size(),out);
    string ret(out,outlen);
    free(out);
    return ret;
}
string Base64Decode(const string &str)
{
    unsigned long len=str.size();
    char *out=(char*)malloc(len+10);
    ::memset(out,0,len+2);
    int outlen=Ns_HtuuDecode((char*)str.data(),(unsigned char*)out,len);

    string ret(out,outlen);
    free(out);
    return ret;
}

void st_rsa_cpp(){}
void st_rsa::init_from_pub_key()
{
    const unsigned char *p = (const unsigned char *)pub_key.data();
    rsa = d2i_RSAPublicKey(NULL, &p, pub_key.size());
    if (!rsa) {
        throw string("i2d_RSAPublicKey");
    }
}
void st_rsa::init_from_priv_key()
{
    const unsigned char *p = (const unsigned char *)priv_key.data();
    rsa = d2i_RSAPrivateKey(NULL, &p, priv_key.size());
    if (!rsa) {
        throw string("i2d_RSAPrivateKey");
    }
}
string st_rsa::private_key()
{
    string s;
    st_malloc ppp(10000);
    char *b = (char *) ppp.buf;
    unsigned char *p = (unsigned char *) b;
    int len = 0;
    if (rsa && p) {
        len = i2d_RSAPrivateKey(rsa, &p);
        if (len < 0)
            return "";
        string s((char *) b, len);
        return s;
    } else {
        throw string("i2d_RSAPrivateKey");
    }
    return s;
}

string st_rsa::public_key()
{
    string s;

    st_malloc b(10000);
    unsigned char *p = (unsigned char *) b.buf;

    int len = 0;
    if (rsa && p) {
        len = i2d_RSAPublicKey(rsa, &p);
        if (len < 0)
            return "";
        string s((char *) b.buf, len);
        return s;
    } else {
        throw string("i2d_RSAPublicKey");
    }
    return s;
}
void st_rsa::generate_key(const int b)
{
    bits = b;
    rsa = RSA_generate_key(bits, RSA_F4, NULL, NULL);
    if (!rsa)
        throw string("RSA_generate_key");
    pub_key = public_key();

    priv_key = private_key();
}


string st_rsa::private_decrypt(const enc_string & m)
{
    return decrypt(m, RSA_private_decrypt);
}

string st_rsa::public_decrypt(const enc_string & m)
{
    return decrypt(m, RSA_public_decrypt);
}

enc_string st_rsa::public_encrypt(const string & m)
{
    return encrypt(m, RSA_public_encrypt);
}

enc_string st_rsa::private_encrypt(const string & m)
{
    return encrypt(m, RSA_private_encrypt);
}

enc_string st_rsa::encrypt(const string & ms, int (*func) (int, const unsigned char *, unsigned char *, RSA *, int))
{
    int rsize = size();
    string mm = /*ms;*/Base64Encode(ms);
//    printf("string before base 64 %s\n",ms.c_str());
//    printf("string after base 64 %s\n",mm.c_str());
    st_malloc vp(mm.size() + rsize);
    char *p = (char *) vp.buf;
    memcpy(p, mm.data(), mm.size());
    int i;
    for (i = 0; i < mm.size(); i += rsize) {
        func(rsize, (unsigned char *) &p[i], (unsigned char *) &p[i], rsa, RSA_NO_PADDING);
    }
    enc_string out;
    out.original_size = mm.size();
    out.buf = string((char *) p, i);
    return out;
}

string st_rsa::decrypt(const enc_string & m, int (*func) (int, const unsigned char *, unsigned char *, RSA *, int))
{
    st_malloc vp(m.buf.size() + 10);
    char *p = (char *) vp.buf;

    memcpy(p, m.buf.data(), m.buf.size());
    int rsize = size();
    for (int i = 0; i < m.buf.size(); i += rsize) {
        func(rsize, (unsigned char *) &p[i], (unsigned char *) &p[i], rsa, RSA_NO_PADDING);
    }
    string out(p, m.original_size);
    string out1 = Base64Decode(out);
    return out1;
}
st_rsa::st_rsa()
{
    rsa = NULL;
}
st_rsa::~st_rsa()
{
    if (rsa)
        RSA_free(rsa);
}
int st_rsa::size()
{
    return RSA_size(rsa);
}
string st_rsa::pub_key_get()
{
    return pub_key;
}
void st_rsa::pub_key_set(const string &s)
{
    pub_key=s;
}
string st_rsa::priv_key_get()
{
    return priv_key;
}
void st_rsa::priv_key_set(const string &s)
{
    priv_key=s;
}
st_malloc::st_malloc(unsigned long size)
{
    buf = malloc(size + 1);
    if(buf==NULL)throw string("st_malloc failed");
}

st_malloc::~st_malloc()
{
    free(buf);
}
string hex2bin(const string &s)
{
    string out="";
    char *p=(char*)s.data();
    int sz=s.size();
    for(int i=0;i<sz;i+=2)
    {
        char ss[3]={0};
        ::memcpy(ss,&p[i],2);
        unsigned char c=(unsigned char)strtol(ss,NULL,16);
        out+=string((char*)&c,1);
    }
    return out;
}
string bin2hex(const string & in, int /* n */ )
{
    string out = "";
    const unsigned char *p = (unsigned char *)in.c_str();
    for (unsigned int i = 0; i < in.size(); i++) {
        char s[40];
        _snprintf(s, sizeof(s) - 1, "%02X", p[i]);
        out += s;
    }
    return out;
}
std::vector < std::string > splitTOK(const char *seps, const std::string & src)
{
    /*
    	split buffer into vector of splices
    	used strtok rules
    */

    std::vector < std::string > res;
    std::map < char, int >mm;
    unsigned int l;
    l =::strlen(seps);
    for (unsigned int i = 0; i < l; i++) {
        mm[seps[i]] = 100;
    }
    std::string tmp;
    l = src.size();
    {for (unsigned int i = 0; i < l; i++) {

            if (mm[src[i]] != 100)
                tmp += src[i];
            else {
                if (tmp.size()) {
                    res.push_back(tmp);
                    tmp = "";
                }
            }
        }}
    if (tmp.size()) {
        res.push_back(tmp);
        tmp = "";
    }
    return res;
}
char l_table[] = {
                     /*
                     	lowercase table
                     */
                     0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd,
                     0xe, 0xf, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
                     0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
                     0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31,
                     0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d,
                     0x3e, 0x3f, 0x40, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
                     0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75,
                     0x76, 0x77, 0x78, 0x79, 0x7a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 0x60, 0x61,
                     0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d,
                     0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
                     0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x90, 0x83, 0x82, 0x83, 0x84, 0x85,
                     0x86, 0x87, 0x88, 0x89, 0x9a, 0x8b, 0x9c, 0x9d, 0x9e, 0x9f, 0x90, 0x91,
                     0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d,
                     0x9e, 0x9f, 0xa0, 0xa2, 0xa2, 0xbc, 0xa4, 0xb4, 0xa6, 0xa7, 0xb8, 0xa9,
                     0xba, 0xab, 0xac, 0xad, 0xae, 0xbf, 0xb0, 0xb1, 0xb3, 0xb3, 0xb4, 0xb5,
                     0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbe, 0xbe, 0xbf, 0xe0, 0xe1,
                     0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed,
                     0xee, 0xef, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9,
                     0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff, 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5,
                     0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 0xf0, 0xf1,
                     0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd,
                     0xfe, 0xff };

char u_table[] = {
                     /*
                     	uppercase table
                     */
                     0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd,
                     0xe, 0xf, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
                     0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
                     0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31,
                     0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d,
                     0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
                     0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55,
                     0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 0x60, 0x41,
                     0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d,
                     0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
                     0x5a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x82, 0x81, 0x84, 0x85,
                     0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x80, 0x91,
                     0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x8a, 0x9b, 0x8c, 0x8d,
                     0x8e, 0x8f, 0xa0, 0xa1, 0xa1, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9,
                     0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb2, 0xa5, 0xb5,
                     0xb6, 0xb7, 0xa8, 0xb9, 0xaa, 0xbb, 0xa3, 0xbd, 0xbd, 0xaf, 0xc0, 0xc1,
                     0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd,
                     0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9,
                     0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5,
                     0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1,
                     0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd,
                     0xde, 0xdf };

string strupper(const string &s)
{
    /*
    	convert string to uppercase
    */
    std::string a;
    for(unsigned int i=0;i<s.length();i++){
        unsigned char z=s[i];
        a+=u_table[z];
    }
    return a;
}

std::string strlower(const std::string & s)
{
    /*
    	convert string to lowercase
    */
    std::string a;
    for (unsigned int i = 0; i < s.length(); i++) {
        unsigned char z = s[i];
        a += l_table[z];
    }
    return a;
}
static std::string itostring(int i)
{
    /*
    	convert int to string
    */

    char ss[200];
    std::string s;
    ::_snprintf(ss, sizeof(ss) - 1, "%d", i);
    s = ss;
    return s;
}
unsigned long __gethostname(const char *hostname)
{

    // try and resolve hostname
    struct hostent *hostEnt;
    if ((hostEnt = gethostbyname(hostname)) == NULL || hostEnt->h_addrtype != AF_INET) {
        throw string("DNS lookup failed");
    } else {
        return *((unsigned long *)(hostEnt->h_addr));
    }
}
bool sock_readable(int &fd)
{
    int iii;


    fd_set rdfs;	/*for select */
    FD_ZERO(&rdfs);
    FD_SET(fd, &rdfs);
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    iii = select(fd + 1, &rdfs, NULL, NULL, &tv);
    if(iii!=-1)
        return FD_ISSET(fd, &rdfs);

    if (iii == -1) {
#ifdef WIN32
        closesocket(fd);
#else
		close(fd);
#endif
        fd=-1;
        return false;
    }
    return false;
}
int sock_connect(const char *host, unsigned short port)
{

    int sock = ::socket(AF_INET, SOCK_STREAM, 0);
    if (sock <= 0)
        throw string("Couldn't create socket");

    struct sockaddr_in remoteAddr;
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(port);
    remoteAddr.sin_addr.s_addr = __gethostname(host);
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = 0;
    int ret=connect(sock,(const struct sockaddr *)&remoteAddr, sizeof(struct sockaddr));
    if(ret<0)
    {
        printf("connect error");
        exit(1);
    }
    return sock;
}
string sock_recv(int &sock)
{
    string out;
    char buffer[4100];
    int recv0;
    int cnt=0;
    while(1)
    {

        cnt++;
        if(cnt>100) break;

        if (sock_readable(sock)) {
            int ret = recv(sock,buffer, 4096, 0);
            if(ret==0){
                recv0++;
                if(recv0>10)
                {

#ifdef WIN32
					closesocket(sock);
#else 
					close(sock);
#endif
                    sock=-1;

                }
            }
            else{

                recv0=0;
            }
            if (ret == -1) {
#ifdef WIN32
				closesocket(sock);
#else 
				close(sock);
#endif
                sock=-1;

            }
            if(ret>0)
                out+=string(buffer, ret);
        }
        if(sock==-1) return out;
#ifdef WIN32
		Sleep(20);
#else
		usleep(20000);
#endif


    }

    return out;
}

void sock_send(int sock, const string& s)
{
    //    int sent=0;
    string ss=s;
    int s0=0;
    while(1)
    {
        int ret=send(sock,ss.data(),ss.size(),0);
        if(ret<0) throw string("send failed");
        if(ret==0) s0++;
        if(s0>=10) throw string("s0==10");
        if(ret==ss.size())break;
        if(ret>0)
        {
            s0=0;
            ss = ss.substr(ret, ss.size() - ret);
        }
#ifdef WIN32
		Sleep(10);
#else
		usleep(10000);
#endif
    }
}
static string tcp_server_request(const string& host, unsigned short port, const string &out_data)
{
    //printf("%s\n",out_data.c_str());
    int fd=sock_connect(host.c_str(),port);
    sock_send(fd,out_data);
    string ret=sock_recv(fd);
    return ret;

}
static string build_http_request(const string &url,const string &body)
{
    string out="POST "+url+" HTTP/1.1\r\n"
               "Content-Type: text/html\r\n";
    out+="Content-Length: "+itostring(body.size())+"\r\n";
    out+="\r\n";
    out+=body;
    return out;
}
#ifdef WIN32
__declspec (dllexport) 
#endif
map<string,string> http_rsa_server_request(const string& host, unsigned short port,const string &url,const string & rsa_key,const map<string,string>& reqm)
{
    string req;
    for(map<string,string>::const_iterator i=reqm.begin();i!=reqm.end();i++)
    {
        req+=i->first+"="+i->second+"\n";
    }
//	printf("req:\n%s\n",req.c_str());

    st_rsa rsa;
    rsa.pub_key_set(rsa_key);
    rsa.init_from_pub_key();
    enc_string es=rsa.public_encrypt(req);
    string body;
    body+="b="+bin2hex(es.buf,10);
    body+="&l="+itostring(es.original_size);
    string http_req=build_http_request(url,body);
//	printf("<< %s\n",http_req.c_str());
    string response=tcp_server_request(host,port,http_req);

    string beg="ENCDATA;";
    int pos=response.find(beg);
    if(pos!=-1)
    {
        string buf=response.substr(pos+beg.size(),response.size()-(pos+beg.size()));
        vector<string> v=splitTOK(";",buf);
        if(v.size()==2)
        {
            enc_string es;
            es.original_size=atoi(v[0].c_str());
            es.buf=hex2bin(v[1]);
            string dec_buf=rsa.public_decrypt(es);

            vector<string> vr=splitTOK("\r\n",dec_buf);
            map<string,string>m;

            for(unsigned i=0;i<vr.size();i++)
            {
                int pz=vr[i].find("=",0);
                if(pz==-1){
                    printf("--Error: in request mcassa\n");
                    continue;
                }
                string key=vr[i].substr(0,pz);
                string val=vr[i].substr(pz+1,vr[i].size()-pz-1);
                m[key]=val;
            }
            return m;
        }
    }
    map<string,string> dummy;
    return dummy;
}
int load_1_file(string & res, const string & fn) // -1 error
{
   struct stat st;
   if (stat(fn.c_str(), &st)) {
      return -1;
   }
   FILE *f=fopen(fn.c_str(),"rb");
   if(f)
   {
   char *buf=(char*)alloca(st.st_size);
   fread(buf, st.st_size,1,f);
   string al((char *)buf, st.st_size);
   res = al;
   fclose(f);
   }
   return st.st_size;

}
