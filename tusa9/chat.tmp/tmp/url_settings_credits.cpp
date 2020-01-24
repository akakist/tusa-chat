#include "stdafx.h"
#ifdef _DEBUG
#define New DEBUG_NEW
#endif

#include "_mutex.h"
#include <list>
#include "mutex_inspector.h"
#include <time.h>
#include <map>
#include "mysql_extens.h"
#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "web_server.h"
#include "message.h"
#include "chat_def.h"

#include <sys/stat.h>
#include <sys/types.h>
#include "copy_file.h"
#include "wrappers.h"
#include "web_tools.h"
#include "file_set.h"

#include "user_credits.h"
#include "levels.h"
#include "server_config.h"

#include "app_def.h"
#include "update_cmd.h"

#include "app_con.h"
#include "chat_globals.h"
#ifdef __WITH_LICENSE
#include "license.h"
#endif
//#include "DR_types.h"

void send_system_note(const DB_id& uid,const string &subj,const string& msg);

_mutex pincode_MX("pincode_MX");

string settings_proceed_pincode(const int v1,const int v2,const int v3, const DB_id &uid,const string& login, const string& cnick)
{
    MUTEX_INSPECTOR;
    string e;
    st_dbh d;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)"select v1,v2,v3,summa,accepted from pincodes where v1='?' and v2='?' and v3='?'"<<v1<<v2<<v3);
    if (v.size()==5)
    {
        if (v[4]=="1") // accepted
        {
            e=_MSG("pincode_already_used");
            logErr2("entered used pincode (%d-%d-%d) from user %s (%s)",v1,v2,v3,cnick.c_str(),login.c_str());
        }
        else
        {
            Double summa;summa.container=atoi(v[3]);
            string fmt=_MSG("accepted_credits");
            char s[200];
            {
                snprintf(s,sizeof(s),fmt.c_str(),summa.container);
            }
            e=s;


            inc_credit_summa(uid,summa,"pincode");



            d.dbh->real_queryQ((QUERY)"update pincodes set accepted='1', date_accepted=NOW(), accepted_by_uid=? where v1='?' and v2='?' and v3='?'"<<CONTAINER(uid)<<v1<<v2<<v3);
            {
                logErr2("accepted pincode=%d-%d-%d summa=%f from user %s (%s)",v1,v2,v3,summa.container,cnick.c_str(),login.c_str());
            }

        }
    }
    else
    {
        e=_MSG("invalid_pincode");
        logErr2("invalid pincode (%d-%d-%d) from user %s (%s)",v1,v2,v3,cnick.c_str(),login.c_str());

    }
    return e;
}

string settings_transaction_dolg_otdat(const DB_id& uid,unsigned int id)
{
    st_dbh d;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)"select from_user,to_user, summa from credits_loans where id=? and pogashen='0'"<<id);
    if (v.size()!=3) return "Not exist by ID";
    DB_id from_user,to_user;
    Double summa;

    CONTAINER(from_user)=atoi(v[0]);
    CONTAINER(to_user)=atoi(v[1]);
    summa.container=atof(v[2].c_str());
    if (to_user!=uid) throw cError("if(to_user!=uid)"+_DMI());
    Double msumma;msumma.container=0;
    bool ok=false;
    {
        PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(uid)));
		msumma=u->credit_summa;
    }
    if (msumma>summa)ok=true;

    string e;

    if (!ok)
        e=_MSG("notenoughcredits");

    if (ok){
        ok=buy_thing(uid,from_user,summa,"zaem_return");
    }
    if (!ok)
        e=_MSG("buy_thing error");

    e=_MSG("credits_otdans");
    if (ok)
    {
        d.dbh->real_queryQ((QUERY)"update credits_loans set pogashen='1'  where id=?"<<id);
    }

    return e;


}
string settings_transaction_dolg_zabrat(const DB_id& uid,unsigned int id)
{
    st_dbh d;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)"select from_user,to_user, summa from credits_loans where id=? and pogashen='0' and committed='1'"<<id);
    if (v.size()!=3) return "Not exist by ID";
    DB_id from_user,to_user;
    Double summa;

    CONTAINER(from_user)=atoi(v[0]);
    CONTAINER(to_user)=atoi(v[1]);
    summa.container=atof(v[2].c_str());
    if (from_user!=uid) throw cError("if(from_user!=uid)"+_DMI());
    Double msumma;msumma.container=0;
    bool ok=false;
    {
        PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(to_user)));
		msumma=u->credit_summa;
    }
    if (msumma>summa)ok=true;

    string e;

    if (!ok)
        e=_MSG("notenoughcredits");

    if (ok){
        ok=buy_thing(to_user,uid,summa,"zaem_zabor");
    }
    if (!ok)
        e=_MSG("buy_thing error");

    e=_MSG("credit_zabrans");
    d.dbh->real_queryQ((QUERY)"update credits_loans set pogashen='1'  where id=?"<<id);
    return e;


}


string settings_transaction_perevod_start(const DB_id uid,const Double& summa, const string& nick)
{
    MUTEX_INSPECTOR;
    st_dbh d;
    string e;
    Double remained_sum;remained_sum.container=0;
    {
        PGLR(user_profile, c,user$profiles.FindByID(CONTAINER(uid)));
        if (c){
            remained_sum=c->credit_summa;
        }
    }
    if (summa.container>remained_sum.container){
        e=_MSG("notenoughcredits");
    }else{
        if (summa.container<=0){
            e=_MSG("nulltransaction");
        }else{
            int id=atoi(d.dbh->select_1Q((QUERY)"select uid from nicks where str_nick like '?'"<<MESL(str_nick(nick))));
            if (id<=0){
                e=_MSG("nicknotfound");
            }else{
                d.dbh->real_queryQ((QUERY)"insert into credits_transactions (summa,from_user,to_user,to_nick,create_time) values(?,?,?,'?',NOW())"<<summa.container<<CONTAINER(uid)<<id<<nick);
                e=_MSG("transactiondone");
            }
        }
    }
    return e;
}
string settings_transaction_zaem_start(const DB_id uid,const Double &summa, const string& nick)
{
    MUTEX_INSPECTOR;
    st_dbh d;
    string e;
    Double remained_sum;remained_sum.container=0;
    {
        PGLR(user_profile, c,user$profiles.FindByID(CONTAINER(uid)));
        if (c){
            remained_sum=c->credit_summa;
        }
    }
    if (summa.container>remained_sum.container){
        e=_MSG("notenoughcredits");
    }else{
        if (summa.container<=0){
            e=_MSG("nulltransaction");
        }else{
            int id=atoi(d.dbh->select_1Q((QUERY)"select uid from nicks where str_nick like '?'"<<MESL(str_nick(nick))));
            if (id<=0){
                e=_MSG("nicknotfound");
            }else{
                d.dbh->real_queryQ((QUERY)"insert into credits_loans (summa,from_user,to_user,to_nick,create_time) values(?,?,?,'?',NOW())"<<summa.container<<CONTAINER(uid)<<id<<nick);
                e=_MSG("transactiondone");
            }
        }
    }
    return e;
}


string settings_transaction_perevod_commit(const DB_id uid, int trid, const string& cnick)
{
    MUTEX_INSPECTOR;
    string e;
    st_dbh d;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)"select summa,to_user,committed from credits_transactions where from_user=? and id='?'"<<CONTAINER(uid)<<trid);
    if (v.size()==3){
        if (v[2]=="0"){
            bool allok=false;
            Double summa;summa.container=atof(v[0].c_str());
            Double rsum;rsum.container=0;
            {
                PGLR(user_profile, c,user$profiles.FindByID(CONTAINER(uid)));
				if(c)
				{
					rsum.container=c->credit_summa.container-summa.container;
					if (c->credit_summa.container>summa.container){
						allok=true;
					}
				}
            }
            DB_id to_user;
            CONTAINER(to_user)=atoi(v[1]);
            if (allok)
            {
                if (buy_thing(uid,to_user,summa,"manual_transfer"))
                {
                    d.dbh->real_queryQ((QUERY)"update credits_transactions set committed=1,commit_time=NOW() where id='?'"<<trid);
                    allok=true;
                }
                else allok=false;
            }

            if (allok){
                e=_MSG("committed");

            }


            if (allok)
            {
                map<string,string> mm;
                mm["~from~"]=cnick;
                mm["~summa~"]=get_f22(summa.container);
                string msg=RVfiles(mm,"settings/credit_transfer_msg");
                send_system_note(to_user,_MSG("credit_transfer"),msg);
                vector<PTR_getter<chat_user> >__Z=local_users.get$(to_user);
                for (unsigned i=0;i<__Z.size();i++)
                    if (__Z[i])
                    {
                        send_syspriv_msg(__Z[i],msg);
                    }
            }
        }
    }
    return e;
}
string settings_transaction_zaem_commit(const DB_id uid, int trid, const string& cnick)
{
    MUTEX_INSPECTOR;
    string e;
    st_dbh d;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)"select summa,to_user,committed from credits_loans where from_user=? and id='?'"<<CONTAINER(uid)<<trid);
    if (v.size()==3){
        if (v[2]=="0"){
            bool allok=false;
            Double summa;summa.container=atof(v[0].c_str());
            Double rsum;rsum.container=0;
            {
                PGLR(user_profile, c,user$profiles.FindByID(CONTAINER(uid)));
				if(c)
				{
					rsum.container=c->credit_summa.container-summa.container;
					if (c->credit_summa.container>summa.container){
						allok=true;
					}
				}
            }
            DB_id to_user;
            CONTAINER(to_user)=atoi(v[1]);
            if (allok)
            {
                if (buy_thing(uid,to_user,summa,"zaem_transfer"))
                {
                    d.dbh->real_queryQ((QUERY)"update credits_loans set committed=1,commit_time=NOW() where id='?'"<<trid);
                }
                else
                {
                    return "error";
                }
            }

            if (allok){
                e=_MSG("committed");

            }


            if (allok)
            {
                map<string,string> mm;
                mm["~from~"]=cnick;
                mm["~summa~"]=get_f22(summa.container);
                string msg=RVfiles(mm,"settings/credit_zaem_msg");
                send_system_note(to_user,_MSG("credit_zaem"),msg);
                vector<PTR_getter<chat_user> >__Z=local_users.get$(to_user);
                for (unsigned i=0;i<__Z.size();i++)
                    if (__Z[i])
                    {
                        send_syspriv_msg(__Z[i],msg);
                    }
            }
        }
    }
    return e;
}


string settings_transaction_perevod_remove(const DB_id uid, int trid)
{
    MUTEX_INSPECTOR;
    st_dbh d;
    string e;
    string committed=d.dbh->select_1Q((QUERY)"select committed from credits_transactions where from_user=? and id='?'"<<CONTAINER(uid)<<trid);
    if (committed!="1"){
        d.dbh->real_queryQ((QUERY)"delete from credits_transactions where id='?' and from_user=?"<<trid<<CONTAINER(uid));
        e=_MSG("transactionremoved");
    }
    return e;
}
string settings_transaction_zaem_remove(const DB_id uid, int trid)
{
    MUTEX_INSPECTOR;
    st_dbh d;
    string e;
    string committed=d.dbh->select_1Q((QUERY)"select committed from credits_loans where from_user=? and id='?'"<<CONTAINER(uid)<<trid);
    if (committed!="1"){
        d.dbh->real_queryQ((QUERY)"delete from credits_loans where id='?' and from_user=?"<<trid<<CONTAINER(uid));
        e=_MSG("transactionremoved");
    }
    return e;
}



transaction_list settings_transaction_list(const DB_id&uid)
{
    MUTEX_INSPECTOR;
    transaction_list t;

    st_dbh d;
    vector<vector<string> >vp=d.dbh->execQ((QUERY)"select id,to_nick,summa,UNIX_TIMESTAMP(create_time) from credits_transactions where committed=0 and from_user=?"<<CONTAINER(uid));
    vector<vector<string> >vz=d.dbh->execQ((QUERY)
                                           "select id,from_user,to_user,summa,UNIX_TIMESTAMP(create_time),committed,pogashen from credits_loans where (committed=0 or pogashen=0) and (from_user=? or to_user=?)"<<CONTAINER(uid)<<CONTAINER(uid));

    for (unsigned i=0;i<vp.size();i++)
    {
        if (vp[i].size()!=4)
            throw cError("if(vp[i].size()!=4)"+_DMI());

        transaction_list::perevod p;
        p.id=atoi(vp[i][0]);
        p.nick=vp[i][1];
        p.summa.container=atof(vp[i][2].c_str());
        p.create_time=atoi(vp[i][3]);
        t.uncommitted_perevody.push_back(p);

    }
    for (unsigned i=0;i<vz.size();i++)
    {
    try{
        if (vz[i].size()!=7) throw cError("if(vz[i].size()!=7) "+_DMI());
        unsigned int id=atoi(vz[i][0]);
        DB_id fid,tid;
        CONTAINER(fid)=atoi(vz[i][1]);
        CONTAINER(tid)=atoi(vz[i][2]);
        Double summa;summa.container=atof(vz[i][3].c_str());
        time_t create_time=atoi(vz[i][4]);
        bool committed=atoi(vz[i][5]);
        bool pogashen=atoi(vz[i][6]);
        if (fid==uid && committed==false)
        {
            transaction_list::perevod p;
            p.id=id;
            {
                PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(tid)));
				p.nick=u->last_nick;
            }
            p.summa=summa;
            p.create_time=create_time;
            t.uncommitted_zajmy.push_back(p);
        }
        if (committed==true && pogashen==false)
        {
            transaction_list::dolg p;
            p.id=id;
            if (fid==uid)
            {
                {
                    PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(tid)));
					p.corr_nick=u->last_nick;
                }
                p.corr_uid=tid;
                p.is_zajm=true;
            }
            else if (tid==uid)
            {
                {
                    PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(fid)));
					p.corr_nick=u->last_nick;
                }
                p.corr_uid=fid;
                p.is_zajm=false;

            }
            p.summa=summa;
            p.start_time=create_time;
            t.zajmy_dolgi.push_back(p);

        }
	}
	catch(cError e)
	{
		logErr2("ERR %s %s %d",e.what(),__FILE__,__LINE__);
	}
	catch(...)
	{
		logErr2("catched %s %d",__FILE__,__LINE__);
	}
    }
    return t;

}

void url_settings_credits(const PTR_getter<chat_user> &__UU,app_connection *cc)
{
    LICENSE_CK(18);
    MUTEX_INSPECTOR;
    if (!__UU){ cc->html_out=cc->redirect();return;}
    DB_id cc_user_id=user$id(__UU);

    user_pair __U(__UU);

    map<string,string> m;
    string cmd=cc->params["cmd"];
    string e;
    LICENSE_CK(15);
    if (cmd=="pincode_activate")
    {
        time_t last_pincode_entered;
        {
            PGLR(chat_user, u,__UU);
            last_pincode_entered=u->last_pincode_entered;
        }
        if (time(NULL)-last_pincode_entered<15)
        {
            string fmt=_MSG("pincode_too_fast");
            char ss[200];
            snprintf(ss,sizeof(ss),fmt.c_str(),15-(time(NULL)-last_pincode_entered));
            e=ss;
        }
        else
        {
            {
                PGLW(chat_user, u,__UU);
                u->last_pincode_entered=time(NULL);
            }


            MUTEX_LOCK kall(pincode_MX);
            unsigned int v1=atoi(cc->params["v1"]);
            unsigned int v2=atoi(cc->params["v2"]);
            unsigned int v3=atoi(cc->params["v3"]);

            e=settings_proceed_pincode(v1,v2,v3,cc_user_id,GET_CNICK(__U),user$login(__U));

        }

    }
    else if (cmd=="transaction_perevod"){
        string sm=remove_spaces(cc->params["summa_perevod"]);
        sm=str_replace(",",".",sm);
        Double summa;summa.container=atof(sm.c_str());
        if (summa.container<0) throw cError("summa<0"+_DMI());
        string nick=remove_spaces(cc->params["nick_perevod"]);
        e=settings_transaction_perevod_start(cc_user_id,summa,nick);
    }
    else if (cmd=="transaction_zaem"){
        string sm=remove_spaces(cc->params["summa_zaem"]);
        sm=str_replace(",",".",sm);
        Double summa;summa.container=atof(sm.c_str());
        if (summa.container<0) throw cError("summa<0"+_DMI());
        string nick=remove_spaces(cc->params["nick_zaem"]);
        e=settings_transaction_zaem_start(cc_user_id,summa,nick);
    }
    else if (cmd=="commit_perevod"){
        string id=cc->params["id"];
        e=settings_transaction_perevod_commit(cc_user_id, atoi(id), GET_CNICK(__U));
    }
    else if (cmd=="remove_perevod"){
        e=settings_transaction_perevod_remove(cc_user_id,atoi(cc->params["id"]));
    }
    else if (cmd=="commit_zaem"){
        string id=cc->params["id"];
        e=settings_transaction_zaem_commit(cc_user_id, atoi(id), GET_CNICK(__U));
    }
    else if (cmd=="remove_zaem"){
        e=settings_transaction_zaem_remove(cc_user_id,atoi(cc->params["id"]));
    }
    else if (cmd=="zajm_zabrat"){
        e=settings_transaction_dolg_zabrat(cc_user_id,atoi(cc->params["id"]));
    }
    else if (cmd=="zajm_wernut"){
        e=settings_transaction_dolg_otdat(cc_user_id,atoi(cc->params["id"]));
    }
    else if (cmd.size()) logErr2("invalid cmd %s",cmd.c_str());

    transaction_list v=settings_transaction_list(cc_user_id);
    if (v.uncommitted_perevody.size()){
        string r;
        for (unsigned int i=0;i<v.uncommitted_perevody.size();i++){
            map<string,string> q;
            transaction_list::perevod &p=v.uncommitted_perevody[i];
            q["~id~"]=itostring(p.id);
            q["~summa~"]=get_f22(p.summa.container);
            q["~tonick~"]=p.nick;
            q["~create_time~"]=date2rus(p.create_time);
            r+=RVfiles(q,"settings/uncommitted_perevod_row");
        }
        map<string,string> q;
        q["~rows~"]=r;
        m["~uncommitted_perevod~"]=RVfiles(q,"settings/uncommitted_perevod");
    }else{
        m["~uncommitted_perevod~"]="";
    }
    if (v.uncommitted_zajmy.size()){
        string r;
        for (unsigned int i=0;i<v.uncommitted_zajmy.size();i++){
            transaction_list::perevod &p=v.uncommitted_zajmy[i];
            map<string,string> q;
            q["~id~"]=itostring(p.id);
            q["~summa~"]=get_f22(p.summa.container);
            q["~tonick~"]=p.nick;
            q["~create_time~"]=date2rus(p.create_time);
            q["~end_time~"]=date2rus(p.create_time);
            r+=RVfiles(q,"settings/uncommitted_zaem_row");
        }
        map<string,string> q;
        q["~rows~"]=r;
        m["~uncommitted_zajm~"]=RVfiles(q,"settings/uncommitted_zaem");
    }else{
        m["~uncommitted_zajm~"]="";
    }
    if (e.size()){
        m["~error~"]=e;
    }else{
        m["~error~"]="";
    }
    string zajms;
    string dolgs;
    if (v.zajmy_dolgi.size())
    {
        for (unsigned i=0;i<v.zajmy_dolgi.size();i++)
        {
            transaction_list::dolg &d=v.zajmy_dolgi[i];


            {
                map<string,string> q;
                q["~nick~"]=d.corr_nick;
                q["~id~"]=itostring(d.id);
                q["~summa~"]=get_f22(d.summa.container);
                q["~date~"]=date2rus(d.start_time);
                if (d.is_zajm)
                {
                    PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(d.corr_uid)));
					if (u->credit_summa.container>d.summa.container)
						zajms+=RVfiles(q,"settings/u_zajm_ret_row");
					else
						zajms+=RVfiles(q,"settings/u_zajm_row");
				}
                else
                {
                    PGLR(user_profile,u,user$profiles.FindByID(CONTAINER(cc_user_id)));
					if (u->credit_summa.container>d.summa.container)
						dolgs+=RVfiles(q,"settings/u_dolg_ret_row");
					else
						dolgs+=RVfiles(q,"settings/u_dolg_row");
				}

            }

        }
    }
    if (zajms.size())
    {
        map<string,string> q;
        q["~rows~"]=zajms;
        zajms=RVfiles(q,"settings/u_zajm");
    }
    if (dolgs.size())
    {
        map<string,string> q;
        q["~rows~"]=dolgs;
        dolgs=RVfiles(q,"settings/u_dolg");
    }
    m["~zajms~"]=zajms;
    m["~dolgs~"]=dolgs;
    m["~uid~"]=itostring(CONTAINER(cc_user_id));

    {
        PGLR(user_profile, c,user$profiles.FindByID(CONTAINER(cc_user_id)));
		if(c)
		{
			m["~login~"]=c->login;
			m["~credits~"]=get_f22(c->credit_summa.container);
		}
    }


    cc->html_out=cc->rvfiles(m,"settings/credits");
}


