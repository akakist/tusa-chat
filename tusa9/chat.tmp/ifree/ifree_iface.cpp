#include "stdafx.h"
#ifdef _DEBUG
#define New DEBUG_NEW
#endif

#include <signal.h>
#include <errno.h>
#include "file_set.h"
#include "PTR.h"
#include "mutex_inspector.h"
#include "chat_def.h"
#include "web_server_data.h"
#include "mysql_extens.h"
#include "user.h"
#include "utils.h"
#include "PTR.h"
#include "version.h"
#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> 
#endif
#ifndef _NO_PROXY
#endif
#include "G_session.h"
#include "session_data.h"
#include "cs_bos_user.h"
#include "session_data__.h"
#include "app_cs_server_iface.h"
#include "ifree_clients.h"
#include "central_server.h"
#include "RTYPES_CORE.h"

#include "web_connection.h"
#include "server_config.h"
#include "copy_file.h"
#include <sys/types.h> 
#include <sys/stat.h>  
#ifndef WIN32
#include <unistd.h>    
#endif
#include "app_con.h"
__ifree_clients ifree_clients;

_mutex i__socks_mx;
struct sock_data
{
    sock_data(const PTR_getter<c_socket> & s):__S(s),t(time(NULL))
    {

    }
    PTR_getter<c_socket> __S;
    time_t t;
};
map<int, sock_data >  i__socks;
void deinit_ifree()
{
}
void init_ifree()
{

}
void on_delete_session_ifree(const G_session& app_data,const PTR_getter<session_data>&SD)
{MUTEX_INSPECTOR;

    PTR_getter<ifree_client> __C=ifree_clients.find(app_data);
    ifree_clients.erase(app_data);
    set<DB_id> lu;
    if(__C)
    {
    logErr2("ifree client logged out");
    }
    else
    {
        logErr2("Error: on_delete_session_ifree clan not found");
    }



}

void process_data_event_ifree(const G_session& app_data, const PTR_getter<session_data> &__SD, oscar_buffer& b,int _msg)
{
    PTR_getter<ifree_client> __CSU=ifree_clients.find(app_data);
    if(!__CSU)
    {
        logErr2("if(!__CSU) ");
        return;
    }
    int msg=( int)_msg;
    switch(msg)
    {
    case 101:
        {
            int rid;
            string head,orig_url;
            string ct;
            string content;
            b>>rid>>orig_url>>head>>ct>>content;
            string out;
            out+=head+"\r\n";
            out+="Content-Type:"+ct+"\r\n";
            out+="Content-Length: "+itostring(content.size())+"\r\n";
            out+="\r\n";
            out+=content;
            PTR_getter<c_socket> __S(NULL);
            string cv;
            {
                M_LOCK(i__socks_mx);
                map<int, sock_data >::const_iterator i=i__socks.find(rid);

                if(i!=i__socks.end())
                {
                    __S=i->second.__S;
                    i__socks.erase(i->first);
                }
            }
            
            reply_socket(__S,out);
            string pathname=global_config.var_dir.get()+"/ipics"+orig_url;
            check_path_wfn(pathname);
            FILE *f=fopen(pathname.c_str(),"wb");
            if(f)
            {
                fwrite(out.data(),1,out.size(),f);
                fclose(f);
            }

        }
        break;
    case 100:
        {
            int rid;
            string original_url,res;
            string head,res_content;
            map<string,vector<string> > headers;

            b>>rid>>original_url>>head>>headers>>res_content;
            string __in;
            __in+=head+"\r\n";
            bool is_m_con=original_url.find("m_con")!=-1;
            string O,P,V;
            for(map<string,vector<string> >::const_iterator i=headers.begin();i!=headers.end();i++)
            {
                for(unsigned j=0;j<i->second.size();j++)
                {
		    if(i->first=="X-Cache") continue;
		    if(i->first=="Date") continue;
		    if(i->first=="PLCache") continue;
		    if(i->first=="X-AspNet-Version") continue;
		    if(i->first=="X-Powered-By") continue;
		    
                    if(is_m_con)
                    {
			if(strupper(i->first)=="SET-COOKIE")
			{

                            vector<string> v=splitTOK("; ",i->second[j]);
			    
                            for(unsigned l=0;l<v.size();l++)
                            {
				
                                vector<string> v2=splitTOK("=",v[l]);
                                if(v2.size()==2)
                                {
				    
                                    if(v2[0]=="__ModuleContent_operatorId" || v2[0]=="__ModuleContent_phoneId" || v2[0]=="__ModuleContent_vendorId")
                                    {
                                        if(v2[0]=="__ModuleContent_operatorId")
                                        {
                                            O=v2[1];
                                        }
                                        if(v2[0]=="__ModuleContent_phoneId")
                                        {
                                            P=v2[1];
                                        }
                                        if(v2[0]=="__ModuleContent_vendorId")
                                        {
                                            V=v2[1];
                                        }

                                        
                                        __in+=i->first+": "+i->second[j]+"\r\n";

                                    }

                                }

                            }
			
			}
			else
			{
                                    __in+=i->first+": "+i->second[j]+"\r\n";
			}
                    }
                    else
                    {
                        if(strupper(i->first)!="SET-COOKIE")
                        {
                            __in+=i->first+": "+i->second[j]+"\r\n";
                            
                        }
                    }

                }
            }
            
            __in+="\r\n";
            __in+=res_content;

            


            PTR_getter<c_socket> __S(NULL);
            string cv;
            {
                M_LOCK(i__socks_mx);
                map<int, sock_data>::const_iterator i=i__socks.find(rid);
                if(i!=i__socks.end())
                {
                    __S=i->second.__S;
                    i__socks.erase(i->first);
                }
            }
            reply_socket(__S,__in);
            string pathname=global_config.var_dir.get()+"/icontent/"+bin2hex(MD5(original_url));

            if(is_m_con)
            {
                pathname+="O"+O+"P"+P+"V"+V;
            }
            check_path_wfn(pathname);
            FILE *f=fopen(pathname.c_str(),"wb");
            if(f)
            {
                fwrite(__in.data(),1,__in.size(),f);
                fclose(f);
            }
        };
        break;
    default: logErr2("undefined MSG 0x%x",msg);
    }

}
bool process_request_ifree(const G_session& app_data, const PTR_getter<session_data> &__SD, oscar_buffer& b,int msg,  int req_id, out_oscar_buffer& bb)
{
    PTR_getter<ifree_client> __CSU=ifree_clients.find(app_data);
    if(!__CSU)
    {
        logErr2("if(!__CSU) ");
        return false;
    }
    switch(msg)
    {

    case 100:
        {
            map<string,string> m;
            b>>m;

        }



    default:
        logErr2("--Error: invalid reqtype %d",msg);
        break;
    }
    return true;
}

bool do_application_login_ifree(const G_session &g_sess, const PTR_getter<session_data> &__SD,const string& ip,map<string,string> &m)
{MUTEX_INSPECTOR;
    st_dbh d;

    ifree_client *ccl=new ifree_client;LEAKCTL_ADD(ccl);
    ccl->session_id=g_sess;
    ccl->session=__SD;
    ccl->ip=ip;
    ccl->login_time=time(NULL);
    PTR_getter<ifree_client> pccl(ccl);
    ifree_clients.insert(g_sess,pccl);
    map<string,string> mm=m;
    mm.erase("pass");
    mm.erase("client_type");
    mm["SV"]=SERVER_VERSION_INT;
    {
        central_server::reply_login_ok(__SD,mm);
	logErr2("ifree client logged in");
    }
    if(0)// Invalid login
    {
        central_server::reply_login_failed(__SD,mm);

        return false;

    }
    return true;
}
string do_adminfo_ifree()
{MUTEX_INSPECTOR;

    string out;
    
    return out;
}
void on_iterate_ifree(map<string,string>& m)
{MUTEX_INSPECTOR;
}
void load_config_ifree(const string &s)
{MUTEX_INSPECTOR;
    
}


app_interface iface_ifree[]=
    {
        {3,
         on_delete_session_ifree,
         do_application_login_ifree,
         do_adminfo_ifree,
         on_iterate_ifree,
         load_config_ifree,
         init_ifree,
         deinit_ifree,
         process_data_event_ifree,
         process_request_ifree
        },
        {-1}
    };
void add_handler(app_interface* iface);

void add_handler_ifree()
{MUTEX_INSPECTOR;
    add_handler(iface_ifree);
}
ifree_client::ifree_client(): base_container("ifree_client"),session(NULL)
{

}
int req_id=0;

void clean_i__socks()
{
    M_LOCK(i__socks_mx);
    time_t t=time(NULL);
    vector<int> to_del;
    for(map<int, sock_data >::const_iterator i=i__socks.begin();i!=i__socks.end();i++)
    {
        if(t-i->second.t>60) to_del.push_back(i->first);
    }
    for(unsigned i=0;i<to_del.size();i++)
        i__socks.erase(to_del[i]);

}



void url_itusa(app_connection *cc)
{MUTEX_INSPECTOR;
#ifndef WIN32

	if (cc->vurl.size())
    {
        
        {
            out_oscar_buffer b;
            int rid=++req_id;
            if(cc->METHOD!="POST")
            {
                string params=cc->original_params;
                string pathname=global_config.var_dir.get()+"/icontent/"+bin2hex(MD5(cc->original_url));

                if(cc->original_url.find("m_con")!=-1)
                {
                    pathname+="O"+cc->in_cookies["__ModuleContent_operatorId"];
                    pathname+="P"+cc->in_cookies["__ModuleContent_phoneId"];
                    pathname+="V"+cc->in_cookies["__ModuleContent_vendorId"];
                }
                struct stat st;
                if(!stat(pathname.c_str(),&st))
                {
                    char ss[st.st_size];
                    FILE *f=fopen(pathname.c_str(),"rb");
                    if(f)
                    {
                        fread(ss,1,st.st_size,f);
                        fclose(f);
                    }
                    string repl=string(ss,st.st_size);
                    reply_socket(cc->socket,repl);
                    cc->allow_build_response=false;
                    clean_i__socks();
                    return;

                }
            }


            
            cc->in_cookies.erase("ASP.NET_SessionId");
            b<<rid;
            b<<*cc->vurl.begin();
            b<<cc->original_url;
            b<<cc->in_cookies;
            b<<cc->POST_CONTENT;
            vector<G_session> v=ifree_clients.keys();
            if(v.size())
            {
                PTR_getter<ifree_client> __C=ifree_clients.find(v[rand()%v.size()]);
                if(__C)
                {
                    reply_ifree_client(__C, 100, b);
                    {
                        M_LOCK(i__socks_mx);
                        i__socks.insert(make_pair(rid,sock_data(cc->socket)));
                    }
                    cc->allow_build_response=false;
                    clean_i__socks();
                    return;
                }
                else
                {
                }
            }
            cc->html_out="service not available now";
        }
    }
    clean_i__socks();
#endif
}
