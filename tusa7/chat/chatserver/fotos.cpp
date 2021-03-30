#include "stdafx.h"
#include "_mutex.h"
#include "db_var.h"
#include "copy_file.h"
#include "st_stuff.h"
#include "fotos.h"
#include "user.h"
#include <sys/stat.h>
#include "server_config.h"
#include "DR_types.h"
#include "utils.h"
db_map<user_fotos> users_fotos("users_fotos",DBMAP_MYSQL,DBMAP_REFID);

string cache_dir(const string & name, unsigned int uid);
string cache_dir2(const string & name, unsigned int uid);
using namespace std;

int calc_photo_rating(const map<DB_id,int> &m)
{

    return 0;
}

unsigned int user_fotos::index2id(unsigned int index) const
{
    int k=0;
    for (map<unsigned int, __foto>::const_iterator i=fotos.begin();i!=fotos.end();i++,k++)
    {
        if (k==index) return i->first;
    }
    throw cError("INdex invalid");
}
unsigned int user_fotos::getsize() const
{
    unsigned int ret=0;
    for (map<unsigned int, __foto>::const_iterator i=fotos.begin();i!=fotos.end();i++)
    {
        ret+=i->second.size;
    }
    return ret;
}
#ifdef __CLAN


int user_fotos::load_from_db(const string & table_name) const
{
    DB_id id;
    id.container=get_db_row_id().as_int();
    string r=clan_data_request(DR_user_fotos,id);
    oscar_buffer bb(r.data(),r.size());
    ((user_fotos*)this)->unpack(bb);
    return 0;
}
#else
int user_fotos::load_from_db(const string & table_name) const
{

    unsigned int uid=get_db_row_id().as_int();
    user_fotos *p=(user_fotos *)this;
    p->__last_change_time=time(NULL);
    p->fotos.clear();
    st_dbh d;
    vector<vector<string> > v=d.dbh->execQ((QUERY)"select ID,orig_filename,descr,size,ext,rating from photos where uid=?"<<uid);
    for (unsigned i=0;i<v.size();i++)
    {
        if (v[i].size()==6)
        {
            __foto f;
            f.id=atoi(v[i][0].c_str());
            f.orig_fn=v[i][1];
            f.descr=v[i][2];
            f.size=atoi(v[i][3].c_str());
            f.ext=v[i][4];
            f.uid.container=uid;
            oscar_buffer b(v[i][5].data(),v[i][5].size());
            b>>f.rates;
            p->fotos[atoi(v[i][0].c_str())]=f;
        }
    }

    return 0;
}
#endif
string update_to_db(const PTR_getter<user_fotos> &__U,const string& table_name)
{
    return "";
}

out_oscar_buffer & operator<<(out_oscar_buffer &b, const __foto &f)
{
    b<<f.uid<<f.id<<f.descr<<f.orig_fn<<f.ext<<f.size<<f.rates;
    return b;
}
oscar_buffer & operator>>(oscar_buffer &b,  __foto &f)
{
    b>>f.uid>>f.id>>f.descr>>f.orig_fn>>f.ext>>f.size>>f.rates;
    return b;

}
void foto_rm_cache(const DB_id& uid,unsigned int pid)
{
#ifdef WIN32
    string pn="del /S /F /Q  ";
#else
    string pn="rm -f -R ";
#endif
    pn+=cache_dir2("photo_cache",uid.container)+"-"+itostring(pid);
    system(pn.c_str());
}
string foto_pn_cache(const DB_id& uid,unsigned int pid, unsigned int xsize,const string& ext)
{
    string pn=cache_dir2("photo_cache",uid.container)+"-"+itostring(pid)+SPLITTER+itostring(xsize)+"."+ext;
    return pn;
}

string foto_pn(const DB_id& uid,unsigned int pid, const string& ext)
{
    string pn=cache_dir("user",uid.container)+SPLITTER "photos" SPLITTER+itostring(pid)+"."+ext;
    return pn;
}
string date2mysql_short(time_t t);
string foto_pn_copy(const DB_id& uid,unsigned int pid, const string& ext)
{
    char pn[300];
    pn[0]=0;
    snprintf(pn,sizeof(pn)-1,"%s/removed_fotos-%s/%d-%d.%s",global_config.var_dir.get().c_str(),date2mysql_short(time(NULL)).c_str(),uid.container,pid,ext.c_str());
    return pn;
}


void user_fotos::pack(out_oscar_buffer &b) const
{
    b<<fotos;
}
void user_fotos::unpack(oscar_buffer &b)
{
    b>>fotos;
}
