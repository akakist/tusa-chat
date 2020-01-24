#ifdef __GNUC__
#pragma implementation
#endif

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
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "web_server.h"
#include "message.h"
#include "chat_def.h"
#include "register.h"
#include "file_set.h"
#include "levels.h"
#include "server_config.h"

#include "chat_config.h"

#include "fotos.h"
#include "irc_utils.h"
#include "user_credits.h"
#include "update_cmd.h"
#include "contact_vec.h"
#include "user_stat.h"
#include "html_out.h"
#include "cs_conn_data.h"
#include "chat_globals.h"
#include "DR_types.h"
vector< vector<string> > gallery_request(const string &snick);
vector<string> select_uid_nick_by_ids(const DB_id &uid, unsigned int nid);
DB_id get_uid_by_nick(const string& nick);

void url_gallery(const PTR_getter<chat_user>&__UU,cs_conn_data *cc)
{
//updater upd;
    bool adm=cc->sub_level>=am_admin;
    map<string,hstring> m;
    string s=remove_spaces(cc->params["s"]);
    m["~data~"]="";
    m["~founded~"]="";
    m["~search~"]=s;


    int n_id=0;
    DB_id zid;

    vector<string> vnz=splitTOK(".",cc->params["ni"]);
    if (vnz.size()==2)
    {
        zid.container=atoi(vnz[0]);
        n_id=atoi(vnz[1]);
    }

    if (s=="" && n_id==0) {
        cc->html_out+=make_pair(m,"gallery_template");
        return;
    }
    hstring error;
    bool logined=local_users.count(__UU);

    if (cc->params.count("buy") && logined)
    {
        user_pair __U(__UU);
        double summa;
        {
            PGLR(user_credit, b,user_credits.find_by_id(cc->user_id));
            summa=b->summa;
        }
        if (summa<chat_config2.nick_cost.get())
        {
            error=FREP("gallery_noen_credits");

        }
        else if (logined)
        {


        }

    }
    if (s!="") {

        string sr=s;
        if (sr=="") {
            m["~founded~"]=_MSG("emptyquery");
            cc->html_out+=make_pair(m,"gallery");
            return;
        }
        string snick=sr;
        vector< vector<string> > v;
        {
            v=gallery_request(snick);
        }

        if (v.size()==1) {

            if (v[0].size()!=4) {
                throw cError("select failed. size different!");
            }
            zid.container=atoi(v[0][1]);
            n_id=atoi(v[0][0]);
        } else {

            bool r=false;
            hstring d;
            string nb;
            unsigned int l=atoi(cc->params["l"]);
            if (l<0 || l>=v.size()) {
                l=0;
            }
            m["~founded~"]=_MSG("founded")+": "+itostring(v.size());
            for (unsigned int i=0;i<v.size();i+=50) {
                if (i==l) {
                    nb<<"["<<itostring(i)<<"] ";
                } else {
                    nb<<"<a class=nick href=\"/gallery?s="<<s<<"&l="<<itostring(i)<<"\">["<<itostring(i)<<"]</a>&nbsp;";
                }
                if (i%500==0) {
                    nb+="<br>";
                }
            }
            d<<"<tr><td colspan=2 align=center>"<<nb<<"</td></tr>";
            int ready_to_sale_cnt=0;
            {
                for (unsigned int i=l;i<l+50;i++) {
                    if (i>=v.size()) {
                        break;
                    }
                    if (v[i].size()!=4) {
                        throw cError("select failed. size different!");
                    }
                    if (!r) {
                        d<<"<tr>";
                    }
                    d<<"<td width=200 align=center><a href=\"/gallery?ni="<<v[i][1]+"."+v[i][0]<<"\">"<<v[i][2]<<"</a>";
                    if (v[i][3]=="1" && logined)    //ready_to_sale
                    {
                        ready_to_sale_cnt++;
                        d<<" <a href='#' onclick='return do_bnick(\""+v[i][1]+"."+v[i][0]+"\");'>"<<_MSG("buy_nick")<<"</a>";
                    }
                    d<<"</td>";
                    if (r) {
                        d<<"</tr>";
                    }
                    r=!r;
                }
            }
            if (error.hstr_size())
            {
                logErr2("error.hstr_size()");
                d<<error;
            }
            else
            {
                if (cc->params.count("buy")==0 &&  ready_to_sale_cnt && logined)
                {
                    map<string,hstring> q;
                    q["~cost~"]=get_f22(chat_config2.nick_cost.get());
                    d+=make_pair(q,"gallery_buy_rules");

                }
            }

            m["~data~"]=d;
        }
    }
    if (n_id!=0)
    {
        vector<string> v;
        v=select_uid_nick_by_ids(zid, n_id);
        if (zid.container==0) {
            m["~founded~"]=_MSG("usernotfound");
            cc->html_out+=make_pair(m,"gallery");
            return;
        }

        time_t last_date;
        string last_ip;
        int v_count;
        int m_count;
        time_t t_count;
        unsigned int kick_count;
        unsigned int kicked_count;

        {
            PGLR(user_stat,u,user_stats.find_by_id(zid));
            last_date=u->last_date;
            last_ip=u->last_ip;
            v_count=u->v_count;
            m_count=u->m_count;
            t_count=u->t_count;
            kick_count=u->kick_count;
            kicked_count=u->kicked_count;
        }

        hstring d;
        if (v.size()==2)
        {
            d<<"<tr valign=middle><td colspan=2 align=center><b><big>"<<v[1]<<"</big></b>";
        }
        if (adm) {
            d<<"&nbsp;&nbsp;&nbsp;<a href=\"javascript: opwin('/admin/logininfo?id="<<itostring(zid.container)<<"',550,500)\"><img src=\"/pics/quest.gif\" width=24 height=24 border=0 alt='Login info'></a>";
        }
        d<<"</td></tr>";
        d<<make_user_info(zid,cc->user_id,adm,false,"","",logined);
        {
            PGLR(user_profile,z,user_profiles.find_by_id(zid));


            if (z->info.size()) {
                d<<"<tr><td align=center colspan=2><hr class=hr size=2 width=\"100%\"></td></tr>";
            }
            {
                map<string,hstring> q;
                q["~reg_date~"]=datetime2rus(z->reg_date);
                q["~last_date~"]=datetime2rus(last_date);
                d+=make_pair(q,"user_info/dates");
            }
            if (adm) {
                map<string,hstring> q;
                q["~m_count~"]=itostring(m_count);
                q["~t_count~"]=make_time(t_count);
                q["~v_count~"]=itostring(v_count);
                d+=make_pair(q,"user_info/stat");
            }
            d<<"<tr><td colspan=2 align=center><a href=\"javascript: history.back(1)\">"<<_MSG("back")<<"</a></td></tr>";
            m["~data~"]=d;
            if (v.size()==2)
            {
                m["~search~"]=v[1];
            }
        }

    }

    cc->html_out+=make_pair(m,"gallery");
}


void url_a_user_info(cs_conn_data *cc)
{

    bool admin=cc->sub_level>=am_admin;

    map<string,hstring> m;
    m["~nick~"]="";
    vector<string> v=splitTOK(".",cc->params["id"]);
    if (v.size() && v.size()!=2)
    {
        throw cError("params id must be 2 "+cc->params["id"]);
    }
    unsigned int id;

    DB_id zid;
    if (v.size()==2)
    {
        zid.container=atoi(v[0]);
        id=atoi(v[1]);
    }
    m["~admin~"]="<!--";
    m["~eadmin~"]="-->";

    if (cc->params["n"]!="") {
        zid=get_uid_by_nick(cc->params["n"]);
    } else {
    }
    if (zid.container==0) {
        string ss;
        ss<<"<tr><td>"<<_MSG("usernotfound2")<<"</td></tr>";
        m["~userinfo~"]=ss;
        cc->html_out+=make_pair(m,"a_user_info");
        return;
    }
    if (admin) {
        m["~admin~"]="";
        m["~eadmin~"]="";
    }
    string nick;
    if (cc->params["n"]=="") {
    } else {
        nick=cc->params["n"];
    }
    m["~nick~"]=nick;
    m["~id~"]=itostring(zid.container);
    m["~userinfo~"]=make_user_info(zid,cc->user_id,admin,false,"","", cc->user_id.container!=0);
    cc->html_out+=make_pair(m,"a_user_info");
}



