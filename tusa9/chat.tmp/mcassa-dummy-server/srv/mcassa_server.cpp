#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/in.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include <openssl/rsa.h>
#include <sys/types.h> 
#include <sys/stat.h>  
#include <unistd.h>    
using namespace std;
#include "mcassa_server.h"

void handle_request(map<string,string>&out,map<string,string>&in)
{
    for(typeof(in.begin())i=in.begin();i!=in.end();i++)
    {
	printf("%s %s\n",i->first.c_str(),i->second.c_str());
    }
    out["kall"]="srall";
    out["kall1"]="srall1";
    out["kall11"]="srall11";
}
void handle_tcp_request(int sock)
{

    printf("handle_tcp_request(int sock) \n");
    char buf[10000];
    int ret=recv(sock,buf,sizeof(buf),0);
    string in(buf,ret);
    printf("in-> %s",in.c_str());
    // read header
    map<string,string> hparams;
    string content;
    bool first_processed=false;
    string method;
    string url;
    string proto;
    while(1)
    {
        string row;
        int pz=in.find("\r\n");
        if(pz==-1)break;
        row=in.substr(0,pz);
        printf("row -> '%s'\n",row.c_str());
        in=in.substr(pz+2,in.size()-pz-2);
        //	printf("in-> %s",in.c_str());
        if(row.size())
        {
            if(!first_processed)
            {
                first_processed=true;
                int p=row.find(" ");
                if(p!=-1)
                {
                    method=row.substr(0,p);
                    row=row.substr(p+1,row.size()-p-1);
                }
                p=row.find(" ");
                if(p!=-1)
                {
                    url=row.substr(0,p);
                    row=row.substr(p+1,row.size()-p-1);
                }
                proto=row;
                printf("method %s url %s proto %s\n",method.c_str(),url.c_str(),proto.c_str());
            }
            else
            {
                pz=row.find(":");
                if(pz!=-1)
                {
                    string key=row.substr(0,pz);
                    string val=row.substr(pz+2,row.size()-pz-2);
                    hparams[key]=val;
                    printf("pair ! %s -> %s\n",key.c_str(),val.c_str());
                }
            }
        }
        else
        {
            content=in;
            printf("\ncontent ==%s==\n",content.c_str());
        }
    }
    map<string,string> params;
    if(method=="POST" && atoi(hparams["Content-Length"].c_str())==content.size())
    {
        vector<string> v=splitTOK("&",content);
        for(unsigned i=0;i<v.size();i++)
        {
            vector<string>vv=splitTOK("=",v[i]);
            if(vv.size()==2)
            {
                params[vv[0]]=repl_percent(vv[1]);
            }
        }
    }
    if(params.count("b")&& params.count("l"))
    {
        string b=params["b"];
        int l=atoi(params["l"].c_str());
        st_rsa rsa;
        string  key;
        if(load_1_file(key,"./rsa_priv.bin")==-1)
        {
            printf("error load priv key\n"); exit(1);
        }
        rsa.priv_key_set(key);
        rsa.init_from_priv_key();
        enc_string es;
        es.buf=hex2bin(b);
        es.original_size=l;
        string body=rsa.private_decrypt(es);
        vector<string> vr=splitTOK("\r\n",body);
        map<string,string> pp;
        for(unsigned i=0;i<vr.size();i++)
        {
            int pz=vr[i].find("=",0);
            if(pz==-1){
                printf("--Error: in request mcassa\n");
                continue;
            }
            string key=vr[i].substr(0,pz);
            string val=vr[i].substr(pz+1,vr[i].size()-pz-1);
            pp[key]=val;
        }
	map<string,string> out;
	handle_request(out,pp);
    string sout;
    for(typeof(out.begin())i=out.begin();i!=out.end();i++)
    {
	sout+=i->first+"="+i->second+"\n";
    }
    enc_string ees=rsa.private_encrypt(sout);
    string html="ENCDATA;"+itostring(ees.original_size)+";"+bin2hex(ees.buf,10);
    string resp="Context-Type: text/html\r\n";
	resp="Context-Length: "+itostring(html.size())+"\r\n";
	resp+="\r\n";
	resp+=html;
	send(sock,resp.data(),resp.size(),0);
    

    }


}
void start()
{
    int sock;
    
        struct sockaddr_in sa;
        sa.sin_family = AF_INET;

        sa.sin_port = htons(PORT);

        sa.sin_addr.s_addr = INADDR_ANY;
        sock=socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if(sock==-1){
            printf("socket error\n");
            exit(1);
        }
        int i = 1;
        i=setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char *)&i,sizeof(i));
    
    

        while(bind (sock,(struct sockaddr *) &sa, sizeof (sa)) == -1){
            printf("binding to %d\n",PORT);
            sleep(1);
        }
        if(listen(sock,128)==-1){
            printf("listen failed\n");
	    exit(1);
        }
	printf("server started\n");

    while(1)
    {
        struct sockaddr_in saa;
	int len=sizeof(saa);
        int ns = accept(sock,(sockaddr *) &saa, (socklen_t *) &len);
        if(ns>0)
	{
	 handle_tcp_request(ns);
	 close(ns);
	}

    }

}
int main()
{
    start();
}
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


string repl_percent(const string & s)
{
    string a;
    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[i] == '%') {
            if (i + 2 > s.size()) {
                break;
            }
            int c1 = u_table[s[i + 1]];
            int c2 = u_table[s[i + 2]];
            i += 2;
            if (c1 > 70 || c2 > 70) {continue;}
            if (c1 < 48 || c2 < 48) {continue;}
            if (c1 >= 48 && c1 <= 57) {c1 -= 48;}
            if (c2 >= 48 && c2 <= 57) {c2 -= 48;}
            if (c1 >= 65 && c1 <= 70) {c1 -= 55;}
            if (c2 >= 65 && c2 <= 70) {c2 -= 55;}
            a += (char) c1 *16 + c2;
        } else {
            if (s[i] == '+') {a += " ";}
            else {a += s[i];}
        }
    }
    return a;
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
void st_rsa::init_from_priv_key()
{
	const unsigned char *p = (const unsigned char *)priv_key.data();
	rsa_xxx = d2i_RSAPrivateKey(NULL, &p, priv_key.size());
	if (!rsa_xxx) {
		throw string("i2d_RSAPrivateKey");
	}
}
int st_rsa::size()
{
	if(!rsa_xxx) throw string("!rsa_xxx");
	return RSA_size(rsa_xxx);
}
enc_string st_rsa::private_encrypt(const string & m)
{
	return encrypt(m, RSA_private_encrypt);
}
enc_string st_rsa::encrypt(const string & ms, int (*func) (int, const unsigned char *, unsigned char *, RSA *, int))
{
	int rsize = size();
	string mm = /*ms;*/Base64Encode(ms);
//	st_malloc vp(mm.size() + rsize);
	char *p = (char *) alloca(mm.size() + rsize);
//	DUMP("new");
	memcpy(p, mm.data(), mm.size());
	int i;
	if(!rsa_xxx) throw string("!rsa_xxx");
	for (i = 0; i < mm.size(); i += rsize) {
		func(rsize, (unsigned char *) &p[i], (unsigned char *) &p[i], rsa_xxx, RSA_NO_PADDING);
	}
	enc_string out;
	out.original_size = mm.size();
	out.buf = string((char *) p, i);
	return out;
}

st_rsa::st_rsa()
{
	rsa_xxx = NULL;
}
st_rsa::~st_rsa()
{
	if (rsa_xxx)
		RSA_free(rsa_xxx);
}
void st_rsa::priv_key_set(const string &s)
{
	priv_key=s;
}
string st_rsa::public_decrypt(const enc_string & m)
{
	return decrypt(m, RSA_public_decrypt);
}
string st_rsa::private_decrypt(const enc_string & m)
{
	return decrypt(m, RSA_private_decrypt);
}

string st_rsa::decrypt(const enc_string & m, int (*func) (int, const unsigned char *, unsigned char *, RSA *, int))
{
    //printf("string st_rsa::decrypt(const enc_string & m, int (*func) (int, const unsigned char *, unsigned char *, RSA *, int))\n");
    //st_malloc vp(m.buf.size() + 1000);
    {
        char *p = (char *) alloca(m.buf.size() + 1000);
        
            memcpy(p, m.buf.data(), m.buf.size());
            
                int rsize = size();
                //printf("before loop for\n");
                if(!rsa_xxx)
		{ 
		printf("!rsa_xxx=\n");
		exit(1);
		
		}
                {
                    for (int i = 0; i < m.buf.size(); i += rsize) {
                        func(rsize, (unsigned char *) &p[i], (unsigned char *) &p[i], rsa_xxx, RSA_NO_PADDING);
                    }
                    //printf("after loop for\n");
                    string out(p, m.original_size);
                    string out1 = Base64Decode(out);
                    return out1;
                }
		
    }
    return "";
}
static char    six2pr[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};

static unsigned char pr2six[256];


/*--- function HTUU_encode -----------------------------------------------
 *
 *   Encode a single line of binary data to a standard format that
 *   uses only printing ASCII characters (but takes up 33% more bytes).
 *
 *    Entry    bufin    points to a buffer of bytes.  If nbytes is not
 *                      a multiple of three, then the byte just beyond
 *                      the last byte in the buffer must be 0.
 *             nbytes   is the number of bytes in that buffer.
 *                      This cannot be more than 48.
 *             bufcoded points to an output buffer.  Be sure that this
 *                      can hold at least 1 + (4*nbytes)/3 characters.
 *
 *    Exit     bufcoded contains the coded line.  The first 4*nbytes/3 bytes
 *                      contain printing ASCII characters representing
 *                      those binary bytes. This may include one or
 *                      two '=' characters used as padding at the end.
 *                      The last byte is a zero byte.
 *             Returns the number of ASCII characters in "bufcoded".
 */
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


/*--- function HTUU_decode ------------------------------------------------
 *
 *  Decode an ASCII-encoded buffer back to its original binary form.
 *
 *    Entry    bufcoded    points to a uuencoded string.  It is
 *                         terminated by any character not in
 *                         the printable character table six2pr, but
 *                         leading whitespace is stripped.
 *             bufplain    points to the output buffer; must be big
 *                         enough to hold the decoded string (generally
 *                         shorter than the encoded string) plus
 *                         as many as two extra bytes used during
 *                         the decoding process.
 *             outbufsize  is the maximum number of bytes that
 *                         can fit in bufplain.
 *
 *    Exit     Returns the number of binary bytes decoded.
 *             bufplain    contains these bytes.
 */
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
std::string itostring(int i)
{
/*
	convert int to string
*/

	char ss[200];
	std::string s;
	::snprintf(ss, sizeof(ss) - 1, "%d", i);
	s = ss;
	return s;
}
string bin2hex(const string & in, int /* n */ )
{
	string out = "";
	const unsigned char *p = (unsigned char *)in.c_str();
	for (unsigned int i = 0; i < in.size(); i++) {
		char s[40];
		::snprintf(s, sizeof(s) - 1, "%02X", p[i]);
		out += s;
	}
	return out;
}
