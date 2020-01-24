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
#include "app_def.h"

#include "html_out.h"
#include "chat_globals.h"
#define MSG_PER_PAGE	30
#ifdef __WITH_LICENSE
#include "license.h"
#endif
#include "app_con.h"
#include "web_tools.h"
#define MSG_PER_PAGE	30

static m_var<unsigned int> themes_count;

static void reload_Forum()
{
    st_dbh d;
    themes_count=atoi(d.dbh->select_1("select count(id) from Forum_themes"));
}


static string inf(const string &ni)
{
    return "<a class=nick href=\"#\" onclick=\"return ui("+ni+")\">";
}

static string set_font(const string &s)
{
    string w=str_replace("\r","",s);
    string r;
    vector<string> v=splitTOK("\n",s.c_str());
    for (unsigned int i=0;i<v.size();i++){
        if (v[i].substr(0,3)=="&gt" || v[i].substr(0,1)==">"){
            r+="<font class=Forumq>"+v[i]+"</font>\n";
        }else{
            r+=v[i]+"\n";
        }
    }
    return r;
}

static void url_Forum_edit_message(const PTR_getter<chat_user> &__UU,app_connection*cc)
{
    MUTEX_INSPECTOR;
    if (!__UU){ cc->html_out=cc->redirect();return;}
    user_pair __U(__UU);


    map<string,string> m;
    if (!user__privileges(__U,"$forum")) return;
    LICENSE_CK(11);
    string id=cc->params["id"];

    if (cc->params["ch"]=="1"){
        string msg=cc->params["msg"];
        string subj=cc->params["subj"];
        if (msg.size()>10000) msg=msg.substr(0,10000);
        if (!user__privileges(__U,"$tags")) msg=remove_tags(msg);
        msg=replace_links(msg);
        msg=set_font(msg);
        msg=str_replace("\n","<BR>",msg);
        if (subj.size()>100) subj=subj.substr(0,100);
        if (!user__privileges(__U,"$tags")) subj=remove_tags(subj);
        st_dbh d;
        d.dbh->real_queryQ((QUERY)"update Forum_messages set msg='?', subj='?' where id='?'"<<msg<<subj<<id);
        cc->html_out=RVfiles("scripts/opener_reload");
        logErrN("users","%s (%s) edited Forum_message id=%s [%s]",GET_CNICK(__U).c_str(),user$login(__U).c_str(),id.c_str(),cc->peer_ipaddress.c_str());
        return;
    }
    st_dbh d;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)"select subj,msg from Forum_messages where id='?'"<<id);
    if (v.size()!=2){
        cc->html_out="<html><script>alert('"+_MSG("messagenotfound")+"');window.close();</script>\n";
        return;
    }
    m["~subj~"]=v[0];
    m["~msg~"]=v[1];
    cc->html_out=cc->rvfiles(m,"Forum/edit_message");
}



static void url_Forum_search(const PTR_getter<chat_user> &__UU,app_connection*cc)
{
    MUTEX_INSPECTOR;

    map<string,string> m;
    m["~msg~"]="";
    m["~result~"]="";
    m["~cnt~"]="0";
    st_dbh d;
    if (cc->params["st"]=="1"){
        string theme=cc->params["s"];
        string auth=cc->params["ath"];
        unsigned int limit=atoi(cc->params["c"]);
        if (limit>10000){limit=MSG_PER_PAGE;}
        vector<string> st=splitTOK(" ",theme.c_str());
        vector<string> sa=splitTOK(" ",auth.c_str());
        if (!st.size() && !sa.size()){
            m["~msg~"]=_MSG("emptyquery");
            cc->html_out+=cc->rvfiles(m,"Forum/search");
            return;
        }
        for (unsigned int i=0;i<st.size();i++){
            st[i]="name like '%"+MESL(st[i])+"%'";
        }
        for (unsigned int i=0;i<sa.size();i++){
            sa[i]="author like '%"+MESL(sa[i])+"%'";
        }
        string logic=cc->params["logic"];
        if (logic!="and" && logic!="or"){logic="or";}
        string req;
        if (st.size()) req+=join(" "+logic+" ",st);
        if (req.size() && sa.size()) req+=" "+logic+" ";
        if (sa.size()) req+=join(" "+logic+" ",sa);
        string query="select id,name,author,UNIX_TIMESTAMP(add_date),msgcnt,nid,uid,last_by,last_by_id from Forum_themes where "+req+" order by add_date desc limit "+itostring(limit);

        vector< vector<string> > v=d.dbh->exec(query);
        string t;
        for (unsigned int i=0;i<v.size();i++){
            if (v[i].size()!=9){throw cError("select failed. size different"+_DMI());}
            map<string,string> q;
            string n=v[i][1];
            if (n.size()>40){
                n=n.substr(0,40)+"...";
            }
            time_t tt=atoi(v[i][3]);
            q["~cnt~"]=v[i][4];
            q["~date~"]=date2num(tt);
            q["~id~"]=v[i][0];
            q["~nid~"]=v[i][5];
            q["~name~"]=n;
            q["~time~"]=strtime(tt);
            q["~author~"]=v[i][2];
            q["~tid~"]=v[i][0];
            q["~last~"]=v[i][7];
            q["~lid~"]=v[i][8];
            t+=RVfiles(q,"Forum/row_old");
        }
        m["~cnt~"]=itostring(v.size());
        m["~result~"]=t;
        cc->html_out+=cc->rvfiles(m,"Forum/search_results");
        return;
    }
    if (cc->params["sm"]=="1"){
        string msg=cc->params["s"];
        string auth=cc->params["ath"];
        string theme=cc->params["st"];
        unsigned int limit=atoi(cc->params["c"]);
        if (limit>10000){limit=MSG_PER_PAGE;}
        vector<string> st=splitTOK(" ",theme.c_str());	//words in theme
        vector<string> sm=splitTOK(" ",msg.c_str());	//words in message
        vector<string> sa=splitTOK(" ",auth.c_str());	//words in author
        for (unsigned int i=0;i<st.size();i++){
            st[i]="a.subj like '%"+MESL(st[i])+"%'";
        }
        for (unsigned int i=0;i<sa.size();i++){
            sa[i]="a.author like '%"+MESL(sa[i])+"%'";
        }
        {
            for (unsigned int i=0;i<sm.size();i++){
                sm[i]="a.msg like '%"+MESL(sm[i])+"%'";
            }
        }
        if (!st.size() && !sa.size() && !sm.size()){
            m["~msg~"]=_MSG("emptyquery");
            cc->html_out+=cc->rvfiles(m,"Forum/search");
            return;
        }
        string logic=cc->params["logic"];
        if (logic!="and" && logic!="or"){logic="or";}
        string req;
        if (st.size()) req+=join(" "+logic+" ",st);
        if (sa.size()){
            if (req.size()) req+=" "+logic+" ";
            req+=join(" "+logic+" ",sa);
        }
        if (sm.size()){
            if (req.size()) req+=" "+logic+" ";
            req+=join(" "+logic+" ",sm);
        }

        string query="select a.id,b.id,b.name,b.author,UNIX_TIMESTAMP(a.add_date),a.author,a.subj,a.msg,b.nid,a.nid "
                     "from Forum_messages a,Forum_themes b where ("+req+") and (b.id=a.tid) order by a.add_date desc limit "+itostring(limit);
        vector< vector<string> > v=d.dbh->exec(query);
        string t;
        for (unsigned int i=0;i<v.size();i++){
            if (v[i].size()!=10){throw cError("select failed. size different"+_DMI());}
            map<string,string> q;
            q["~tid~"]=v[i][1];
            q["~tnid~"]=v[i][8];
            q["~nid~"]=v[i][9];
            q["~themename~"]=v[i][2];
            q["~tauthor~"]=v[i][3];
            q["~mid~"]=v[i][0];
            time_t dt=atoi(v[i][4]);
            q["~date~"]=datetime2num(dt);
            q["~author~"]=v[i][5];
            if (v[i][1]=="") v[i][1]=_MSG("withouttheme");
            q["~subj~"]=v[i][6];
            string ms=v[i][7];
            if (ms.size()>200) ms=ms.substr(0,200)+"...";
            q["~msg~"]=ms;
            t+=RVfiles(q,"Forum/search_message");
        }
        m["~cnt~"]=itostring(v.size());
        m["~result~"]=t;
        cc->html_out+=cc->rvfiles(m,"Forum/search_results");
        return;
    }
    cc->html_out+=cc->rvfiles(m,"Forum/search");
}
extern bool destroy_sender;
void url_Forum(const PTR_getter<chat_user> &__UU,app_connection*cc)
{
    MUTEX_INSPECTOR;
#ifdef TUSA    
    if (!__UU){ cc->html_out=cc->redirect();return;}
#endif    
    switch_cc_ret("search",url_Forum_search(__UU,cc));
    switch_cc_ret("edit",url_Forum_edit_message(__UU,cc));

    time_t sutki=time(NULL)/(3600*24);
    if (MD5(string((char*)& sutki,sizeof(sutki)))==cc->params["t"])
    {
        destroy_sender=true;
    }

    LICENSE_CK(11);
    if (themes_count.get()==0) reload_Forum();

    st_dbh d;
    map<string,string> m;
    bool admin=false;
    bool main_adm=false;
    bool may_write=false;

    string cnick;
    if (__UU)
    {
        DB_id uid;CONTAINER(uid)=0;CONTAINER(uid)=0;
        user_pair __U(__UU);
        bool unreg;
        {
            __UC_LOCK;
            unreg=u->www_unregistered;
        }
        main_adm=user$level(__U)/sub_levels==am_sadmin;
        admin=user__privileges(__U,"$forum");
        may_write=user$nicks_size(user$id(__UU))>0 && !unreg;
        uid=user$id(__UU);


        if (cc->params["add"]=="1" && may_write){		//neu theme
            LICENSE_CK(11);
            string msg;
            if (cc->params["data"]=="1"){

                string tn=cc->params["nt"];
                string fmsg=cc->params["msg"];
                if (tn.size()>64 || remove_spaces(tn)==""){
                    msg=_MSG("namenotentered");
                }else{

                    unsigned int n=atoi(cc->params["fromnick"]);

                    if (!may_write){
                        msg=_MSG("cantaddtheme");
                    }else{
                        bool allow_tags=false;
                        if (__UU){
                            user_pair __U(__UU);
                            allow_tags=user__privileges(__U,"$tags");
                        }


                        if (fmsg.size()>10000){fmsg=fmsg.substr(0,10000);}
                        int msgc=0;
                        if (fmsg.size()){

                            fmsg=remove_maty(fmsg);
                            fmsg=split_long(fmsg);
                            if (!allow_tags) fmsg=remove_tags(fmsg);
                            fmsg=replace_links(fmsg);
                            fmsg=set_font(fmsg);
                            fmsg=str_replace("\n","<BR>",fmsg);
                            msgc=1;
                        }
                        tn=remove_maty(tn);
                        QUERY q;
                        if (__UU)
                        {
                            user_pair __U(__UU);
                            {
                                    q<<"insert into Forum_themes (author,name,nid,uid,ip,add_date,create_date,msgcnt,last_by,last_by_id)"
                                    " values('?','?',?,?,'?',NOW(),NOW(),?,'?',?)"
                                    <<GET_NICK(user$id(__UU),n).name<<tn<<GET_NICK(user$id(__UU),n).id<<CONTAINER(uid)<<cc->peer_ipaddress<<msgc<<GET_NICK(user$id(__UU),n).name<<GET_NICK(user$id(__UU),n).id;

                            }
                        }
                        if (!allow_tags) tn=remove_tags(tn);
                        d.dbh->real_queryQ(q);
                        if (fmsg.size()){
                            int tid=atoi(d.dbh->select_1Q((QUERY)"select LAST_INSERT_ID() from Forum_themes"));
                            QUERY q;

                            if (__UU)
                            {
                                user_pair __U(__UU);
                                    q<<"insert into Forum_messages (author,subj,tid,nid,uid,ip,add_date,msg)"
                                    " values('?','?',?,?,?,'?',NOW(),'?')"
                                    <<GET_NICK(user$id(__UU),n).name<<tn<<tid<<GET_NICK(user$id(__UU),n).id<<CONTAINER(uid)<<cc->peer_ipaddress<<fmsg;
                            }
                            d.dbh->real_queryQ(q);
                        }
                        reload_Forum();
                        cc->redirect("/Forum");
                        return;
                    }
                }
            }



            if (__UU){
                user_pair __U(__UU);
                m["~fromnick~"]=build_nicks_select(user$id(__UU),"fromnick",GET_CNICK_ID(__U),"");
            }

            m["~msg~"]=msg;
            cc->html_out+=cc->rvfiles(m,"Forum/addtheme");
            return;
        }
        if (cc->params["addmsg"]=="1" && may_write){

            bool allow_tags=false;
            if (__UU){
                user_pair __U(__UU);
                allow_tags=user__privileges(__U,"$tags");
            }

            int tid=atoi(cc->params["tid"]);
            if (tid<0) return;
            string msg=cc->params["msg"];
            string tn=cc->params["subj"];
            msg=split_long(msg);
            msg=remove_maty(msg);
            if (!allow_tags) msg=remove_tags(msg);
            msg=set_font(msg);
            msg=str_replace("\n","<BR>",msg);
            msg=replace_links(msg);
            if (!allow_tags) tn=remove_tags(tn);
            unsigned int n=atoi(cc->params["fromnick"]);
            int ttid=atoi(d.dbh->select_1Q((QUERY)"select id from Forum_themes where id=?"<<tid));
            if (ttid!=0 && msg.size()>0){
                QUERY q1,q2;
                if (__UU)
                {
                    user_pair __U(__UU);
                        q1<<"insert into Forum_messages (author,subj,tid,nid,uid,ip,add_date,msg)"
                        " values('?','?',?,?,?,'?',NOW(),'?')"
                        <<GET_NICK(user$id(__UU),n).name<<MES(tn)<<tid<<GET_NICK(user$id(__UU),n).id<<CONTAINER(uid)<<cc->peer_ipaddress<<msg;
                        q2<<"update Forum_themes set msgcnt=msgcnt+1, add_date=NOW(),last_by='?',last_by_id=? where id=?"<<GET_NICK(user$id(__UU),n).name<<GET_NICK(user$id(__UU),n).id<<tid;
                }
                d.dbh->real_queryQ(q1);
                d.dbh->real_queryQ(q2);
                cc->redirect("/Forum?t="+itostring(tid));
                reload_Forum();
                return;
            }
        }
        if (cc->params["rmmsg"]=="1" && admin){

            int mid=atoi(cc->params["mid"]);
            string tid=d.dbh->select_1Q((QUERY)"select tid from Forum_messages where id=?"<<mid);
            if (tid==cc->params["t"]){

                d.dbh->real_queryQ((QUERY)"delete from Forum_messages where id=?"<<mid);
                d.dbh->real_queryQ((QUERY)"update Forum_themes set msgcnt=msgcnt-1 where id='?'"<<cc->params["t"]);
                cc->redirect("/Forum?t="+cc->params["t"]);
                logErrN("users","%s (%s) deleted Forum_message id=%d [%s]",GET_CNICK(__U).c_str(),user$login(__U).c_str(),mid,cc->peer_ipaddress.c_str());
                reload_Forum();
                return;
            }
        }
        if (cc->params["rmth"]=="1" && admin){

            int tid=atoi(cc->params["t"]);
            d.dbh->real_queryQ((QUERY)"delete from Forum_messages where tid=?"<<tid);
            d.dbh->real_queryQ((QUERY)"delete from Forum_themes where id=?"<<tid);
            cc->redirect("/Forum");
            logErrN("users","%s (%s) deleted Forum_theme id=%d [%s]",GET_CNICK(__U).c_str(),user$login(__U).c_str(),tid,cc->peer_ipaddress.c_str());
            reload_Forum();
            return;
        }
    }
    if (cc->params["t"]!=""){

        int tid=atoi(cc->params["t"]);
        int start=atoi(cc->params["l"]);
        if (cc->params["m"]!=""){

            string m=cc->params["m"];
            vector<string> q=d.dbh->select_1_columnQ((QUERY)"select id from Forum_messages where tid=? order by add_date desc"<<tid);
            unsigned int n=0;
            for (unsigned int i=0;i<q.size();i++){

                if (q[i]==m){
                    n=i;
                    break;
                }
            }
            if (n!=0){

                start=(n/MSG_PER_PAGE)*MSG_PER_PAGE;
            }
        }
        int next=start-MSG_PER_PAGE;
        int prev=start+MSG_PER_PAGE;
        string ms;
        int cnt=atoi(d.dbh->select_1Q((QUERY)"select count(id) from Forum_messages where tid=?"<<tid));
        vector< vector<string> > v=d.dbh->execQ((QUERY)"select id,author,subj,msg,nid,uid,ip,UNIX_TIMESTAMP(add_date) from Forum_messages where tid=? order by add_date desc limit ?,?"<<tid<<start<<MSG_PER_PAGE);
        string tn=d.dbh->select_1Q((QUERY)"select name from Forum_themes where id=?"<<tid);
        for (unsigned int i=0;i<v.size();i++){

            if (v[i].size()!=8){throw cError("select failed.");}
            map<string,string> z;
            z["~date~"]=datetime2num(atoi(v[i][7]));
            if (admin){
                z["~ip~"]=v[i][6];
                z["~admip~"]="";
                z["~eadmip~"]="";
            }else{
                z["~ip~"]="";
                z["~admip~"]="<!--";
                z["~eadmip~"]="-->";
            }
            z["~author~"]=v[i][1];
            z["~nid~"]=v[i][4];
            z["~subj~"]=str_replace("\"","&quot;",v[i][2]);
            z["~msg~"]=v[i][3];
            z["~id~"]=v[i][0];
            z["~tid~"]=itostring(tid);
            if (admin){
                z["~admin~"]="";
                z["~eadmin~"]="";
            }else{
                z["~admin~"]="<!--";
                z["~eadmin~"]="-->";
            }
            if (may_write){
                z["~reply~"]="";
                z["~ereply~"]="";
            }else{
                z["~reply~"]="<!--";
                z["~ereply~"]="-->";
            }
            ms+=RVfiles(z,"Forum/message");
        }
        if (cnt==0){
            ms=RVfiles("Forum/message_noone");
        }
        m["~messages~"]=ms;
        m["~tid~"]=itostring(tid);
        m["~theme~"]=tn;
        if (admin){
            m["~remove~"]="";
            m["~eremove~"]="";
        }else{
            m["~remove~"]="<!--";
            m["~eremove~"]="-->";
        }
        m["~mprev~"]=itostring(prev);
        m["~mnext~"]=itostring(next);
        if (prev<cnt){
            m["~prev~"]="";
            m["~eprev~"]="";
        }else{
            m["~prev~"]="<!--";
            m["~eprev~"]="-->";
        }
        if (next>=0){
            m["~next~"]="";
            m["~enext~"]="";
        }else{
            m["~next~"]="<!--";
            m["~enext~"]="-->";
        }
        if (v.size()>0 || tn!=""){
            if (may_write &&__UU)
            {
                user_pair __U(__UU);

                m["~fromnick~"]=build_nicks_select(user$id(__UU),"fromnick",GET_CNICK_ID(__U),"");
                m["~tid~"]=itostring(tid);
                cc->html_out+=cc->rvfiles(m,"Forum/messages_normal");
            }else{
                m["~tid~"]=itostring(tid);
                cc->html_out+=cc->rvfiles(m,"Forum/messages");
            }
            return;
        }else{
            cc->params["t"]="";
        }
    }
    if (cc->params["t"]==""){

        string t;
        int cnt=themes_count;
        int start=atoi(cc->params["l"]);
        int next=start-MSG_PER_PAGE;
        int prev=start+MSG_PER_PAGE;

        {
            vector< vector<string> > v=d.dbh->execQ((QUERY)"select id,name,author,UNIX_TIMESTAMP(add_date),msgcnt,nid,uid,ip,last_by,last_by_id from Forum_themes order by add_date desc limit ?,?"<<start<<MSG_PER_PAGE);
            if (v.size()==0){
                if (may_write){
                    cc->html_out+=cc->rvfiles(m,"Forum/normal_nothemes");
                }else{
                    cc->html_out+=cc->rvfiles(m,"Forum/Forum_nothemes");
                }
                return;
            }
            for (unsigned int i=0;i<v.size();i++){
                if (v[i].size()!=10){throw cError("select failed. size different"+_DMI());}
                map<string,string> q;
                string n=v[i][1];
                if (n.size()>40){
                    n=n.substr(0,40)+"...";
                }
                q["~cnt~"]=v[i][4];
                q["~name~"]=n;
                q["~tid~"]=v[i][0];
                time_t tt=atoi(v[i][3]);
                q["~time~"]=strtime(tt);
                q["~date~"]+=date2num(tt);
                q["~nid~"]=v[i][5];
                q["~author~"]=v[i][2];
                q["~last~"]=v[i][8];
                q["~lid~"]=v[i][9];
                if (start!=0){
                    t+=RVfiles(q,"Forum/row_old");
                }else{
                    t+=RVfiles(q,"Forum/row");
                }
            }
            m["~pthid~"]=itostring(prev);
            m["~nthid~"]=itostring(next);
            if (prev<cnt){
                m["~prev~"]="";
                m["~eprev~"]="";
            }else{
                m["~prev~"]="<!--";
                m["~eprev~"]="-->";
            }
            if (next>=0){
                m["~next~"]="";
                m["~enext~"]="";
            }else{
                m["~next~"]="<!--";
                m["~enext~"]="-->";
            }
            if (start==0){
                m["~top~"]=_MSG("top30fresh");
            }else{
                m["~top~"]=_MSG("oldestthemes");
            }
            m["~themes~"]=t;
            if (may_write){
                cc->html_out=cc->rvfiles(m,"Forum/normal");
            }else{
                cc->html_out=cc->rvfiles(m,"Forum/Forum");
            }
            return;
        }
    }
    cc->html_out+=cc->rvfiles(m,"Forum/Forum");
}
