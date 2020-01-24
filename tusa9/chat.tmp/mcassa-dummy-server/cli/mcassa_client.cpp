
#ifdef WIN32
#include <time.h>
#include <winsock.h>
#endif
#ifndef WIN32
#include <netdb.h>
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>   
#endif
#include <cerrno>
#include <string>
#include <map>
//#include "tusa_rsa_pub.cpp"
//#include "st_rsa_client.h"
using namespace std;
#define IN
#define OUT

#ifndef _WIN32
#define _sprintf sprintf
#define _snprintf snprintf
#endif

#ifdef WIN32
__declspec (dllexport) 
#endif
map<string,string> http_rsa_server_request(const string& host, unsigned short port,const string &url,const string & rsa_key,const map<string,string>& reqm);
int load_1_file(string & res, const string & fn); // -1 error

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




void get_info_by_uid(IN unsigned int uid, OUT double &summa, OUT string& login)
{
    map<string,string> req;
    req["todo"]="getinfo";
    req["cassa-login"]="sib-ras-comp";
    req["cassa-password"]="sibpwd0011";
    req["uid"]=itostring(uid);
    string tusakey;
    if(load_1_file(tusakey, "rsa_pub.bin")==-1)
    {
	printf("Error loading key\n");
    }
    map<string,string> response=http_rsa_server_request("localhost",4354,"/495/mcassa",tusakey,req);
    summa=atof(response["summa"].c_str());
    login=response["login"];
    for(typeof(response.begin())i=response.begin();i!=response.end();i++)
    {
	printf("%s -> %s\n", i->first.c_str(),i->second.c_str());
    }


}
void make_payment(IN unsigned int uid, IN double payment, OUT double &new_summa, OUT string& login)
{
    map<string,string> req;
    req["todo"]="put_money";
    req["cassa-login"]="sib-ras-comp";
    req["cassa-password"]="sibpwd0011";
    req["uid"]=itostring(uid);
    char ss[200];
    _snprintf(ss,sizeof(ss),"%f",payment);
    req["add_summa"]=ss;

    string tusakey;
    if(load_1_file(tusakey, "rsa_pub.bin")==-1)
    {
	printf("Error loading key\n");
    }
    map<string,string> response=http_rsa_server_request("localhost",4354,"/495/mcassa",tusakey,req);

    new_summa=atof(response["tot_summa"].c_str());
    login=response["login"];

    for(typeof(response.begin())i=response.begin();i!=response.end();i++)
    {
	printf("%s -> %s\n", i->first.c_str(),i->second.c_str());
    }

}
int main(int argc, char *argv[])
{
#ifdef WIN32                                         
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        printf("WSAStartup failed\n");
        return 0;
    }
#endif                                               
    try{
        string login;
        double summa;
        get_info_by_uid(26, summa, login);
        printf("info %d %f %s\n",26,summa,login.c_str());
        make_payment(26, 10, summa, login);
        printf("make paiment 26, %f %s\n",summa,login.c_str());
    }catch(string e)
    {
        printf("%s\n",e.c_str());
    }
#ifdef WIN32
    Sleep(10000);
#endif
    return 0;
}
