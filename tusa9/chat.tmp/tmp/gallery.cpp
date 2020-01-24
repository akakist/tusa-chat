
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
#include "file_set.h"
#include "levels.h"
#include "server_config.h"

#include "chat_config.h"

#include "irc_utils.h"
#include "user_credits.h"
#include "update_cmd.h"
#include "contact_vec.h"
#include "user_profile.h"
#include "html_out.h"
#include "time_limit.h"

#include "chat_globals.h"
#include "DR_types.h"
#include "app_con.h"
#include "web_tools.h"
vector< vector<string> > gallery_request(const string &snick);
vector<string> select_uid_nick_by_ids(const DB_id& uid, unsigned int nid);
DB_id get_uid_by_nick(const string& nick);

void url_gallery(const PTR_getter<chat_user>&__UU,app_connection*cc)
{
    CKTIME;

    MUTEX_INSPECTOR;
#ifdef TUSA    
    if (!__UU){ cc->html_out=cc->redirect();return;}
#endif    

    bool adm=cc->sub_level>=am_admin;
    map<string,string> m;
    string sT;
    int n_id=0;
    DB_id zid;CONTAINER(zid)=0;CONTAINER(zid)=0;
    m["~data~"]="";
    m["~founded~"]="";
    if (cc->vurl.size())
    {
        string val=cc->vurl[0];
        cc->vurl.pop_front();
        vector<string> v=splitTOK(".",val);
        if (v.size()==2)
        {
            CONTAINER(zid)=atoi(v[0]);
            n_id=atoi(v[1]);
        }
        else
        {
            sT=val;
            sT=remove_spaces(sT);
        }

    }
    if (cc->params.count("s"))
        sT=cc->params["s"];
    m["~search~"]=sT;






    if (sT=="" && (n_id==0|| CONTAINER(zid)==0 ||CONTAINER(zid)==7 )){
        cc->html_out+=cc->rvfiles(m,"gallery_template"); return;
    }
    string error;
    bool logined=local_users.count$(__UU);


    if (sT!=""){

        string sr=sT;
        if (sr==""){
            m["~founded~"]=_MSG("emptyquery");
            cc->html_out+=cc->rvfiles(m,"gallery");
            return;
        }
        string snick=sr;
        vector< vector<string> > v;
        {
            v=gallery_request(snick);
        }

        if (v.size()==1){

            if (v[0].size()!=4){throw cError("select failed. size different!"+_DMI());}
            CONTAINER(zid)=atoi(v[0][1]);
            n_id=atoi(v[0][0]);
        }else{

            bool r=false;
            string d;
            string nb;
            unsigned int l=0;
            if (cc->vurl.size())
            {
                l=atoi(cc->vurl[0]);
                cc->vurl.pop_front();
            }

            if (l<0 || l>=v.size()){l=0;}
            m["~founded~"]=_MSG("founded")+": "+itostring(v.size());
            for (unsigned int i=0;i<v.size();i+=50){
                if (i==l){
                    nb<<"["<<itostring(i)<<"] ";
                }else{
                    nb<<"<a class=nick href=\"/ca/gallery/"<<sT<<"/"<<itostring(i)<<"\">["<<itostring(i)<<"]</a>&nbsp;";
                }
                if (i%500==0){
                    nb+="<br>";
                }
            }
            d<<"<tr><td colspan=2 align=center>"<<nb<<"</td></tr>";
            int ready_to_sale_cnt=0;
            {
                for (unsigned int i=l;i<l+50;i++){
                    if (i>=v.size()){break;}
                    if (v[i].size()!=4){throw cError("select failed. size different!"+_DMI());}
                    if (!r){
                        d<<"<tr>";
                    }
                    d<<"<td width=200 align=center><a href=\"/ca/gallery/"<<v[i][1]+"."+v[i][0]<<"\">"<<v[i][2]<<"</a>";
                    if (v[i][3]=="1" && logined)    //ready_to_sale
                    {
                        ready_to_sale_cnt++;
                        d<<" <a href='#' onclick='return do_bnick(\""+v[i][1]+"."+v[i][0]+"\");'>"<<_MSG("buy_nick")<<"</a>";
                    }
                    d<<"</td>";
                    if (r){
                        d<<"</tr>";
                    }
                    r=!r;
                }
            }
            if (error.size())
            {
                logErr2("error.hstr_size()");
                d+=error;
            }
            else
            {

            }

            m["~data~"]=d;
        }
    }
    if (n_id!=0)
    {
        vector<string> v;
        v=select_uid_nick_by_ids(zid, n_id);
        if (CONTAINER(zid)==0){
            m["~founded~"]=_MSG("usernotfound");
            cc->html_out+=cc->rvfiles(m,"gallery");
            return;
        }

        time_t stat_last_date;
        string stat_last_ip;
        int stat_v_count;
        int stat_m_count;
        time_t stat_t_count;
        unsigned int kick_count;
        unsigned int kicked_count;

        if (CONTAINER(zid))
        {
            PTR_getter<user_profile> __P=user$profiles.FindByID(CONTAINER(zid));
            if (__P)
            {
                PGLR(user_profile,u,__P);
                stat_last_date=u->stat_last_date;
                stat_last_ip=u->stat_last_ip;
                stat_v_count=u->stat_v_count;
                stat_m_count=u->stat_m_count;
                stat_t_count=u->stat_t_count;
                kick_count=u->kick_count;
                kicked_count=u->kicked_count;
            }
            else
            {
                throw cError("err load __P %s %d %s",__FILE__,__LINE__,_DMI().c_str());
            }
        }

        string d;
        if (v.size()==2)
        {
            d<<"<tr valign=middle><td colspan=2 align=center><b><big>"<<v[1]<<"</big></b>";
        }
        if (adm){
            d<<"&nbsp;&nbsp;&nbsp;<a href=\"javascript: opwin('/admin/logininfo?id="<<itostring(CONTAINER(zid))<<"',550,500)\"><img src=\"/pics/quest.gif\" width=24 height=24 border=0 alt='Login info'></a>";

        }
        if (cc->sub_level>=am_killer)
        {
            map<string,string> q;
            q["~id~"]=itostring(CONTAINER(zid));
            d<<RVfiles(q,"user_info/ban_uid");
        }

        d<<"</td></tr>";
        string out_www,out_irc;
        DB_id cc_user_id;CONTAINER(cc_user_id)=0;
        if (__UU)
            cc_user_id=user$id(__UU);


        make_user_info(zid,cc_user_id,adm,"","",logined,out_www,out_irc);
        d<<out_www;
        {
            PTR_getter<user_profile> __P=user$profiles.FindByID(CONTAINER(zid));
            if (__P)
            {
                PGLR(user_profile,z,__P);


                if (z->info.size()){
                    d<<"<tr><td align=center colspan=2><hr class=hr size=2 width=\"100%\"></td></tr>";
                }
                {
                    map<string,string> q;
                    q["~reg_date~"]=datetime2rus(z->reg_date);
                    q["~stat_last_date~"]=datetime2rus(stat_last_date);
                    d+=RVfiles(q,"user_info/dates");
                }
                if (adm){
                    map<string,string> q;
                    q["~stat_m_count~"]=itostring(stat_m_count);
                    q["~stat_t_count~"]=make_time(stat_t_count);
                    q["~stat_v_count~"]=itostring(stat_v_count);
                    d+=RVfiles(q,"user_info/stat");
                }
                d<<"<tr><td colspan=2 align=center><a href=\"javascript: history.back(1)\">"<<_MSG("back")<<"</a></td></tr>";
                m["~data~"]=d;
                if (v.size()==2)
                {
                    m["~search~"]=v[1];
                }
            }
            else
            {
                throw cError("err load __P %s %d %s",__FILE__,__LINE__,_DMI().c_str());
            }
        }

    }

    cc->html_out+=cc->rvfiles(m,"gallery");
}


void url_a_user_info(const PTR_getter<chat_user>&__UU, app_connection *cc)
{
    MUTEX_INSPECTOR;
    CKTIME;

    bool admin=cc->sub_level>=am_admin;

    map<string,string> m;
    m["~nick~"]="";

    vector<string> v;
    unsigned int id;
    DB_id zid;CONTAINER(zid)=0;CONTAINER(zid)=0;
    string nick;

    if (cc->vurl.size())
    {
        string val=cc->vurl[0];
        v=splitTOK(".",val);
        cc->vurl.pop_front();
        if (v.size()==2)
        {
            CONTAINER(zid)=atoi(v[0]);
            id=atoi(v[1]);

            if (CONTAINER(zid)){
                PGLR(nick_vec,u,nick_vecs.find_by_id_create(CONTAINER(zid)));
                map<unsigned int,user_nick>::const_iterator it=u->u_nicks.find(id);

                if (it!=u->u_nicks.end())
                {
                    nick=it->second.name;
                }
                else if (u->u_nicks.size())
                    nick=u->u_nicks.begin()->second.name;
            }
        }
        else
        {
            zid=get_uid_by_nick(val);
            nick=val;

        }
    }
    m["~admin~"]="<!--";
    m["~eadmin~"]="-->";

    if (CONTAINER(zid)==0){
        string ss;
        ss<<"<tr><td>"<<_MSG("usernotfound2")<<"</td></tr>";
        m["~userinfo~"]=ss;
        cc->html_out+=cc->rvfiles(m,"a_user_info");
        return;
    }
    if (admin){
        m["~admin~"]="";
        m["~eadmin~"]="";
    }

    m["~nick~"]=nick;
    m["~id~"]=itostring(CONTAINER(zid));
    string out_www,out_irc;

    DB_id cc_user_id;CONTAINER(cc_user_id)=0;
    if (__UU)
        cc_user_id=user$id(__UU);
    make_user_info(zid,cc_user_id,admin,"","", CONTAINER(cc_user_id)!=0,out_www,out_irc);
    m["~userinfo~"]=out_www;
    cc->html_out+=cc->rvfiles(m,"a_user_info");
}



