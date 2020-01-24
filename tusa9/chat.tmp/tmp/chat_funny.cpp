#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include "mutex_inspector.h"
#include <time.h>
#include <errno.h>
#include <map>
#include "mysql_extens.h"
#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "_mutex.h"
#include <stdio.h>
#include "app_con.h"
#include "errs.h"
#include "file_set.h"
#include "chat_funny.h"
#include "copy_file.h"
#include "server_config.h"

#include "chat_config.h"
#include "app_def.h"

#include "web_tools.h"
static _mutex fMutex("static fMutex");
static	vector<c_neu>  news;
string _MSG(const string &n);


void url_admin_news(const PTR_getter<chat_user>  &__UU,app_connection *cc)
{
    MUTEX_INSPECTOR;
    if (!__UU){ cc->html_out=cc->redirect();return;}
    user_pair __U(__UU);
    if (!user__privileges(__U,"$news")) return;
    map<string,string> m;
    m["~msg~"]="";
    if (cc->params["cmd"]=="add"){
        string uid;
//        unsigned int nid=atoi(cc->params["nick"]);


//        user_nick	nick=GET_NICK(user$id(__U),nid);
        st_dbh d;
        //string id;
        d.dbh->real_queryQ((QUERY)"insert into news (txt,add_date,add_by) values ('?',NOW(),'?')"<<cc->params["add"]<<GET_CNICK(__U));
//        uid=d.dbh->select_1("select LAST_INSERT_ID() from news");
//        id=uid;
//        d.dbh->real_queryQ((QUERY)"update news set uid=? where id=?"<<uid<<id);
        load_news();
        m["~msg~"]=_MSG("added");
    }
    if (cc->params["remove"].size()){
        st_dbh d;
        d.dbh->real_queryQ((QUERY)"delete from news where id='?'"<<cc->params["remove"]);
        m["~msg~"]=_MSG("newsremoved");
        load_news();
    }
    if (cc->params["id"].size()){
        st_dbh d;
        vector< vector<string> > v=d.dbh->execQ((QUERY)"select txt,UNIX_TIMESTAMP(add_date),add_by from news where id='?'"<<cc->params["id"]);
        string h;

        for (unsigned int i=0;i<v.size();i++){
            if (v[i].size()!=3) throw cError("select failed."+_DMI());
            h+=": ";h+=v[i][0];h+=" (<b>";h+=date2num(atoi(v[i][1]));h+="</b>)<br><br>";
            m["~nick~"]=v[i][2];
        }
        m["~new~"]=h;
        cc->html_out=cc->rvfiles(m,"admin/news/new");
        return;
    }
    st_dbh d;
    vector< vector<string> > v=d.dbh->execQ((QUERY)"select id,txt,UNIX_TIMESTAMP(add_date) from news  order by add_date desc");
    string out;
    for (unsigned int i=0;i<v.size();i++){
        if (v[i].size()!=3) throw cError("select failed."+_DMI());
        map<string,string> q;
        q["~id~"]=v[i][0];
        string h=v[i][1];
        if (!user__privileges(__U,"$tags")) h=remove_tags(h);
//        if(h.size()>70) h=h.substr(0,70)+"...";
        q["~new~"]=h;
        q["~date~"]=date2num(atoi(v[i][2]));
        out+=cc->rvfiles(q,"admin/news/news_row");
    }
    m["~news~"]=out;
    out="";
    {
        map<string,string> q;
        q["~flang~"]="";
        q["~lang~"]="";
        out+=cc->rvfiles(q,"admin/news/news_add");
    }
    m["~addnews~"]=out;



//    m["~nicks~"]=build_nicks_select(user$id(__U),"nick",GET_CNICK_ID(__U),"");

    cc->html_out=cc->rvfiles(m,"admin/news/news");
}




bool load_news()
{
    MUTEX_INSPECTOR;
    M_LOCK(fMutex);
    news.clear();
    try{
        vector< vector<string> > v;
        {
            st_dbh d;
            v=d.dbh->execQ((QUERY)"select id,txt,add_by,UNIX_TIMESTAMP(add_date) from news order by add_date desc");
        }
        for (unsigned j=0;j<v.size();j++){
            if (v[j].size()!=4) throw cError("select failed"+_DMI());
            c_neu n;
            n.id=atoi(v[j][0]);
            n.txt=v[j][1];
            n.add_by=v[j][2];//GET_CNICK_DBID(uid);
            n.add_date=atoi(v[j][3]);
            news.push_back(n);
        }
    }catch (cError e){
        logErr2("--Error: load_news error: %s",e.error_string.c_str());
        return false;
    }
    return true;
}



unsigned int NEWS_SIZE()
{
    M_LOCK(fMutex);
    return news.size();
}

vector<c_neu> NEWS()
{
    M_LOCK(fMutex);
    return news;
}














vector < c_neu >  NEWS_GET_N(int cnt)
{

    vector < c_neu > v;
    unsigned k=0;
    M_LOCK(fMutex);
    vector<c_neu> &vv=news;
    for (unsigned i=0;i<vv.size()&&k<cnt;i++,k++)
    {
        v.push_back(vv[i]);
    }
    return v;

}
void url_news(app_connection *cc)
{
    MUTEX_INSPECTOR;
    map<string,string> m;
    unsigned int l=atoi(cc->params["l"]);
    unsigned int npp=chat_config.news_per_page;
    vector<c_neu> n=NEWS();
    if (l>=n.size()) l=0;
    unsigned int en=l+npp-1;
    if (en>=n.size()) en=n.size()-1;
    string out;
    for (unsigned int i=l;i<=en;i++){
        if (i<n.size())
        {
            map<string,string> q;
            q["~date~"]=date2num(n[i].add_date);
            q["~text~"]=n[i].txt;
//            q["~nid~"]=itostring(n[i].nid);
            q["~nick~"]=n[i].add_by;
            out+=cc->rvfiles(q,"news_row");
        }
        else break;
    }
    m["~news~"]=out;
    l+=npp;
    if (l>=n.size()){
        m["~next~"]="";
    }else{
        m["~next~"]="<a href=\"?l="+itostring(l)+"\">"+_MSG("nextnews")+"</a>";
    }
    cc->html_out=cc->rvfiles(m,"news");
}

string get_news_for_index(app_connection * cc)
{
    int cn = 0;
    int cnt = chat_config.news_count_in_index_page;
    vector < c_neu > n = NEWS_GET_N(cnt);
    string news;
    {
        for (unsigned int i = 0; i < n.size(); i++) {

            map<string , string > q;
            q["~date~"] = date2num(n[i].add_date);
            q["~text~"] = n[i].txt;
            q["~nick~"] = n[i].add_by;
//            q["~nid~"] = itostring(n[i].nid);
            news += cc->rvfiles(q, "index_news_row");
            cn++;
            if (cn >= cnt)
                break;
        }
    }
    return news;
}
s_text_funny::s_text_funny(){}
funny_pic::funny_pic(){}
c_neu::c_neu(){}
