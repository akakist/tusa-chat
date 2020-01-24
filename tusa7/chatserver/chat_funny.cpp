#ifdef __GNUC__
#pragma implementation
#endif

#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <errno.h>
#include <map>
#ifndef __CLAN
#include "mysql_extens.h"
#endif
#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "_mutex.h"
#include <stdio.h>
#include "errs.h"
#include "file_set.h"
#include "chat_funny.h"
#include "copy_file.h"
#include "server_config.h"

#include "chat_config.h"
#include "chat_def.h"
#include "web_tools.h"
#include "cs_conn_data.h"
#include "html_out.h"
#include "chat_globals.h"
#include "DR_types.h"
static _mutex fMutex("static fMutex");
#ifndef __CLAN
static	vector<funny_pic> funnypics;
static	vector<s_text_funny> anekdots;
static	vector<s_text_funny> histories;
#endif

static	vector<string> hints;
static	vector<c_neu>  news;

#ifndef __CLAN
bool load_funnypics()
{
    M_LOCK(fMutex);
    funnypics.clear();
    try {
        vector< vector<string> > v;
        {
            st_dbh d;
            v=d.dbh->exec("select id,name,descr from funnypics order by id");
        }
        for (unsigned int i=0;i<v.size();i++) {
            funny_pic f;
            if (v[i].size()!=3) {
                throw cError("load_funnypics: size different");
            }
            f.id=atoi(v[i][0].c_str());
            f.name=v[i][1];
            f.descr=v[i][2];
            funnypics.push_back(f);
        }
    } catch (cError e) {
        logErr2("--Error: load_funnypics: %s",e.error_string.c_str());
        return false;
    }
    return true;
}
#endif

#ifndef __CLAN
bool load_histories()
{
    M_LOCK(fMutex);
    histories.clear();
    try {
        vector< vector<string> > v;
        {
            st_dbh d;
            v=d.dbh->exec("select id,txt,add_by from histories where chk=1 order by id");
        }
        for (unsigned int i=0;i<v.size();i++) {
            s_text_funny f;
            if (v[i].size()!=3) {
                throw cError("load_histories: size different");
            }
            f.id=atoi(v[i][0].c_str());
            f.text=v[i][1];
            f.add_by=v[i][2];
            histories.push_back(f);
        }
    } catch (cError e) {
        logErr2("--Error: load_histories: %s",e.error_string.c_str());
        return false;
    }
    return true;
}
#endif

#ifndef __CLAN
bool load_anekdots()
{
    M_LOCK(fMutex);
    anekdots.clear();
    try {
        vector< vector<string> > v;
        {
            st_dbh d;
            v=d.dbh->exec("select id,txt,add_by from anekdots where chk=1 order by id");
        }
        for (unsigned int i=0;i<v.size();i++) {
            s_text_funny f;
            if (v[i].size()!=3) {
                throw cError("load_anekdots: size different");
            }
            f.id=atoi(v[i][0].c_str());
            f.text=v[i][1];
            f.add_by=v[i][2];
            anekdots.push_back(f);
        }
    } catch (cError e) {
        logErr2("--Error: load_anekdots: %s",e.error_string.c_str());
        return false;
    }
    return true;
}
#endif

#ifndef __CLAN
funny_pic FUNNYPICS(unsigned int n)
{
    M_LOCK(fMutex);
    if (n >= funnypics.size() || n < 0) {
        throw cError("n>funnypics.size()");
    }
    return funnypics[n];
}
unsigned int FUNNYPICS_SIZE()
{
    M_LOCK(fMutex);
    return funnypics.size();
}

s_text_funny ANEKDOTS(unsigned int n)
{
    M_LOCK(fMutex);
    if (n >= anekdots.size() || n < 0) {
        throw cError("n>anekdots.size()");
    }
    return anekdots[n];
}

unsigned int ANEKDOTS_SIZE()
{
    M_LOCK(fMutex);
    return anekdots.size();
}

s_text_funny HISTORIES(unsigned int n)
{
    M_LOCK(fMutex);
    if (n >= histories.size() || n < 0) {
        throw cError("n>histories.size()");
    }
    return histories[n];
}

unsigned int HISTORIES_SIZE()
{
    M_LOCK(fMutex);
    return histories.size();
}
#endif
#ifdef __CLAN
bool load_hints()
{

    string cr=clan_data_request(DR_load_hints);
    oscar_buffer b(cr.data(),cr.size());

    M_LOCK(fMutex);
    b>>hints;
    return true;
}
#else
bool load_hints()
{
    hints.clear();
    try {
        vector<string> v;
        {
            st_dbh d;
            v=d.dbh->select_1_columnQ((QUERY)"select txt from hints");
        }
        hints=v;

    } catch (cError e) {
        logErr2("--Error: load_hints error: %s",e.error_string.c_str());
        return false;
    }
    return true;
}
#endif
void pack_hints(out_oscar_buffer &b)
{
    M_LOCK(fMutex);
    b<<hints;
}
void unpack_hints(oscar_buffer &b)
{
    M_LOCK(fMutex);
    b>>hints;
}
string HINTS()
{
    M_LOCK(fMutex);
    if (hints.size()==0) return "";
    int sz=hints.size();
    unsigned int n=0;
    if (sz)
        n=rand()%sz;
    if (n>=hints.size()) {
        throw cError("n>hints.size()");
    }
    return hints[n];
}
//#endif

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
#ifndef __CLAN
void url_anek_adm(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);
    if (!(user$privileges(__U)&u_is_funny_admin)) return;
    map<string,hstring> m;
    string cmd=cc->params["cmd"];
    int pn=atoi(cc->params["pn"].c_str());
    if (cmd=="add") {
        {
            st_dbh d;
            d.dbh->real_queryQ((QUERY)"update anekdots set chk=1 where id='?'"<<cc->params["id"]);
        }
        load_anekdots();
    }
    if (cmd=="remove") {
        {
            st_dbh d;
            d.dbh->real_queryQ((QUERY)"delete from anekdots where id='?'"<<cc->params["id"]);
        }
        load_anekdots();
    }
    if (pn<0) pn=0;
    vector<string> ids;
    {
        st_dbh d;
        ids=d.dbh->select_1_column("select id from anekdots order by id desc");
    }
    if (ids.size()<=0) {
        map<string,hstring> K;
        cc->html_out=make_pair(K,"admin/anekdots/index_empty");
        return;
    }
    int mx=ids.size()-1;
    if (pn>mx) pn=mx;
    int prev=pn-1;
    int next=pn+1;
    if (next>mx || next<0) next=0;
    if (prev<0 || prev>mx) prev=mx;
    vector<string> v;
    {
        st_dbh d;
        v=d.dbh->select_1_rowQ((QUERY)"select txt,add_by,UNIX_TIMESTAMP(add_date),chk from anekdots where id=?"<<ids[pn]);
    }
    if (v.size()!=4) {
        throw cError("select() failed. Size is different.");
    }
    string txt=v[0];
    txt=str_replace("\r\n","<br>",txt);
    m["~pn~"]=itostring(pn);
    m["~prev~"]=itostring(prev);
    m["~next~"]=itostring(next);
    m["~text~"]=txt;
    m["~addby~"]=v[1];
    m["~adddate~"]=datetime2rus(atoi(v[2].c_str()));
    m["~cnt~"]=itostring(mx+1);
    m["~id~"]=ids[pn];
    m["~stat~"]=_MSG("checked");
    if (v[3]=="0") {
        string s;
        s<<"<b>"<<_MSG("notchecked")<<"</b>";
        m["~stat~"]=s;
    }
    string a;
    if (v[3]=="0") {
        string s;
        s<<"<input type=button value='"<<_MSG("allow")<<"' onclick=\"fupdate('add')\">&nbsp;";
        a=s;
    }
    string ss;
    ss<<"<input type=button value='"<<_MSG("remove")<<"' onclick=\"fupdate('remove')\">";
    a+=ss;
    m["~adm~"]=a;
    cc->html_out=make_pair(m,"admin/anekdots/index");
}
void url_addfunny(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    if (cc->sub_level<=am_newuser) return;
    user_pair __U(__UU);
    string txt=cc->params["txt"];
    user_nick   nick=GET_NICK(__U,atoi(cc->params["nick"].c_str()));
    if (!(user$privileges(__U)&u_allow_tags)) txt=remove_tags(txt);

    int tp=atoi(cc->params["tp"].c_str());
    txt=remove_maty(txt);

    if (txt.size()>10000) txt=txt.substr(0,10000);

    if (tp==1) {
        st_dbh d;
        d.dbh->real_queryQ((QUERY)"insert into anekdots (txt,add_by,add_date,ip,chk) values ('?','?',now(),'?',0)"<<txt<<nick.name<<cc->peer_ipaddress);
    }
    if (tp==2) {
        st_dbh d;
        d.dbh->real_queryQ((QUERY)"insert into histories (txt,add_by,add_date,ip,chk) values ('?','?',now(),'?',0)"<<txt<<nick.name<<cc->peer_ipaddress);
    }
    map<string,hstring> K;
    cc->html_out=make_pair(K,"funny_added");
}

void url_funny_pics(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    map<string,hstring> m;
    bool rnd=true;
    int nn=0;
    if (FUNNYPICS_SIZE()==0) {
        map<string,hstring> K;
        cc->html_out=make_pair(K,"funny_pics_empty");
        return;
    }
    if (cc->params["n"]!="") {
        nn=atoi(cc->params["n"].c_str());
        rnd=false;
    }
    int mx=FUNNYPICS_SIZE()-1;
    if (rnd && mx>1) {
        nn=rand()%mx;
    }
    if (nn>mx || nn<0) {
        nn=0;
    }
    int n=nn+1;
    int p=nn-1;
    int r;
    if (mx>1) {
        r=rand()%mx;
    } else {
        r=0;
    }
    if (nn>mx) {
        nn=0;
    }
    if (p<0) {
        p=mx;
    }
    if (n>mx) {
        n=0;
    }
    funny_pic f=FUNNYPICS(nn);
    m["~pic~"]="<img src=\"/pics/funnypics/"+f.name+"\" border=0>";
    m["~next~"]="/FunnyPics?n="+itostring(n);
    m["~prev~"]="/FunnyPics?n="+itostring(p);
    m["~rnd~"]="/FunnyPics?n="+itostring(r);
    m["~descr~"]=f.descr;
    cc->html_out=make_pair(m,"funny_pics");
}

void url_histories(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    map<string,hstring> m;
    bool may_add=false;
    if (__UU) {
        cc->sub_level>am_newuser;
    }
    string nicks;
    if (may_add) {
        user_pair __U(__UU);
        nicks=build_nicks_select(__U,"nick",GET_CNICK_ID(__U),"");
    }
    if (may_add) {
        map<string,hstring> q;
        q["~nicks~"]=nicks;
        m["~addform~"]=make_pair(q,"funny_form");
    } else {
        m["~addform~"]="";
    }
    if (HISTORIES_SIZE()==0) {
        cc->html_out=make_pair(m,"histories_empty");
        return;
    }

    bool rnd=true;
    int nn=0;
    if (cc->params["n"]!="") {
        nn=atoi(cc->params["n"].c_str());
        rnd=false;
    }
    int mx=HISTORIES_SIZE()-1;
    if (rnd && mx>1) {
        nn=rand()%mx;
    }
    if (nn>mx || nn<0) nn=0;
    int n=nn+1;
    int p=nn-1;
    int r;
    if (mx>1) {
        r=rand()%mx;
    } else {
        r=0;
    }
    if (p<0) p=mx;
    if (n>mx) n=0;
    s_text_funny t=HISTORIES(nn);
    string hs=t.text;
    hs=str_replace("\r\n","<br>",hs);
    m["~hist~"]=hs;
    m["~next~"]="/Histories?n="+itostring(n);
    m["~prev~"]="/Histories?n="+itostring(p);
    m["~rnd~"]="/Histories?n="+itostring(r);
    m["~from~"]=t.add_by;
    cc->html_out=make_pair(m,"histories");
}

void url_anekdots(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    map<string,hstring> m;
    bool may_add=false;
    if (__UU)
    {
        may_add=cc->sub_level>am_newuser;
    }
    string nicks;
    if (may_add) {
        user_pair __U(__UU);
        nicks=build_nicks_select(__U,"nick",GET_CNICK_ID(__U),"");
    }
    if (may_add) {

        map<string,hstring> q;
        q["~nicks~"]=nicks;
        m["~addform~"]=make_pair(q,"funny_form");
    } else {
        m["~addform~"]="";
    }
    if (ANEKDOTS_SIZE()==0) {
        cc->html_out=make_pair(m,"anekdots_empty");
        return;
    }

    bool rnd=true;
    int nn=0;
    if (cc->params["n"]!="") {

        nn=atoi(cc->params["n"].c_str());
        rnd=false;
    }
    int mx=ANEKDOTS_SIZE()-1;
    if (rnd && mx>1) {
        nn=rand()%mx;
    }
    if (nn>mx || nn<0) nn=0;
    int n=nn+1;
    int p=nn-1;
    int r;
    if (mx>1) {
        r=rand()%mx;
    } else {
        r=0;
    }
    if (nn>mx) nn=0;
    if (p<0) p=mx;
    if (n>mx) n=0;
    s_text_funny t=ANEKDOTS(nn);
    string hs=t.text;
    hs=str_replace("\r\n","<br>",hs);
    m["~anek~"]=hs;
    m["~next~"]="/Anekdots?n="+itostring(n);
    m["~prev~"]="/Anekdots?n="+itostring(p);
    m["~rnd~"]="/Anekdots?n="+itostring(r);
//    m["~nusr~"]=cc->_nusr;
    m["~from~"]=t.add_by;
    cc->html_out=make_pair(m,"anekdots");
}

void url_pic_adm(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);

    if (!(user$privileges(__U)&u_is_funny_admin)) return;

    map<string,hstring> m;
    string cmd=cc->params["cmd"];

    m["~msg~"]="";
    int pn=atoi(cc->params["pn"].c_str());
    if (cmd=="change") {
        string d=cc->params["descr"];
        if (!(user$privileges(__U)&u_allow_tags)) d=remove_tags(d);
        d=remove_maty(d);
        {
            st_dbh db;
            db.dbh->real_queryQ((QUERY)"update funnypics set descr='?' where id='?'"<<d<<cc->params["id"]);
        }
        m["~msg~"]=_MSG("changed");
        load_funnypics();
    }
    if (cmd=="remove") {
        {
            st_dbh d;
            string n=d.dbh->select_1Q((QUERY)"select name from funnypics where id='?'"<<cc->params["id"]);
            string fn=(string)chat_config.funny_dir+split_char+n;
            unlink(fn.c_str());
            d.dbh->real_queryQ((QUERY)"delete from funnypics where id='?'"<<cc->params["id"]);
        }
        load_funnypics();
    }
    if (cmd=="add") {
        string ct=cc->params["pic_CONTENT-TYPE"];
        if (ct!="image/gif" && ct!="image/jpeg" && ct!="image/pjpeg" &&ct!="image/jpg") {
            m["~msg~"]=_MSG("picturemustbe");
        } else {
            string fn=itostring(cc->params["pic"].size())+itostring(time(NULL))+"."+get_file_ext(cc->params["pic_FILENAME"]);
            string path=(string)chat_config.funny_dir+split_char+fn;
            check_path_wfn(path);
            st_FILE f(path,"wb");
            f.puts(cc->params["pic"]);
            {
                st_dbh d;
                d.dbh->real_queryQ((QUERY)"insert into funnypics (name,descr) values('?','')"<<fn);
            }
            load_funnypics();
            m["~msg~"]=_MSG("added");
        }
    }
    if (pn<0) pn=0;
    vector<string> ids;
    {
        st_dbh d;
        ids=d.dbh->select_1_column("select id from funnypics order by id");
    }
    if (ids.size()<=0) {
        map<string,hstring> K;
        cc->html_out=make_pair(K,"admin/pics/pics_empty");
        return;
    }
    int mx=ids.size()-1;
    if (pn>mx) pn=mx;
    int prev=pn-1;
    int next=pn+1;
    if (next>mx || next<0) next=0;
    if (prev<0 || prev>mx) prev=mx;
    vector<string> v;
    {
        st_dbh d;
        v=d.dbh->select_1_rowQ((QUERY)"select name,descr from funnypics where id=?"<<ids[pn]);
    }
    if (v.size()!=2) {
        throw cError("select() failed. Size is different.");
    }
    m["~id~"]=ids[pn];
    m["~pic~"]="<img src=\"/pics/funnypics/"+v[0]+"\" border=0>";
    m["~descr~"]=v[1];
    m["~pn~"]=itostring(pn);
    m["~prev~"]=itostring(prev);
    m["~next~"]=itostring(next);
    m["~cnt~"]=itostring(mx+1);
    cc->html_out=make_pair(m,"admin/pics/pics");
}

void url_hist_adm(const PTR_getter<chat_user> &__UU,cs_conn_data *cc)
{

    user_pair __U(__UU);
    if (!(user$privileges(__U)&u_is_funny_admin)) return;
    map<string,hstring> m;
    string cmd=cc->params["cmd"];
    int pn=atoi(cc->params["pn"].c_str());
    if (cmd=="add") {
        {
            st_dbh d;
            d.dbh->real_queryQ((QUERY)"update histories set chk=1 where id='?'"<<cc->params["id"]);
        }
        load_histories();
    }
    if (cmd=="remove") {
        {
            st_dbh d;
            d.dbh->real_queryQ((QUERY)"delete from histories where id=?"<<cc->params["id"]);
        }
        load_histories();
    }
    if (pn<0) pn=0;
    vector<string> ids;
    {
        st_dbh d;
        ids=d.dbh->select_1_column("select id from histories order by id desc");
    }
    if (ids.size()<=0) {
        map<string,hstring> K;
        cc->html_out=make_pair(K,"admin/histories/histories_empty");
        return;
    }
    int mx=ids.size()-1;
    if (pn>mx) pn=mx;
    int prev=pn-1;
    int next=pn+1;
    if (next>mx || next<0) next=0;
    if (prev<0 || prev>mx) prev=mx;
    vector<string> v;
    {
        st_dbh d;
        v=d.dbh->select_1_rowQ((QUERY)"select txt,add_by,UNIX_TIMESTAMP(add_date),chk from histories where id=?"<<ids[pn]);
    }
    if (v.size()!=4) {
        throw cError("select() failed. Size is different.");
    }
    string txt=v[0];
    txt=str_replace("\r\n","<br>",txt);
    m["~pn~"]=itostring(pn);
    m["~prev~"]=itostring(prev);
    m["~next~"]=itostring(next);
    m["~text~"]=txt;
    m["~addby~"]=v[1];
    m["~adddate~"]=datetime2rus(atoi(v[2].c_str()));
    m["~cnt~"]=itostring(mx+1);
    m["~id~"]=ids[pn];
    m["~stat~"]=_MSG("checked");
    if (v[3]=="0") {
        m["~stat~"]="<b>"+_MSG("notchecked")+"</b>";
    }
    hstring a;
    if (v[3]=="0") {
        a="<input type=button value='"+_MSG("allow")+"' onclick=\"fupdate('add')\">&nbsp;";
    }
    a+="<input type=button value='"+_MSG("remove")+"' onclick=\"fupdate('remove')\">";
    m["~adm~"]=a;
    cc->html_out=make_pair(m,"admin/histories/histories");
}
#endif

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
void url_news(cs_conn_data *cc)
{
    map<string,hstring> m;
    unsigned int l=atoi(cc->params["l"].c_str());
    unsigned int npp=chat_config.news_per_page;
    vector<c_neu> n=NEWS();
    if (l>=n.size()) l=0;
    unsigned int en=l+npp-1;
    if (en>=n.size()) en=n.size()-1;
    hstring out;
    for (unsigned int i=l;i<=en;i++) {
        if (i<n.size())
        {
            map<string,hstring> q;
            q["~date~"]=date2num(n[i].add_date);
            q["~text~"]=n[i].txt;
//            q["~nid~"]=itostring(n[i].nid);
            q["~nick~"]=n[i].add_by;
            out+=make_pair(q,"news_row");
        }
        else break;
    }
    m["~news~"]=out;
    l+=npp;
    if (l>=n.size()) {
        m["~next~"]="";
    } else {
        m["~next~"]="<a href=\"?l="+itostring(l)+"\">"+_MSG("nextnews")+"</a>";
    }
    cc->html_out=make_pair(m,"news");
}

hstring get_news_for_index(cs_conn_data * cc)
{
    int cn = 0;
    int cnt = chat_config.news_count_in_index_page;
    vector < c_neu > n = NEWS_GET_N(cnt);
    hstring news;
    {
        for (unsigned int i = 0; i < n.size(); i++) {

            map<string , hstring > q;
            q["~date~"] = date2num(n[i].add_date);
            q["~text~"] = n[i].txt;
            q["~nick~"] = n[i].add_by;
            news += make_pair(q, "index_news_row");
            cn++;
            if (cn >= cnt)
                break;
        }
    }
    return news;
}
s_text_funny::s_text_funny() {}
funny_pic::funny_pic() {}
c_neu::c_neu() {}

void url_admin_news(const PTR_getter<chat_user>  &__UU,cs_conn_data *cc)
{
    user_pair __U(__UU);
    if (!(user$privileges(__U)&u_is_news_admin)) return;
    map<string,hstring> m;
    m["~msg~"]="";
    if (cc->params["cmd"]=="add") {
        unsigned int nid=atoi(cc->params["nick"].c_str());


        user_nick	nick=GET_NICK(__U,nid);
        st_dbh d;

        string id;
        d.dbh->real_queryQ((QUERY)"insert into news (txt,add_date,add_nid,add_by,uid) values ('?',NOW(),'?','?','?')"<<cc->params["add"]<<nick.id<<nick.name<<cc->user_id.container);
        id=d.dbh->select_1("select LAST_INSERT_ID() from news");
        load_news();
        m["~msg~"]=_MSG("added");
    }
    if (cc->params["remove"].size()) {
        st_dbh d;
        d.dbh->real_queryQ((QUERY)"delete from news where id='?'"<<cc->params["remove"]);
        m["~msg~"]=_MSG("newsremoved");
        load_news();
    }
    if (cc->params["id"].size()) {
        st_dbh d;
        vector< vector<string> > v=d.dbh->execQ((QUERY)"select txt,UNIX_TIMESTAMP(add_date), add_by from news where id='?'"<<cc->params["id"]);
        string h;
        for (unsigned int i=0;i<v.size();i++) {
            if (v[i].size()!=3) throw cError("select failed.");
            h+=": ";
            h+=v[i][0];
            h+=" (<b>";
            h+=date2num(atoi(v[i][1].c_str()));
            h+="</b>)<br><br>";
            m["~nick~"]=v[i][2];
        }
        m["~new~"]=h;
        cc->html_out=make_pair(m,"admin/news/new");
        return;
    }
    st_dbh d;
    vector< vector<string> > v=d.dbh->execQ((QUERY)"select id,txt,UNIX_TIMESTAMP(add_date) from news  order by add_date desc");
    hstring out;
    for (unsigned int i=0;i<v.size();i++) {
        if (v[i].size()!=3) throw cError("select failed.");
        map<string,hstring> q;
        q["~id~"]=v[i][0];
        string h=v[i][1];
        if (!(user$privileges(__U)&u_allow_tags)) h=remove_tags(h);
        if (h.size()>70) h=h.substr(0,70)+"...";
        q["~new~"]=h;
        q["~date~"]=date2num(atoi(v[i][2].c_str()));
        out+=make_pair(q,"admin/news/news_row");
    }
    m["~news~"]=out;
    out="";
    {
        map<string,hstring> q;
        q["~flang~"]="";
        q["~lang~"]="";
        out+=make_pair(q,"admin/news/news_add");
    }
    m["~addnews~"]=out;



    m["~nicks~"]=build_nicks_select(__U,"nick",GET_CNICK_ID(__U),"");

    cc->html_out=make_pair(m,"admin/news/news");
}
void unpack_news(oscar_buffer &b)
{
    M_LOCK(fMutex);
    b>>news;
}
void pack_news(out_oscar_buffer &b)
{
    M_LOCK(fMutex);
    b<<news;
}

bool load_news()
{
    M_LOCK(fMutex);
    news.clear();
    try {
        vector< vector<string> > v;
        {
            st_dbh d;
            v=d.dbh->execQ((QUERY)"select id,txt,add_by,UNIX_TIMESTAMP(add_date) from news order by add_date desc");
        }
        for (unsigned j=0;j<v.size();j++) {
            if (v[j].size()!=4) throw cError("select failed");
            c_neu n;
            n.id=atoi(v[j][0].c_str());
            n.txt=v[j][1];
            n.add_by=v[j][2];
            n.add_date=atoi(v[j][3].c_str());
            news.push_back(n);
        }
    } catch (cError e) {
        logErr2("--Error: load_news error: %s",e.error_string.c_str());
        return false;
    }
    return true;
}


out_oscar_buffer & operator<<(out_oscar_buffer&b, const c_neu& n)
{
    b<<n.id;
    b<<n.txt;
    b<<n.add_by;
    b<<n.add_date;
    return b;

}
oscar_buffer & operator>>(oscar_buffer&b, c_neu& n)
{
    b>>n.id;
    b>>n.txt;
    b>>n.add_by;
    b>>n.add_date;
    return b;

}
