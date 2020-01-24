#include "stdafx.h"
#include "_mutex.h"
#include <list>
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
#include "register.h"
#include "copy_file.h"
#include "wrappers.h"
#include "web_tools.h"
#include "file_set.h"

#include "user_credits.h"
#include "levels.h"
#include "server_config.h"
#include "chat_colors.h"
//#include "app_con.h"
#include "app_def.h"
#include "update_cmd.h"
#include "html_out.h"
#include "cs_conn_data.h"
#include "chat_globals.h"

void send_system_note(const DB_id &uid,const string &subj,const string& msg);

_mutex pincode_MX("pincode_MX");
void url_settings_credits(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);

    st_dbh d;
    map<string,hstring> m;
    string cmd=cc->params["cmd"];
    string e;
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
            unsigned int v1=atoi(cc->params["v1"].c_str());
            unsigned int v2=atoi(cc->params["v2"].c_str());
            unsigned int v3=atoi(cc->params["v3"].c_str());
            st_dbh d;
            vector<string> v=d.dbh->select_1_rowQ((QUERY)"select v1,v2,v3,summa,accepted from pincodes where v1='?' and v2='?' and v3='?'"<<v1<<v2<<v3);
            if (v.size()==5)
            {
                if (v[4]=="1") // accepted
                {

                    e=_MSG("pincode_already_used");
                    logErr2("entered used pincode (%d-%d-%d) from user %s (%s)",v1,v2,v3,GET_CNICK(__U).c_str(),string(user$login(__U)).c_str());
                }
                else
                {
                    int summa=atoi(v[3].c_str());
                    string fmt=_MSG("accepted_credits");
                    char s[200];
                    {
                        snprintf(s,sizeof(s),fmt.c_str(),summa);
                    }
                    e=s;
                    double rsum;
                    {
                        PGLW(user_credit, c,user_credits.find_by_id(cc->user_id));
                        rsum=c->summa+summa;
                        c->summa.dbset(rsum);

                    }
#ifndef __CLAN
                    user_credits.make_1st_update(cc->user_id);
#endif
                    send_update_d3(credit$set_summa,cc->user_id,rsum);

                    {
                        credit_transaction ct;
                        ct.from_user_id=cc->user_id;
                        ct.to_user_id=cc->user_id;
                        ct.summa=summa;
                        ct.operation_code="pincode";
                        ct.t=time(NULL);
                        credit_transactions.push_back(ct);
                    }

                    d.dbh->real_queryQ((QUERY)"update pincodes set accepted='1', date_accepted=NOW(), accepted_by_uid=? where v1='?' and v2='?' and v3='?'"<<cc->user_id.container<<v1<<v2<<v3);
                    {
                        logErr2("accepted pincode=%d-%d-%d summa=%d from user %s (%s)",v1,v2,v3,summa,GET_CNICK(__U).c_str(),string(user$login(__U)).c_str());
                    }

                }
            }
            else
            {
                e=_MSG("invalid_pincode");
                logErr2("invalid pincode (%d-%d-%d) from user %s (%s)",v1,v2,v3,GET_CNICK(__U).c_str(),string(user$login(__U)).c_str());

            }
        }

    }
    if (cmd=="transaction") {
        string sm=remove_spaces(cc->params["summa"].c_str());
        sm=str_replace(",",".",sm);
        double summa=atof(sm.c_str());
        double remained_sum=0;
        {
            PGLR(user_credit, c,user_credits.find_by_id(cc->user_id));
            if (c) {
                remained_sum=c->summa;
            }
        }
        if (summa>remained_sum) {
            e=_MSG("notenoughcredits");
        } else {
            string nick=remove_spaces(cc->params["nick"]);
            if (summa<=0) {
                e=_MSG("nulltransaction");
            } else {
                int id=atoi(d.dbh->select_1Q((QUERY)"select uid from nicks where str_nick like '?'"<<MESL(str_nick(nick))).c_str());
                if (id<=0) {
                    e=_MSG("nicknotfound");
                } else {
                    d.dbh->real_queryQ((QUERY)"insert into credits_transactions (summa,from_user,to_user,to_nick,create_time) values(?,?,?,'?',NOW())"<<summa<<cc->user_id.container<<id<<nick);
                    e=_MSG("transactiondone");
                }
            }
        }
    }
    else if (cmd=="commit") {
        string id=cc->params["id"];
        vector<string> v=d.dbh->select_1_rowQ((QUERY)"select summa,to_user,committed from credits_transactions where from_user=? and id='?'"<<cc->user_id.container<<id);
        if (v.size()==3) {
            if (v[2]=="0") {
                d.dbh->real_queryQ((QUERY)"update credits_transactions set committed=1,commit_time=NOW() where id='?'"<<id);
                bool allok=false;
                double summa=atof(v[0].c_str());
                double rsum;
                {
                    PGLW(user_credit, c,user_credits.find_by_id(cc->user_id));
                    rsum=c->summa-summa;
                    if (rsum>0) {
                        c->summa.dbset(rsum);
                        allok=true;
                    }
                }
                if (allok)
                    send_update_d3(credit$set_summa,cc->user_id,rsum);

                if (allok) {
                    {
                        PGLW(user_credit, c,user_credits.find_by_id(atoi(v[1].c_str())));
                        rsum=c->summa+summa;
                        c->summa.dbset(rsum);
                        e=_MSG("committed");
                    }
#ifndef __CLAN
                    user_credits.make_1st_update(atoi(v[1].c_str()));
#endif
                }
                if (allok)
                    send_update_d3(credit$set_summa,atoi(v[1].c_str()),rsum);

                if (allok)
                {
                    credit_transaction ct;
                    ct.from_user_id=cc->user_id;
                    ct.to_user_id.container=atoi(v[1].c_str());
                    ct.summa=summa;
                    ct.operation_code="manual_transfer";
                    ct.t=time(NULL);
                    credit_transactions.push_back(ct);
                    DB_id tuid;
                    tuid.container=atoi(v[1].c_str());
                    map<string,string> mm;
                    mm["~from~"]=GET_CNICK(__U);
                    mm["~summa~"]=get_f22(summa);
                    string msg=RVfiles(mm,"settings/credit_transfer_msg");
                    send_system_note(tuid,_MSG("credit_tansfer"),msg);
                    PTR_getter<chat_user> __Z=local_users.get(tuid);
                    if (__Z)
                    {
                        send_syspriv_msg(__Z,msg);
                    }
                }
            }
        }
    }
    else if (cmd=="remove") {
        string id=cc->params["id"];
        string committed=d.dbh->select_1Q((QUERY)"select committed from credits_transactions where from_user=? and id='?'"<<cc->user_id.container<<id);
        printf("'%s'\n",committed.c_str());
        if (committed!="1") {
            d.dbh->real_queryQ((QUERY)"delete from credits_transactions where id='?' and from_user=?"<<id<<cc->user_id.container);
            e=_MSG("transactionremoved");
        }
    }

    vector< vector<string> > v=d.dbh->execQ((QUERY)"select id,to_nick,summa,create_time from credits_transactions where committed=0 and from_user=?"<<cc->user_id.container);
    if (v.size()) {
        hstring r;
        for (unsigned int i=0;i<v.size();i++) {
            if (v[i].size()!=4) throw cError("select failed");
            map<string,hstring> q;
            q["~id~"]=v[i][0];
            q["~summa~"]=v[i][2];
            q["~tonick~"]=v[i][1];
            q["~create_time~"]=v[i][3];
            r+=make_pair(q,"settings/uncommitted_row");
        }
        map<string,hstring> q;
        q["~rows~"]=r;
        m["~uncommitted~"]=make_pair(q,"settings/uncommitted");
    } else {
        m["~uncommitted~"]="";
    }
    if (e.size()) {
        m["~error~"]=e;
    } else {
        m["~error~"]="";
    }

    m["~uid~"]=itostring(cc->user_id.container);
    {
        PGLR(user_profile, c,user_profiles.find_by_id(cc->user_id));
        m["~login~"]=c->login;

    }
    {
        PGLR(user_credit, c,user_credits.find_by_id(cc->user_id));
        m["~credits~"]=get_f22(c->summa);
    }


    cc->html_out=make_pair(m,"settings/credits");
}


