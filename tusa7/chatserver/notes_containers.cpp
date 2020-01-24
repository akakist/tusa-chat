#include "stdafx.h"
#include "_mutex.h"
#include <list>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <map>
#ifndef __CLAN
#include "mysql_extens.h"
#endif
#include "_mutex.h"
#include "user.h"
#include "utils.h"
#include "str_lib.h"
#include "web_server.h"
#include "message.h"
#include "chat_def.h"
#include "copy_file.h"
#include "wrappers.h"
#include "file_set.h"
#include "notes.h"
#include "levels.h"
#include "server_config.h"
#include "chat_config.h"
#include <sys/types.h>
#ifndef WIN32
#include <dirent.h>
#endif
#include <algorithm>
#ifndef WIN32
#include <dirent.h>
#endif
#include "DR_types.h"
db_map<u_notes> __notes("user_notes",DBMAP_MYSQL,DBMAP_REFID);
db_map<note_text> note_texts("note_texts",DBMAP_MYSQL,DBMAP_REFID);

string FOLD_ID(unsigned int uid, unsigned int fold);
string FOLD_ID(unsigned int uid, unsigned int fold)
{
    return itostring(uid)+"."+itostring(fold);
}
string cache_dir(const string & name, unsigned int uid);

string attach_pn(const DB_id&  uid,unsigned int msgid, const string& orig)
{
    string pn=cache_dir("user",uid.container)+"/attach/"+itostring(msgid)+"_"+orig;
    return pn;
}
string date2mysql_short(time_t t);
string attach_pn_copy(const DB_id&  uid,unsigned int msgid, const string& orig)
{
    char pn[300];
    pn[0]=0;
    string sid=itostring(msgid);
    string dd=date2mysql_short(time(NULL));
    if (msgid<0x100)
    {
        snprintf(pn,sizeof(pn)-1,"%s" SPLITTER "removed-%s" SPLITTER "0_%X_%02x%s",global_config.var_dir.get().c_str(),dd.c_str(),uid.container,msgid,orig.c_str());
    }
    else if (msgid<0x10000)
    {
        snprintf(pn,sizeof(pn)-1,"%s" SPLITTER "removed-%s" SPLITTER "1_%X_%02x_%02x%s",global_config.var_dir.get().c_str(),dd.c_str(),uid.container,msgid/0x100,msgid%0x100,orig.c_str());
    }
    else if (msgid<0x1000000)
    {
        int u1=msgid/0x10000;
        int u2=(msgid-(u1*0x10000))/0x100;
        int u3=msgid%0x100;
        snprintf(pn,sizeof(pn)-1,"%s" SPLITTER "removed-%s" SPLITTER "2_%X_%02x_%02x_%02x%s",global_config.var_dir.get().c_str(),dd.c_str(),uid.container,u1,u2,u3,orig.c_str());
    }
    else if (msgid<0xffffffff)
    {
        int u1=msgid/0x1000000;
        int u2=(msgid-(u1*0x1000000))/0x10000;
        int u3=(msgid-(u1*0x10000))/0x100;
        int u4=msgid%0x100;
        snprintf(pn,sizeof(pn)-1,"%s" SPLITTER "removed-%s" SPLITTER "2_%x_%02x_%02x_%02x_%02x%s",global_config.var_dir.get().c_str(),dd.c_str(),uid.container,u1,u2,u3,u4,orig.c_str());
    }
    else {
        logErr2("attachdir id >= UNREG_BASE %s","");
        throw cError("attachdir id >= UNREG_BASE");
    }
    return pn;

}

string cache_dir(const string & name, unsigned int uid)
{

    char pn[300];
    pn[0]=0;
    string sid=itostring(uid);
    if (uid<100)
    {
        snprintf(pn,sizeof(pn)-1,"%s" SPLITTER "%s" SPLITTER "0" SPLITTER "%02d",global_config.var_dir.get().c_str(),name.c_str(),uid);
    }
    else if (uid<10000)
    {
        snprintf(pn,sizeof(pn)-1,"%s" SPLITTER "%s" SPLITTER "1" SPLITTER "%02d/%02d",global_config.var_dir.get().c_str(),name.c_str(),uid/100,uid%100);
    }
    else if (uid<1000000)
    {
        int u1=uid/10000;
        int u2=(uid-(u1*10000))/100;
        int u3=uid%100;
        snprintf(pn,sizeof(pn)-1,"%s" SPLITTER "%s" SPLITTER "2" SPLITTER "%02d" SPLITTER "%02d" SPLITTER "%02d",global_config.var_dir.get().c_str(),name.c_str(),u1,u2,u3);
    }
    else if (uid<100000000)
    {
        int u1=uid/1000000;
        int u2=(uid-(u1*1000000))/10000;
        int u3=(uid-(u1*10000))/100;
        int u4=uid%100;
        snprintf(pn,sizeof(pn)-1,"%s" SPLITTER "%s" SPLITTER "3" SPLITTER "%02d" SPLITTER "%02d" SPLITTER "%02d" SPLITTER "%02d",global_config.var_dir.get().c_str(),name.c_str(),u1,u2,u3,u4);
    }
    else {
        logErr2("cache_dir id >= UNREG_BASE %s","");
        throw cError("cache_dir id >= UNREG_BASE");
    }
    return pn;

}

string cache_dir2(const string & name, unsigned int uid)
{

    char pn[300];
    pn[0]=0;
    string sid=itostring(uid);
    if (uid<100)
    {
        snprintf(pn,sizeof(pn)-1,"%s" SPLITTER "%s" SPLITTER "0" SPLITTER "%02d",global_config.var_dir.get().c_str(),name.c_str(),uid);
    }
    else if (uid<10000)
    {
        snprintf(pn,sizeof(pn)-1,"%s" SPLITTER "%s" SPLITTER "1" SPLITTER "%02d/%02d",global_config.var_dir.get().c_str(),name.c_str(),uid/100,uid%100);
    }
    else if (uid<1000000)
    {
        int u1=uid/10000;
        int u2=(uid-(u1*10000))/100;
        int u3=uid%100;
        snprintf(pn,sizeof(pn)-1,"%s" SPLITTER "%s" SPLITTER "2" SPLITTER "%02d" SPLITTER "%02d" SPLITTER "%02d",global_config.var_dir.get().c_str(),name.c_str(),u1,u2,u3);
    }
    else if (uid<100000000)
    {
        int u1=uid/1000000;
        int u2=(uid-(u1*1000000))/10000;
        int u3=(uid-(u1*10000))/100;
        int u4=uid%100;
        snprintf(pn,sizeof(pn)-1,"%s" SPLITTER "%s" SPLITTER "3" SPLITTER "%02d" SPLITTER "%02d" SPLITTER "%02d" SPLITTER "%02d",global_config.var_dir.get().c_str(),name.c_str(),u1,u2,u3,u4);
    }
    else {
        logErr2("cache_dir id >= UNREG_BASE %s","");
        throw cError("cache_dir id >= UNREG_BASE");
    }
    return pn;

}

string homedir(unsigned int uid)
{

    return cache_dir("homes",uid);

}

static int srt_note_size(const pair<__note_head, unsigned int/*fid*/>& a,const pair<__note_head, unsigned int/*fid*/>& b) {
    return a.first.nfh.content_length<b.first.nfh.content_length;
}
static int srt_note_size_desc(const pair<__note_head, unsigned int/*fid*/>& a,const pair<__note_head, unsigned int/*fid*/>& b) {
    return a.first.nfh.content_length>b.first.nfh.content_length;
}

static int srt_note_from(const pair<__note_head, unsigned int/*fid*/>& a,const pair<__note_head, unsigned int/*fid*/>& b) {
    return a.first.nfh.from_nick<b.first.nfh.from_nick;
}
static int srt_note_from_desc(const pair<__note_head, unsigned int/*fid*/>& a,const pair<__note_head, unsigned int/*fid*/>& b) {
    return a.first.nfh.from_nick>b.first.nfh.from_nick;
}

static int srt_note_to(const pair<__note_head, unsigned int/*fid*/>& a,const pair<__note_head, unsigned int/*fid*/>& b) {
    return a.first.nfh.to_nick<b.first.nfh.to_nick;
}
static int srt_note_to_desc(const pair<__note_head, unsigned int/*fid*/>& a,const pair<__note_head, unsigned int/*fid*/>& b) {
    return a.first.nfh.to_nick>b.first.nfh.to_nick;
}

static int srt_note_senddate(const pair<__note_head, unsigned int/*fid*/>& a,const pair<__note_head, unsigned int/*fid*/>& b) {
    return a.first.nfh.send_date<b.first.nfh.send_date;
}
static int srt_note_senddate_desc(const pair<__note_head, unsigned int/*fid*/>& a,const pair<__note_head, unsigned int/*fid*/>& b) {
    return a.first.nfh.send_date>b.first.nfh.send_date;
}

static int srt_note_subj(const pair<__note_head, unsigned int/*fid*/>& a,const pair<__note_head, unsigned int/*fid*/>& b) {
    return a.first.nfh.subject<b.first.nfh.subject;
}
static int srt_note_subj_desc(const pair<__note_head, unsigned int/*fid*/>& a,const pair<__note_head, unsigned int/*fid*/>& b) {
    return a.first.nfh.subject>b.first.nfh.subject;
}

bool u_notes::find_msg_by_id(unsigned int id, __note_head &h) const // 0 failure
{
    map<unsigned int,__note_head>::const_iterator i=map_msgs.find(id);
    if (i!=map_msgs.end())
    {
        h=i->second;
        return true;
    }
    return false;
}

u_notes::u_notes()
{
}


void u_notes::resort(unsigned char sort, bool sort_desc)
{
    for (map<unsigned int,__note_folder> ::iterator i=map_folders.begin();i!=map_folders.end();i++)
    {
        unsigned int fid=i->first;
        set<unsigned int> ss;
        for (unsigned j=0;j<i->second.vec_msgs.size();j++)
        {
            ss.insert(i->second.vec_msgs[j]);
        }
        vector< pair <__note_head, unsigned int/*fid*/> > v;


        for ( set<unsigned int>::iterator j=ss.begin();j!=ss.end();j++)
        {
            unsigned int msgid=*j;
            v.push_back(pair<__note_head, unsigned int/* msgid*/>(map_msgs[msgid],msgid));
        }
        if (sort==sort_date)
        {
            if (sort_desc)
                ::sort(v.begin(),v.end(),srt_note_senddate_desc);
            else	::sort(v.begin(),v.end(),srt_note_senddate);
        }
        else if (sort==sort_size)
        {
            if (sort_desc)
                ::sort(v.begin(),v.end(),srt_note_size_desc);
            else	::sort(v.begin(),v.end(),srt_note_size);
        }
        else if (sort==sort_from)
        {
            if (sort_desc)
                ::sort(v.begin(),v.end(),srt_note_from_desc);
            else	::sort(v.begin(),v.end(),srt_note_from);
        }
        else if (sort==sort_to)
        {
            if (sort_desc)
                ::sort(v.begin(),v.end(),srt_note_to_desc);
            else	::sort(v.begin(),v.end(),srt_note_to);
        }
        else if (sort==sort_subj)
        {
            if (sort_desc)
                ::sort(v.begin(),v.end(),srt_note_subj_desc);
            else	::sort(v.begin(),v.end(),srt_note_subj);
        }
        map_folders[fid].vec_msgs.clear();
        for (unsigned k=0;k<v.size();k++)
        {
            map_folders[fid].vec_msgs.push_back(v[k].second);
        }

    }
}
#ifdef __CLAN
int note_text::load_from_db(const string & table_name)
{
    out_oscar_buffer b;
    b<<get_db_row_id().as_string();
    string r=clan_data_request(DR_note_text,b);
    oscar_buffer bb(r.data(),r.size());
    unpack(bb);
    return 0;
}
#else
int note_text::load_from_db(const string & table_name)
{
    try {
        string id=get_db_row_id().as_string();

        vector<string> v=splitTOK(".",id);
        if (v.size()==2)
        {
            DB_id uid;
            uid.container=atoi(v[0]);
            int nid=atoi(v[1]);
            st_dbh d;
            vector<string>vv=d.dbh->select_1_rowQ((QUERY)"select body from note_texts where message_id=? and owner_uid=?"<<nid<<uid.container);
            if (vv.size())
                body=vv[0];
        }
        return 0;
    }
    catch (cError e)
    {
        logErr2("catched %s %s %d",e.what(),__FILE__,__LINE__);
        return -1;
    }
    catch (...)
    {
        logErr2("catched  %s %d",__FILE__,__LINE__);
        return -1;
    }
    return 0;
}
#endif
string update_to_db(const PTR_getter<note_text>&__P,const string &tblname)
{
    return "";
}
#ifdef __CLAN
#else
void load_notes(u_notes &p, const DB_id&  uid)
{

    st_dbh d;
    vector<vector<string> > vfold=d.dbh->execQ((QUERY)"select id,name from note_folders where uid=?"<<uid.container);
    vector<string> vf;
    for (unsigned i=0;i<vfold.size();i++)
    {
        if (vfold[i].size()==2)
        {
            p.map_folders[atoi(vfold[i][0])].name=vfold[i][1];
            vf.push_back(vfold[i][0]);
        }
    }
    vector<string> ms;
    if (vf.size())
    {
        vector<vector<string> > fin=d.dbh->execQ((QUERY)"select folder_id, uid from filters_in where owner_uid=?"<<uid.container);
        for (unsigned i=0;i<fin.size();i++)
        {
            if (fin[i].size()==2)
            {
                p.map_folders[atoi(fin[i][0])].filter_in.insert(atoi(fin[i][1]));
            }
        }
        vector<vector<string> > fout=d.dbh->execQ((QUERY)"select folder_id, uid from filters_out where owner_uid=?"<<uid.container);
        for (unsigned i=0;i<fout.size();i++)
        {
            if (fout[i].size()==2)
            {
                p.map_folders[atoi(fout[i][0])].filter_out.insert(atoi(fout[i][1]));
            }
        }
        vector<vector<string> > m=d.dbh->execQ((QUERY)
                                               "select id,from_nick_id,to_nick_id,from_uid,to_uid,from_nick,to_nick,subject,UNIX_TIMESTAMP(send_date),status,unread,content_length,has_attachment,"
                                               "attachment_filename,attachment_content_length,important,system,owner_folder,notify_read  from notes where owner_uid=?"<<uid.container);
        for (unsigned i=0;i<m.size();i++) {

            if (m[i].size()==19)
            {
                __note_head hh;
                hh.id=atoi(m[i][0]);
                hh.nfh.from_nick_id=atoi(m[i][1]);
                hh.nfh.to_nick_id=atoi(m[i][2]);
                hh.nfh.from_uid=atoi(m[i][3]);
                hh.nfh.to_uid=atoi(m[i][4]);
                hh.nfh.from_nick=m[i][5];
                hh.nfh.to_nick=m[i][6];
                hh.nfh.subject=m[i][7];
                hh.nfh.send_date=atoi(m[i][8]);
                hh.nfh.status=atoi(m[i][9]);
                hh.nfh.unread=atoi(m[i][10]);
                if (hh.nfh.from_uid==uid.container)hh.nfh.unread=false;
                hh.nfh.content_length=atoi(m[i][11]);
                hh.nfh.has_attachment=atoi(m[i][12]);
                hh.nfh.attachment_filename=m[i][13];
                hh.nfh.attachment_content_length=atoi(m[i][14]);
                hh.nfh.important=atoi(m[i][15]);
                hh.nfh.system=atoi(m[i][16]);
                hh.nfh.notify_read =atoi(m[i][18]);
                p.map_msgs[hh.id]=hh;
                p.map_folders[atoi(m[i][17])].vec_msgs.push_back(hh.id);

            }
        }
    }

    unsigned char sort;
    bool  sort_desc;

    {
        PGLR(user_set,u,user_sets.find_by_id(uid));
        sort=u->notes_sort;
        sort_desc=u->notes_sort_desc;
    }

    p.resort(sort,sort_desc);

}
#endif
string update_to_db(const PTR_getter<u_notes> &__U,const string& table_name)
{
    return "";
}
#ifdef __CLAN
int u_notes::load_from_db(const string & table_name) const
{

    DB_id id;
    id.container=get_db_row_id().as_int();
    string r=clan_data_request(DR_u_notes,id);
    oscar_buffer bb(r.data(),r.size());
    ((u_notes*)this)->unpack(bb);
    return 0;

}
#else
int u_notes::load_from_db(const string & table_name) const
{

    DB_id id;
    id.container=get_db_row_id().as_int();
    try {

        u_notes *u=(u_notes *) this;
        load_notes(*u,id);
        return 0;
    }
    catch (cError e)
    {
        logErr2("catched %s %s %d",e.what(),__FILE__,__LINE__);
        return -1;
    }
    catch (...)
    {
        logErr2("catched  %s %d",__FILE__,__LINE__);
        return -1;
    }
    return 0;
}
#endif

oscar_buffer& operator>>(oscar_buffer & b, u_notes   &c)
{
    b>>c.map_folders>>c.map_msgs;
    return b;
}
out_oscar_buffer& operator<<(out_oscar_buffer & b, const u_notes & c)
{
    b<<c.map_folders<<c.map_msgs;
    return b;
}
oscar_buffer& operator>>(oscar_buffer & b, __note_folder   &c)
{
    b>>c.name>>c.filter_in>>c.filter_out>>c.vec_msgs;
    return b;
}
out_oscar_buffer& operator<<(out_oscar_buffer & b, const __note_folder & c)
{
    b<<c.name<<c.filter_in<<c.filter_out<<c.vec_msgs;
    return b;
}
out_oscar_buffer& operator<<(out_oscar_buffer & b, const __note_head & c)
{
    b<<c.id<<c.nfh;
    return b;
}
oscar_buffer& operator>>(oscar_buffer & b, __note_head   &c)
{
    b>>c.id>>c.nfh;
    return b;
}
oscar_buffer& operator>>(oscar_buffer & b, note_file_head   &c)
{
    b>>c.subject>>c.from_nick>>c.to_nick>>c.to_nick_id>>c.from_nick_id>>c.to_uid>>c.from_uid>>c.unread>>c.important>>c.system>>c.content_length>>c.send_date>>c.status>>c.has_attachment>>c.attachment_filename>>c.attachment_content_length>>c.notify_read;
    return b;
}
out_oscar_buffer& operator<<(out_oscar_buffer & b, const note_file_head & c)
{
    b<<c.subject<<c.from_nick<<c.to_nick<<c.to_nick_id<<c.from_nick_id<<c.to_uid<<c.from_uid<<c.unread<<c.important<<c.system<<c.content_length<<c.send_date<<c.status<<c.has_attachment<<c.attachment_filename<<c.attachment_content_length<<c.notify_read;
    return b;
}
void u_notes::pack(out_oscar_buffer &b) const
{
    b<<map_folders<<map_msgs;

}
void u_notes::unpack(oscar_buffer &b)
{
    b>>map_folders>>map_msgs;

}
