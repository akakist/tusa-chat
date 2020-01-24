
#include "stdafx.h"
#ifdef _DEBUG
#define New DEBUG_NEW
#endif

#include "_mutex.h"
#include <list>
#include "mutex_inspector.h"
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <map>
#include "mysql_extens.h"
#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "web_server.h"
#include "message.h"
#include "chat_def.h"
#include "copy_file.h"
#include "file_set.h"

#include "app_con.h"
#include "app_def.h"
#include "tcp_stats.h"
#include "chat_config.h"
#include "user_credits.h"
#include <algorithm>

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#ifndef WIN32
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include "tcp_oscar_dialog_server.h"
#ifndef _NO_PROXY
#endif
#include "oscar_buffer.h"

#include "chat_globals.h"
#include "tusa_rsa_priv.cpp"
#include "st_rsa.h"
#include "web_tools.h"
#include "update_cmd.h"
#ifdef KALL
void send_system_note(const DB_id& uid,const string &subj,const string& msg);
void cassa_handler(map<string,string>&out,map<string,string>&in)
{

    if(in["cassa-login"]!="sib-ras-comp"){
        logErr2("--Error: invalid mcassa login '%s'",in["cassa-login"].c_str());
        out["result"]="invalid_cassa_login";
        return;
    }
    if(in["cassa-password"]!="sibpwd0011"){
        logErr2("--Error: invalid mcassa password '%s'",in["cassa-password"].c_str());
        out["result"]="invalid_cassa_password";
        return;
    }
    st_dbh d;
    string todo=in["todo"];
    if(todo=="getinfo")
    {
        DB_id uid;CONTAINER(uid)=0;CONTAINER(uid)=atoi(in["uid"]);
        string login;
        Double summa;summa.container=0;
        {
            vector<string> v=d.dbh->select_1_rowQ((QUERY)"select login from tbl_users where id=?"<<CONTAINER(uid));
            if(v.size()==0)
            {
                out["result"]="invalid_uid";
                return;
            }
            out["login"]=v[0];
        }
        {
            PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(uid)));
			summa=u->summa;
			out["summa"]=get_f22(summa.container);
			out["nick"]=u->last_nick;
		}
        
        //send_system_note

        out["todo"]="getinfo_response";
        out["result"]="success";
        logErr2("Requested getinfo uid=%d from multicassa",CONTAINER(uid));
        return;
    }
    if(todo=="put_money")
    {
        DB_id uid;CONTAINER(uid)=0;CONTAINER(uid)=atoi(in["uid"]);
	map<string,string> mm=chat_config.get_pay_params();
	if(!mm.count("mcassa"))
	{
	logErr2("!!!!!!! ERRROR         chat_config.get_pay_params undef mcassa");
	}
        Double add_summa;add_summa.container=atof(in["add_summa"].c_str())/atof(mm["mcassa"].c_str());
        {
            vector<string> v=d.dbh->select_1_rowQ((QUERY)"select login from tbl_users where id=?"<<CONTAINER(uid));
            if(v.size()==0)
            {
                //out["result"]="invalid_uid";
//                return;
        	out["login"]="invalid";
            }
	    else
        	out["login"]=v[0];
        }
        Double summa_before;
        Double summa_after;
        {
            PGLW(user_profile,u,user$profiles.FindByID(CONTAINER(uid)));
			summa_before=u->summa;
			//u->summa.dbset(u->summa.get()+add_summa);
			summa_after.container=u->credit_summa.container+add_summa.container;

			Double summa;summa.container=u->credit_summa.container+add_summa.container;
			out["tot_summa"]=get_f22(summa.container);
			out["add_summa"]=get_f22(add_summa.container);
		}

	
		inc_credit_summa(uid,add_summa,"mcassa");

        map<string,string>qq;
        qq["~summa_before~"]=get_f22(summa_before.container);
        qq["~summa_after~"]=get_f22(summa_after.container);
        qq["~add_summa~"]=get_f22(add_summa.container);
	try{
        send_system_note(uid,RVfiles(qq,"admin/credgen/note_subj_mcassa"),RVfiles(qq,"admin/credgen/note_body_mcassa"));
	}
	catch(...)
	{
	}

        out["todo"]="put_money_response";
        out["result"]="success";
        logErr2("Requested add_summa uid=%d add_summa=%f from multicassa",CONTAINER(uid),add_summa.container);
    }
}

void url_mcassa( app_connection* cc)
{
    st_rsa rsa;
    string  key=string(tusa_rsa_priv_key,tusa_rsa_priv_key_size);
    rsa.priv_key_set(key);
    rsa.init_from_priv_key();
    enc_string es;
    es.buf=hex2bin(cc->params["b"]);
    es.original_size=atoi(cc->params["l"]);

    string body=rsa.private_decrypt(es);
    vector<string> vr=splitTOK("\r\n",body);
    map<string,string> pp;
    for(unsigned i=0;i<vr.size();i++)
    {
        int pz=vr[i].find("=",0);
        if(pz==-1){
            logErr2("--Error: in request mcassa");
            continue;
        }
        string key=vr[i].substr(0,pz);
        string val=vr[i].substr(pz+1,vr[i].size()-pz-1);
        pp[key]=val;
    }
    if(!pp.size())return;
    map<string,string>out;
    cassa_handler(out,pp);
    string sout;
	for(map<string,string>::const_iterator i=out.begin();i!=out.end();i++)
    {
        sout+=i->first+"="+i->second+"\n";
    }
    enc_string ees=rsa.private_encrypt(sout);
    cc->html_out="ENCDATA;"+itostring(ees.original_size)+";"+bin2hex(ees.buf,10);

}
#endif