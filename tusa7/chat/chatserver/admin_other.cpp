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
#include "register.h"

#include <algorithm>
#include "web_server_data.h"
#include "file_set.h"
#include "copy_file.h"

#include "channels.h"
#include "levels.h"
#include "server_config.h"

#include "chat_config.h"
#include "app_def.h"
#include "chat_thread_event.h"
#include "user_set.h"
#include "user_credits.h"
#include "update_cmd.h"
#include "web_tools.h"
#include "cs_conn_data.h"
#include "html_out.h"
#include "chat_globals.h"
#ifndef __CLAN


void send_system_note(const DB_id &uid,const string &subj,const string& msg);

void url_admin_channels(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);
    if (!(user$privileges(__U)&u_is_settings_admin)) return;
    map<string,hstring> m;
    m["~msg~"]="";

    if (cc->params["cmd"]=="addchannel") {
        bool cens=strupper(cc->params["addcensored"])=="ON";
        bool save=strupper(cc->params["addsave"])=="ON";
        st_dbh d;
        d.dbh->real_queryQ((QUERY)"insert into channels (censored,save,move_to_channel) values (?,?,0)"<<cens<<save);
        string id=d.dbh->select_1("select LAST_INSERT_ID() from channels");
        chat_channel *ms=new chat_channel();
        if (!ms)throw cError("!ms ");

        ms->cd.chid.container=atoi(id.c_str());
        ms->cd.censored=cens;
        ms->cd.save_messages=save;
        ms->cd.move=false;
        ms->cd.move_to_channel=0;
        ms->cd.names[""]=cc->params["add"];
        ms->cd.names["2"]=cc->params["add2"];
        d.dbh->real_queryQ((QUERY)"insert into channels_names (cid,lang,name) values (?,'','?')"<<id<<cc->params["add"]);
        d.dbh->real_queryQ((QUERY)"insert into channels_names (cid,lang,name) values (?,'2','?')"<<id<<cc->params["add2"]);
        chat_channels.add(ms->cd.chid,ms);

        chat_event_SEND_DATA_TO_WWW_USERS *e=new chat_event_SEND_DATA_TO_WWW_USERS;
        e->msg="<script>window.top.location.reload();</script>";
        send_chat_event(e,false);

        m["~msg~"]=_MSG("added");
    }
    if (cc->params["cmd"]=="del") {
        vector<PTR_getter<chat_user> > k=local_users.values();
        CH_id id;
        id.container=atoi(cc->params["id"].c_str());
        bool may_del=true;
        st_dbh d;
        if (may_del) {
            d.dbh->real_queryQ((QUERY)"delete from channels where id=?"<<id.container);
            d.dbh->real_queryQ((QUERY)"delete from channels_names where cid=?"<<id.container);

            m["~msg~"]=_MSG("channelremoved");
            chat_event_SEND_DATA_TO_WWW_USERS *e=new chat_event_SEND_DATA_TO_WWW_USERS;
            e->msg="<script>window.top.location.reload();</script>";
            send_chat_event(e,false);

        } else {
            m["~msg~"]=_MSG("cantremovechannel");
        }
    }
    if (cc->params["cmd"]=="change") {
        CH_id id;
        id.container=atoi(cc->params["id"].c_str());
        bool cens=strupper(cc->params["c"+itostring(id.container)])=="ON";
        bool save=strupper(cc->params["s"+itostring(id.container)])=="ON";
        bool move=strupper(cc->params["nm"+itostring(id.container)])=="ON";
        bool no_stat=strupper(cc->params["ns"+itostring(id.container)])=="ON";
        bool ext=strupper(cc->params["e"+itostring(id.container)])=="ON";
        int read_level=atoi(cc->params["rl"+itostring(id.container)].c_str());
        int write_level=atoi(cc->params["wl"+itostring(id.container)].c_str());
        string irc_name=cc->params["irc_name"+itostring(id.container)];
        int mtc=atoi(cc->params["m"+itostring(id.container)].c_str());
        {
            __CH_LOCKW(chat_channels[id]);
            CH->cd.censored=cens;
            CH->cd.save_messages=save;
            CH->cd.move_to_channel=mtc;
            CH->cd.move=move;
            CH->cd.no_statistic=no_stat;
            CH->cd.extended=ext;
            CH->cd.read_level=read_level;
            CH->cd.write_level=write_level;
            CH->cd.irc_name=irc_name;
        }
        st_dbh d;
        d.dbh->real_queryQ((QUERY)"update channels set censored=?, save=?, move_to_channel=?,move=?,no_stat=?,ext=?,read_level=?,write_level=?, irc_name='?' where id=?"<<cens<<save<<mtc<<move<<no_stat<<ext<<read_level<<write_level<<irc_name<<id.container);
        m["~msg~"]=_MSG("changed");
    }
    st_dbh d;
    vector< vector<string> > v=d.dbh->execQ((QUERY)
                                            "select a.id,a.censored,a.save,a.move_to_channel,"
                                            "a.move,b.name,a.no_stat,a.ext,a.read_level,"
                                            "a.write_level,a.irc_name from channels a, channels_names b where b.cid=a.id and b.lang='2'");
    hstring data;


    for (unsigned int i=0;i<v.size();i++) {
        if (v[i].size()!=11) throw cError("select failed");
        map<string,hstring> q;
        q["~id~"]=v[i][0];
        q["~censored~"]=checked(atoi(v[i][1].c_str()));
        q["~save~"]=checked(atoi(v[i][2].c_str()));
        q["~move_to_channel~"]=v[i][3];
        q["~move~"]=checked(atoi(v[i][4].c_str()));
        q["~name~"]=v[i][5];
        q["~no_stat~"]=checked(atoi(v[i][6].c_str()));
        q["~ext~"]=checked(atoi(v[i][7].c_str()));
        int rl=atoi(v[i][8].c_str());
        int wl=atoi(v[i][9].c_str());
        q["~irc_name~"]=v[i][10];

        map<unsigned int, c_level> lvl;
        lvl=LEVELS_GET();
        string sr="<SELECT name=rl"+v[i][0]+">",sw="<SELECT name=wl"+v[i][0]+">";
        for (map<unsigned int,c_level>::iterator j=lvl.begin();j!=lvl.end();j++) {
            sr+="<option value="+itostring(j->first);
            sw+="<option value="+itostring(j->first);
            if (j->first==rl) sr+=" SELECTED";
            if (j->first==wl) sw+=" SELECTED";
            sr+=">"+j->second.name(0)+"\r\n";
            sw+=">"+j->second.name(0)+"\r\n";
        }
        sr+="</SELECT>";
        sw+="</SELECT>";
        q["~read_level~"]=sr;
        q["~write_level~"]=sw;
        data+=make_pair(q,"admin/channels/channels_row");
    }
    m["~channels~"]=data;
    data="";
    map<string,hstring> q;
    q["~lang~"]="";
    q["~flang~"]="";
    data+=make_pair(q,"admin/channels/channels_add");
    m["~addchannel~"]=data;
    cc->html_out=make_pair(m,"admin/channels/channels");
}

void url_admin_credgen(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);
    if (!(user$privileges(__U)&u_is_credit_operator)) return;
    st_dbh d;
    map<string,hstring> m;
    m["~msg~"]="";
    map<string,string> c;
    c["WM"]="WM";
    c["BANK"]="BANK";
    c["OTHER"]="Другое";
    string code="OTHER";

    if (cc->params["code"]=="WM" ||cc->params["code"]=="BANK") code=cc->params["code"];
    m["~code~"]=make_select("code",c,code," onchange='document.f.submit();return false;'");

    if (cc->params["cmd"]=="" ||cc->params["cmd"]=="conf")
    {
        m["~id~"]="";
        m["~summa~"]="";
        m["~comment~"]="";
        m["~cmd~"]="za4";
        m["~butname~"]="Зачислить";
    }
    if (cc->params["cmd"]=="za4")
    {
        string login;
        DB_id uid;
        uid.container=atoi(cc->params["id"].c_str());
        {
            PGLR(user_profile,u,user_profiles.find_by_id(uid));
            login=u->login;
        }
        m["~id~"]=cc->params["id"];
        double summa=atof(cc->params["summa"].c_str());
        m["~summa~"]=get_f22(summa);

        m["~comment~"]=cc->params["comment"];
        m["~cmd~"]="conf";
        m["~msg~"]="Подтвердите зачисление на логин "+login+" суммы "+get_f22(summa)+ " кр.";
        m["~butname~"]="Подтвердить";

    }
    if (cc->params["cmd"]=="conf")
    {
        DB_id uid;
        uid.container=atoi(cc->params["id"].c_str());
        string comment=cc->params["comment"];
        string login;
        {
            PGLR(user_profile,u,user_profiles.find_by_id(uid));
            login=u->login;
        }

        double summa=atof(cc->params["summa"].c_str());

        credit_transaction ct;
        ct.from_user_id=cc->user_id;
        ct.to_user_id=uid;
        ct.summa=summa;
        ct.operation_code="credgen";
        ct.t=time(NULL);
        credit_transactions.push_back(ct);
        map<string,string> q;
        q["~summa~"]=get_f22(summa);
        q["~comment~"]=comment;
        send_system_note(uid,RVfiles("admin/credgen/note_subj"),RVfiles(q,"admin/credgen/note_body"));
        double csumma;
        {
            PGLR(user_credit,u,user_credits.find_by_id(uid));
            csumma=u->summa;
        }
        send_update_d3(credit$set_summa,uid,csumma+summa);
        d.dbh->real_queryQ((QUERY)"insert into credit_bank (code,summa,touid,comment,dt) values('?','?','?','?',NOW())"<<code<<summa<<uid.container<<comment);
        m["~msg~"]=RVfiles("admin/credgen/op_committed");

    }

    vector<vector<string> > v;
    if (code=="OTHER")	v=d.dbh->execQ((QUERY)"select id,code,summa,touid, comment,dt from credit_bank order by dt desc limit 20");
    else 	v=d.dbh->execQ((QUERY)"select id,code,summa,touid, comment,dt from credit_bank where code='?' order by dt desc limit 20"<<code);

    hstring rows;
    rows+="<table>";
    rows +=RVfiles("admin/credgen/table_head");
    for (unsigned i=0;i<v.size();i++)
    {
        if (v[i].size()==6)
        {
            string id=v[i][0];
            string cod=v[i][1];
            string sm=v[i][2];
            DB_id zid;
            zid.container=atoi(v[i][3].c_str());
            string comm=v[i][4];
            string dt=v[i][5];
            string lg;
            {
                PGLR(user_profile,u,user_profiles.find_by_id(zid));
                lg=u->login;
            }
            rows+="<tr>";
            rows+="<td>"+id+"</td>";
            rows+="<td>"+cod+"</td>";
            rows+="<td>"+itostring(zid.container)+"</td>";
            rows+="<td>"+lg+"</td>";
            rows+="<td>"+sm+"</td>";
            rows+="<td>"+dt+"</td>";
            rows+="<td>"+comm+"</td>";
            rows+="</tr>";
        }
    }
    rows+="</table>";
    m["~rows~"]=rows;
    cc->html_out=make_pair(m,"admin/credgen/credgen");

}
bool load_hints();

void url_admin_hints(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);
    if (!(user$privileges(__U)&u_is_hints_admin)) return;
    map<string,hstring> m;
    m["~msg~"]="";
    if (cc->params["cmd"]=="add") {
        string uid;
        string id;
        st_dbh d;
        d.dbh->real_queryQ((QUERY)"insert into hints (txt) values ('?')"<<cc->params["add"]);
        uid=d.dbh->select_1("select LAST_INSERT_ID() from hints");
        id=uid;
        d.dbh->real_queryQ((QUERY)"update hints set uid=? where id=?"<<uid<<id);
        load_hints();
        m["~msg~"]=_MSG("added");
    }
    if (cc->params["remove"].size()) {
        st_dbh d;
        d.dbh->real_queryQ((QUERY)"delete from hints where uid=?"<<cc->params["remove"]);
        m["~msg~"]=_MSG("hintremoved");
        load_hints();
    }
    if (cc->params["id"].size()) {
        st_dbh d;
        vector< vector<string> > v=d.dbh->execQ((QUERY)"select txt from hints where uid='?'"<<cc->params["id"]);
        string h;
        for (unsigned int i=0;i<v.size();i++) {
            if (v[i].size()!=1) throw cError("select failed.");
            h+=v[i][0];
            h+="<br><br>";
        }
        m["~hint~"]=h;
        cc->html_out=make_pair(m,"admin/hints/hint");
        return;
    }
    st_dbh d;
    vector< vector<string> > v=d.dbh->execQ((QUERY)"select uid,txt from hints order by id");
    hstring out;
    for (unsigned int i=0;i<v.size();i++) {
        if (v[i].size()!=2) throw cError("select failed.");
        map<string,hstring> q;
        q["~id~"]=v[i][0];
        string h=v[i][1];
        if (!(user$privileges(__U)&u_allow_tags)) h=remove_tags(h);
        if (h.size()>70) h=h.substr(0,70)+"...";
        q["~hint~"]=h;
        out+=make_pair(q,"admin/hints/hints_row");
    }
    m["~hints~"]=out;
    out="";
    {
        map<string,hstring> q;
        q["~flang~"]="";
        q["~lang~"]="";
        out+=make_pair(q,"admin/hints/hint_add");

    }
    m["~addhint~"]=out;
    cc->html_out=make_pair(m,"admin/hints/hints");
}
#endif
