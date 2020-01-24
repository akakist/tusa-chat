#include "stdafx.h"
#include "ifree_client.h"
#include "version.h"

#include "ifree_data_event.h"
#include "ifree_requests.h"
#include "errs.h"
#include "mutex_inspector.h"
#include <netdb.h>
#include "str_lib.h"
#include "web_tools.h"
#include "PTR.h"
#include "c_conn.h"
#include <signal.h>
#include "st_stuff.h"
#include "tcp_sender.h"
#include <sys/socket.h>   
#include <netinet/in.h>   
#include <arpa/inet.h>    

//extern "C" void logErr2(char *fmt,...);
m_var<string> www_bind_ip;
#ifdef WIN32
void sleep(unsigned long);
#endif
m_var<bool> ex(false);
string thread_info_txt();


unsigned int ifree_id;
bool logged=false;
std::string __gets(const PTR_getter <c_socket> &__S, const string &delim);
int S_recv(const PTR_getter<c_socket>&__S,void *buf, size_t len, int flags);
void init_senders(const string& pn,const string& prefix,map<string,string>&m);

unsigned long __gethostname(const char *hostname)
{MUTEX_INSPECTOR;

    // try and resolve hostname
    struct hostent *hostEnt;
    if ((hostEnt = gethostbyname(hostname)) == NULL || hostEnt->h_addrtype != AF_INET) {
        throw string("DNS lookup failed");
    } else {
        return *((unsigned long *)(hostEnt->h_addr));
    }
}
bool sock_readable(int &fd)
{MUTEX_INSPECTOR;
    int iii;


    fd_set rdfs;	/*for select */
    FD_ZERO(&rdfs);
    FD_SET(fd, &rdfs);
    struct timeval tv;
    tv.tv_sec = 10;
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
string sock_recv(int &sock)
{MUTEX_INSPECTOR;
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
{MUTEX_INSPECTOR;
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

PTR_getter<c_socket> sock_connect(const char *host, unsigned short port)
{MUTEX_INSPECTOR;

    int sock = ::socket(AF_INET, SOCK_STREAM, 0);
    if (sock <= 0)
        throw string("Couldn't create socket");

    struct sockaddr_in localAddr;
    localAddr.sin_family = AF_INET;
    localAddr.sin_port = 0;
    localAddr.sin_addr.s_addr = inet_addr(www_bind_ip.get().c_str());
    if(bind(sock,(sockaddr*)&localAddr,sizeof(localAddr)))
    {
	logErr2("failed to bind");
    }
    

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
        //        exit(1);
    }
    PTR_getter<c_socket> __S=new c_socket(sock);
    return __S;
}
static void www_server_request(const string& host, unsigned short port, const string &out_data, string & head,map<string,vector<string> > & headers,map<string,vector<string> > & upperheaders,string& content, string & full_content)
{MUTEX_INSPECTOR;
    //printf("%s\n",out_data.c_str());
    PTR_getter<c_socket> __S=sock_connect(host.c_str(),port);
    {
    PGLR(c_socket,s,__S);
    sock_send(s->get_socket_fd(),out_data);
    }
    head=__gets(__S,"\r\n");
    full_content+=head+"\r\n";
    while(1)
    {//MUTEX_INSPECTOR;
	string s=__gets(__S,"\r\n");
	full_content+=s+"\r\n";
	if(s=="") break;

                int pop = s.find(":", 0);
                if (pop == -1) {
                    return;
                }
                headers[s.substr(0, pop)].push_back(s.substr(pop + 1, s.length() - pop - 1));
                upperheaders[strupper(s.substr(0, pop))].push_back(s.substr(pop + 1, s.length() - pop - 1));
	
    }
    if(upperheaders.count("CONTENT-LENGTH"))
    {//MUTEX_INSPECTOR;
	if(upperheaders["CONTENT-LENGTH"].size())
	{
	    int cl=atoi(upperheaders["CONTENT-LENGTH"][0]);
	    char buf[cl+100];
//	    PGLR(c_socket,s,__S);
//	    int sock=s->get_socket_fd();
//	    content=sock_recv(sock);
	    int readden=0;
	    while(readden!=cl)
	    {
	    int res=S_recv(__S,buf, cl, 0);
/*	    if(res!=cl)
	    {
		logErr2("-Error: if(res!=cl)");
	    }*/
	    content+=string(buf,res);
	    readden+=res;
	    }
	    full_content+=content;
	}
    }
//    string ret=sock_recv(fd);
//    return ret;

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

void ifree_client::on_redirector_connected()
{
    logErr2("UNDEF %s %d",__FILE__,__LINE__);
}
void ifree_client::on_bos_connected()
{
    logErr2("UNDEF %s %d",__FILE__,__LINE__);
}
void ifree_client::on_login_ok(const map<string,string> &m)
{MUTEX_INSPECTOR;
    logged=true;
    logErr2("login_ok");

    /*	if(m.count("SV"))
    	{
    		if(m.find("SV")->second!=SERVER_VERSION_INT)
    		{
    			logErr2("Version is older then required. Please download version %s",m.find("SV")->second.c_str());
    			sleep(1000);
    			exit(1);
    		}
    	}*/
    string out;
    //#ifdef DEBUG
    out+=("LOGIN OK, params:\n");
    for(map<string,string>::const_iterator/*typeof(m.begin())*/ i=m.begin();i!=m.end();i++)
    {
        char ss[200];
        sprintf(ss,"%s=%s\n",i->first.c_str(),i->second.c_str());
        out+=ss;
    }
    //#endif
    /*	if(m.count("ifree_id"))
    		ifree_id=atoi(m.find("ifree_id")->second.c_str());
    	out+=m.find("ifree_id")->second+"\n";*/
#ifdef WIN32		
    MessageBox(NULL,out.c_str(),"Logged",MB_OK);
#else
    logErr2("Logged");
#endif		

}
void ifree_client::on_login_failed(const map<string,string> &m)
{
    string e="Login failed ";
    if(m.count("error"))
    {
        e+=m.find("error")->second;
    }
#ifdef WIN32
    MessageBox(NULL,e.c_str(),"Login failed",MB_OK);
#else
    logErr2("Login failed");
#endif	
    //logErr2("login_failed: error '%s'",e.c_str());
    //    logErr2("UNDEF ifree_client::on_login_failed %s %d",__FILE__,__LINE__);
}
void ifree_client::on_disconnect(const string& reason)
{MUTEX_INSPECTOR;
    logged=false;
    logErr2("ifree_client::on_disconnect '%s'",reason.c_str());
    //    exit(1);
    map<string,string> mm;
    mm["login"]="ser_bel";
    mm["pass"]="zzz";
    mm["client_type"]="3";
    mm["SV"]=SERVER_VERSION_INT;
    do_auth(mm);
    //    logErr2("do_auth(mm);");
}
void ifree_client::on_socket_create(int sock)
{
//MUTEX_INSPECTOR;
    //    logErr2("ifree_client::on_socket_create %s %d",__FILE__,__LINE__);
}
ifree_client::ifree_client(): bos_client_interface(true)
{
//MUTEX_INSPECTOR;
    //    logErr2("UNDEF %s %d",__FILE__,__LINE__);
}
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

void split_params(map<string,string>& params,const string & s)
{
MUTEX_INSPECTOR;

    vector <string> pr = splitTOK("&", s);
    for (unsigned int i = 0; i < pr.size(); i++) {
        string p = pr[i];
        int pp = p.find("=", 0);
        if (pp == -1) {
            continue;
        }
        string val = repl_percent(p.substr(pp + 1, p.length() - pp - 1));
        string key = p.substr(0, pp);
        params[key] = val;

        /*if (process_v_params)
            v_params[key].push_back(val);*/
    }
}
string _hex(char c)
{MUTEX_INSPECTOR;
    char ss[200];
    snprintf(ss,sizeof(ss),"%%%02x",c);
    return ss;
}
//! * ' ( ) ; : @ & = + $ , / ? % # [ ] 

string urlencode(const string &s)
{MUTEX_INSPECTOR;
    string r;
    int n=s.size();
    for(int i=0;i<n;i++)
    {
	switch(s[i])
	{
	    case '!':
	    case '*':
	    case '\'':
	    case '(':
	    case ')':
	    case ';':
	    case ':':
	    case '@':
	    case '&':
	    case '=':
	    case '+':
	    case '$':
	    case ',':
	    case '/':
	    case '?':
	    case '\%':
	    case '#':
	    case '[':
	    case ']':
	    case '{':
	    case '}':
	    r+=_hex(s[i]);
	    break;
	    case ' ': r+="+";break;
	    default: r+=s[i];
	}
    }
    //    string o;
    //    for(unsigned in)
    return r;
}
string filt_comma(const string &s)
{
    string r;
    for(unsigned i=0;i<s.size();i++)
    {
	if(s[i]!=',')
		r+=string(&s[i],1);
    }
    return r;
}
void ifree_client::on_data_event(int cmd,oscar_buffer & in_b)
{MUTEX_INSPECTOR;
    //	logErr2("UNDEF %s %d",__FILE__,__LINE__);
    switch(cmd)
    {
    case 101:
	{
	MUTEX_INSPECTOR;
//            logErr2("recvd 101");
		int rid;
		string l_url;
		
		string orig_url;
		in_b>>rid>>l_url>>orig_url;
		//logErr2("orig_url %s",orig_url.c_str());
		//logErr2("l_url %s",l_url.c_str());

		string url=orig_url;
		string host;
		if(url.find("/ipicz/1")!=-1) host="frame.mmi.ru";
		if(url.find("/ipicz/2")!=-1) host="media.4446.ru";
		//logErr2("host %s",host.c_str());
		if(host.size())
		{
		    string path;
		    if(l_url=="1") path=str_replace("/ipicz/1","",url);
		    else if(l_url=="2") path=str_replace("/ipicz/2","",url);
		    
	    string head;
	    map<string,vector<string> >  headers,upperheaders;
	    string res_content;
	    string full_content;
	    string out=(string)"GET "+"http://"+host+"/"+path+" HTTP/1.0\r\n\r\n";
	    //logErr2("out %s",out.c_str());
	    www_server_request(host, 80, out, head,headers,upperheaders,res_content,full_content);
	    //logErr2("%s",full_content.c_str());
		    
            out_oscar_buffer b;
	    if(upperheaders["CONTENT-TYPE"].size())
                b<<rid<<orig_url<<head<<upperheaders["CONTENT-TYPE"][0]<<res_content;
            send_packet(true,101,b.as_string());
	    		
		}

//		=str_replace("http://frame.mmi.ru","/ipicz/1",res_content);
//		res_content=str_replace("http://media.4446.ru","/ipicz/2",res_content);
		
	}break;
    case 100:
//	logErr2("recvd 100");
        {
	//MUTEX_INSPECTOR;
            int rid;
            string original_url;
//            string params;
	    map<string,string> in_cookies/*,out_cookies*/;
	    string post_content;
	    string l_url;
	    
            in_b>>rid>>l_url>>original_url>>in_cookies>>post_content;
//	    logErr2("post_content %s",post_content.c_str());
//            //logErr2("%d %s %s",rid,url.c_str(),params.c_str());
            //frame.mmi.ru

            map<string,string> m;

            m["ProjectGUID"] = "{46CEF7A0-B355-4B1F-9F38-0034CB1764C6}";
            m["skinID"] = "1002";
            m["color"] = "blue";
            m["enc"] = "windows-1251";
            m["baseUrl"] = l_url;
	    

            m["ID"] = "default";
            m["contentColumnCount"] = "3";
            m["contentRowCount"] = "2";
            m["previewSize"] = "100x100";
            m["moduleType"] = "Catalogue";
            m["contentType"] = l_url;


            vector<string> vp;
            for(map<string,string>::iterator i=m.begin();i!=m.end();i++)
            {
                vp.push_back(i->first+"="+urlencode(i->second) );
            }
	    string url_params=original_url;

            int qp = original_url.find("?", 0);
            if (qp!= -1) {
                url_params=url_params.substr(qp + 1, url_params.length() - qp - 1);
//                split_params(original_params);
//                url = url.substr(0, qp);
            }
	    //logErr2("url_params: %s",url_params.c_str());
	    
            string content=post_content;
            if(content.size() && vp.size())
	    {
	        content+="&";
            //if(vp.size()) 
	    }
		content+=join("&",vp);
//	    content=filt_comma(content);
//	    url_params=filt_comma(url_params);
            string out="POST /phplight.aspx?"+url_params+" HTTP/1.0\r\n";
            out+="Host: frame.mmi.ru\r\n";
            out+="Content-Type: application/x-www-form-urlencoded\r\n";
            out+="User-Agent: i-Free PHP Lite module/1.0.1\r\n";
            out+="Content-Length: "+itostring(content.size())+"\r\n";
            out+="Accept-language: en-us\r\n";
	    if(in_cookies.size())
	    {
		vector<string> vc;
		for(map<string,string>::iterator i=in_cookies.begin();i!=in_cookies.end();i++)
		{
		    vc.push_back(i->first+"="+i->second);
		}
		out+="Cookie: "+join("; ",vc)+"\r\n";
	    }
            out+="\r\n";
            out+=content;

            //logErr2("%s",out.c_str());

            //string res=tcp_server_request("frame.mmi.ru", 80, out);
	    string head;
	    map<string,vector<string> >  headers,upperheaders;
	    string res_content;
	    string full_content;
	    
	    www_server_request("frame.mmi.ru", 80, out, head,headers,upperheaders,res_content,full_content);
//             logErr2("result: %s",res_content.c_str());
	    if(upperheaders["CONTENT-TYPE"].size())
	    {
	    if(upperheaders["CONTENT-TYPE"][0].find("text/html")!=-1)
	    {
		res_content=str_replace("http://frame.mmi.ru","/ipicz/1",res_content);
		res_content=str_replace("http://media.4446.ru","/ipicz/2",res_content);
		
	    }
	    }
            out_oscar_buffer b;
            b<<rid<<original_url<<head<<headers<<res_content;
            send_packet(true,100,b.as_string());

        }
        break;
    default:
        logErr2("clan_parser MSG undefined 0x%X (%s %d),",cmd,__FILE__,__LINE__);
    }

}
#ifndef WIN32
#include "str_lib.h"
void onterm(int signum)
{
    int n=rand();
    if(!ex)	logErr2("Received signal %d",signum);
    try{
        if(!ex){
            ex=true;
            string out;
            {
/*#ifdef MUTEX_INSPECTOR_DBUG
                logErr2("%s",dump_mutex_inspectors().c_str());
#endif			*/
            }

            if(signum==SIGUSR1)
            {
                ex=true;
                logErr2("BACKUP mode switched on");
                sleep(1);
                ex=false;
                return;
            }
            if(signum==SIGUSR2)
            {
                ex=true;
                logErr2("Print statistics");
                string di;

//                di+=thread_info_txt();
#ifdef MUTEX_INSPECTOR_DBUG
                di+=dump_mutex_inspectors();
#endif			
                string fn="stat."+itostring(time(NULL));
                {
                    st_FILE f(fn,"wb");
                    f.write(di);
                }
                logErr2("BACKUP mode switched off");
                sleep(1);
                ex=false;
                return;
            }
            if(signum==SIGHUP){
                ex=true;
//                load_central_server_config();
                sleep(1);
                ex=false;
                return;
            }
            if(signum!=10){
                ex=true;
                logErr("Terminating on SIGNAL %d",signum);
            }

#ifdef MUTEX_INSPECTOR_DBUG
            out+=dump_mutex_inspectors();
//            logErr2("%s",out.c_str());
#endif			
            string fn;
            if(signum!=10){
                fn=(string)"TERM."+itostring(time(NULL));
            }else{
                fn=(string)"USERTERM."+itostring(time(NULL));
            }
            if(out.size())
            {
                out="Terminating on SIGNAL "+itostring(signum)+"\n"+out;

                FILE *f=fopen(fn.c_str(),"wb");
                if(f){
                    fprintf(f,"%s",out.c_str());
                    fclose(f);
                }

            }
            if(signum!=10){
		{
		//MUTEX_LOCK kall(destroy_MX);
//		if(pserver)
		{

//		typeof(pserver) p=pserver;
//		pserver=NULL;
//		delete p;

		}
		destroy_senders();
		}
		sleep(3);
                exit(signum);
            }
        }
    }catch(cError e){
    }catch(...){
        logErr("--Error: unknow error in on_term() %s %d",__FILE__,__LINE__);
    }
}



int app_main(int, char**)
{ MUTEX_INSPECTOR;


#ifndef WIN32
        signal(SIGPIPE,SIG_IGN);
        signal(SIGABRT,onterm);
        signal(SIGTERM,onterm);
        signal(SIGINT,onterm);
        signal(SIGSEGV,onterm);
        signal(SIGFPE,onterm);
        signal(SIGQUIT,onterm);
        signal(SIGILL,onterm);
        signal(SIGBUS,onterm);
        signal(SIGHUP,onterm);
        signal(SIGUSR1,onterm);
        signal(SIGUSR2,onterm);

        signal(10,onterm);
#endif		

    string g_conf_pn="./conf";
    map<string,string> g_conf=load_m_file(g_conf_pn);
    init_senders(g_conf_pn,"sender_",g_conf);
    
    set_cfg_str(g_conf,	"www_bind_ip", g_conf_pn,www_bind_ip,"0.0.0.0");
    

    //    bos_client_config.load_config("./conf");
    ifree_client * cli=new     ifree_client;

    cli->start(g_conf_pn,"client_",g_conf);

    map<string,string> mm;
    mm["login"]="ser_bel";
    mm["pass"]="zzz";
    mm["client_type"]="3";
    mm["SV"]=SERVER_VERSION_INT;
    cli->do_auth(mm);
    int n=0;
    while(1)
    {MUTEX_INSPECTOR;
        n++;
        sleep(1);
        if(logged /*&& rand()%10==0*/)
        {MUTEX_INSPECTOR;
            //    for(unsigned ii=0;ii<10;ii++)
            //{
            /*				out_oscar_buffer b;
            				b<<26;
            				string in;
            				logErr2("before cli->send_request");*/
            //if(cli->send_request(r_TUSA_GET_INFO,in,b.as_string(), 10))
            {
                /*	oscar_buffer bb(in.data(),in.size());
                	int uid;
                	string summa;                                     
                	string login;                                     
                	string result;       
                	bb>>uid>>summa>>login>>result;
                	logErr2("RESUO %d %s %s  %s",uid,summa.c_str(),login.c_str(),result.c_str());
                	*/
                //		tusa_get_info_by_uid(uid, summa, login, result);
                //		bb<<uid<<summa<<login<<result;

            }
            //				else logErr2("cli->send_request failed");
            //}
            //	    bool send_request(int cmd_code,string &in,const string & out, time_t timeout);
        }
    }
    return 0;
}

#endif

