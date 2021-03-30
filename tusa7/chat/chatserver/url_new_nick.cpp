#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#ifndef WIN32
#include <unistd.h>
#endif
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
#include "file_set.h"
#include "web_server_data.h"
#include "web_tools.h"
#include "chat_funny.h"
#include "channels.h"
#include "levels.h"
#include "server_config.h"

#include "app_def.h"
#include "chat_colors.h"
#include "chat_config.h"
#include "register.h"
#include "irc_server_config.h"

#include "update_cmd.h"
#include "html_out.h"
#include "cs_conn_data.h"
#include "chat_globals.h"
#include "user_credits.h"
#include <math.h>

void reload(const PTR_getter<nick_vec> &N);
void send_system_note(const DB_id &uid,const string &subj,const string& msg);

void url_new_nick(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    if (!__UU) return;
    if (inchat$(__UU)) return;
    if (cc->user_unregistered) return;
    user_pair __U(__UU);

    map<string,hstring> m;
    if (cc->params["nick"]=="") {
        m["~msg~"]="";
        m["~nick~"]="";
        cc->html_out=make_pair(m,"new_nick");
        return;
    }
    string nick=cc->params["nick"];
    try {

        if (!check_maty(" "+nick)) {
            m["~nick~"]=nick;
            m["~msg~"]=_MSG("incorrectwordsinnick");
            cc->html_out=make_pair(m,"new_nick");
            return;
        }
        if (!check_nick(nick)) {		//bad nick
            m["~nick~"]=nick;
            m["~msg~"]=_MSG("incorrectnick");
            cc->html_out=make_pair(m,"new_nick");
            return;
        }
        if (nick.size()>16) {		//Nick to long
            m["~nick~"]=nick;
            m["~msg~"]=_MSG("nickistoolong");
            cc->html_out=make_pair(m,"new_nick");
            return;
        }
        {
            st_dbh d;
            vector<string> v=d.dbh->select_1_rowQ((QUERY)
                                                  "select uid,nick,str_nick from nicks where str_nick like '?'"
                                                  <<str_nick(nick)
                                                 );

            if (v.size()>0) {			//Nick exists
                if (v.size()>0)
                {
                    m["~nick~"]=nick;
                    m["~msg~"]=_MSG("nickexists");
                    cc->html_out=make_pair(m,"new_nick");
                    return;
                }
            }
        }
        QUERY q;
        string uinfo_login;
        DB_id uid;
        uinfo_login=user$login(__U);
        uid=user$id(__U);
        if (!can_add_nick(__U))
        {
            m["~nick~"]=nick;
            m["~msg~"]=_MSG("toomanynicks");
            cc->html_out=make_pair(m,"new_nick");
            return;
        }
        unsigned int newid=0;
        {
            PGLW(nick_vec,n,nick_vecs.find_by_id(cc->user_id));
            if (n->u_nicks.size())
                newid=n->u_nicks.rbegin()->first;
        }
        newid++;
        user_nick nnn(nick,newid,cc->user_id,false,0);

        {
            PGLW(nick_vec,n,nick_vecs.find_by_id(cc->user_id));
            n->u_nicks.insert(make_pair(newid,nnn));
        }
        user_unregister_all_nicks(user$id(__U),true);
        out_oscar_buffer b;
        b<<cc->user_id;
        b<<nnn;
        send_update_g2(nick$add,b);
        logErr2("%s registered neu nick '%s'.",user$login(__U).c_str(),nick.c_str());
        {

            user_nick n=user_nick(nick,newid,cc->user_id,false,0);
            out_oscar_buffer o;
            o<<user_state::SET_NICK<<user$id(__U)<<n;
            set_user_state(o);

            DB_id u_dbid=user$id(__U);
            send_update_g3(user_set$last_nick,u_dbid,n.name);
            send_update_g3(user_set$last_nick_id,u_dbid,n.id);

        }
        user_register_all_nicks(user$id(__U),true);

        cc->html_out+="<html><script>window.opener.location='/login?r="+itostring(rand())+"'; window.close();</script>";
    }
    catch (cError e) {
        m["~nick~"]=nick;
        m["~msg~"]=e.error_string;
        cc->html_out=make_pair(m,"new_nick");
    }
}
void url_settings_nick_buy(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);
    vector<string> __vn=splitTOK(".",cc->params["n"]);

    if (__vn.size()!=2) throw cError("__vn.size()!=2");
    DB_id zid;
    unsigned int znid;
    zid.container=atoi(__vn[0].c_str());
    znid=atoi(__vn[1].c_str());
    st_dbh d;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)"select nick,ready_to_sale,cost from nicks where uid=? and id=?"<<zid.container<<znid);
    if (v.size()!=3) throw cError("v.size()!=3");

    string nick=v[0];
    bool ready_to_sale=atoi(v[1].c_str());
    double cost=fabs(atof(v[2].c_str()));
    map<string,hstring>m;
    m["~n~"]=cc->params["n"];
    m["~nick~"]=nick;
    m["~cost~"]=get_f22(cost);
    m["~error~"]="";
    double summa;
    {
        PGLR(user_credit,u,user_credits.find_by_id(cc->user_id));
        summa=u->summa;
    }
    m["~credits~"]=get_f22(summa);
    m["~b_buy~"]="";
    m["~e_buy~"]="";
    if (summa<cost)
    {
        m["~b_buy~"]="<!--";
        m["~e_buy~"]="-->";
    }
    if (cc->params["todo"]=="buy" && ready_to_sale)
    {
        if (summa>cost)
        {
            credit_transaction ct;
            ct.from_user_id=cc->user_id;
            ct.to_user_id=zid;
            ct.summa=cost;
            ct.operation_code="buy_nick";
            ct.t=time(NULL);
            credit_transactions.push_back(ct);
        }
        else throw cError("not enouph credits");

        {
            PGLW(user_credit,u,user_credits.find_by_id(cc->user_id));
            if (summa<cost) throw cError("not enouph credits");
            u->summa.dbset(u->summa.get()-fabs(cost));
            summa=u->summa;

        }
        m["~credits~"]=get_f22(summa);
#ifndef __CLAN
        user_credits.make_1st_update(cc->user_id);
#endif
        send_update_d3(credit$set_summa,cc->user_id,summa);

        double summa2;
        {
            PGLW(user_credit,u,user_credits.find_by_id(zid));
            u->summa.dbset(u->summa.get()+fabs(cost));
            summa2=u->summa;

        }
#ifndef __CLAN
        user_credits.make_1st_update(zid);
#endif
        send_update_d3(credit$set_summa,zid,summa2);

        map<string,string>qq;

        qq["~nick~"]=nick;
        qq["~cost~"]=get_f22(cost);
        send_system_note(zid,RVfiles(qq,"settings/nick_buy_success_note_subj"),RVfiles(qq,"settings/nick_buy_success_note_body"));

        user_unregister_all_nicks(zid,true);
        send_update_g3(nick$remove,zid,znid);

        {
            PGLW(nick_vec, n,nick_vecs.find_by_id(zid));
            n->u_nicks.erase(znid);
        }
        user_register_all_nicks(zid,true);

        unsigned int newid=0;
        {
            PGLW(nick_vec, n,nick_vecs.find_by_id(cc->user_id));
            if (n->u_nicks.size())
                newid=n->u_nicks.rbegin()->first;
        }
        newid++;
        logErr2("%s  bought already registered nick '%s'.",user$login(__U).c_str(),nick.c_str());
        user_unregister_all_nicks(cc->user_id,true);
        user_nick nnn(nick,newid,cc->user_id,false,0);
        {
            PGLW(nick_vec, n,nick_vecs.find_by_id(cc->user_id));
            n->u_nicks.insert(make_pair(newid,nnn));
        }
        {
            out_oscar_buffer o;
            o<<cc->user_id;
            o<<nnn;
            send_update_g2(nick$add,o);
        }
        user_register_all_nicks(cc->user_id,true);


        cc->html_out=make_pair(m,"settings/nick_buy_success");
        return;

    }
    cc->html_out=make_pair(m,"settings/nick_buy");
}
