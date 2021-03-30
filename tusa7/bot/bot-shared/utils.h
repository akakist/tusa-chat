#ifndef UTILS__H
#define UTILS__H
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

string strupper(const string &s);
string strlower(const string &s);


string str_nick(const string &n);


extern unsigned char l_table[];
extern unsigned char u_table[];
extern unsigned char nicks_char[256];

bool strex(const string &str,const string &patt);

vector <string>  splitTOK(const char *seps, const string& src);
string itostring(int i);
string ftostring(double i);
string luitostring(long unsigned int i);
int atoi(const string&);

string join(const string &pattern, const vector<string> & arr);
string join(const char* pattern, const vector<string> & arr);

class user_nick
{
public:
    string name;
    unsigned int id;
//	user_nick();

//	user_nick(const string &n);
//	user_nick(const string &n,unsigned int i);
};

struct user_status
{
    string name;
    int pic;
    int id;
    bool disable_invite;
    bool uniq;
};

class user_state
{

public:

    enum
    {
        UNDEF=0xffff0000
    };
    unsigned int channel;
    user_status status;
    user_nick nick;
//		bool contact_mode; // true if userlist contains contacts only
//		user_state():nick("undef",UNDEF){channel=UNDEF;status.id=UNDEF;nick.id=UNDEF;/*contact_mode=false;*/}
};


#endif

