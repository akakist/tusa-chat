#include "stdafx.h"
#ifdef _DEBUG
#define New DEBUG_NEW
#endif

#include "_mutex.h"
#include "mutex_inspector.h"
#include "db_var.h"
#include "copy_file.h"
#include "st_stuff.h"
#include "fotos.h"
#include "user.h"
#include <sys/stat.h>
#include "server_config.h"
#include "DR_types.h"
#include "utils.h"
#include "mysql_extens.h"
db_map<unsigned int,user_fotos> users_fotos("users_fotos");

string cache_dir(const string & name, unsigned int uid);
string __new_cache_dir(unsigned int uid);

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
    throw cError("INdex invalid"+_DMI());
}
size_t user_fotos::getsize() const
{
    size_t ret=0;
    for (map<unsigned int, __foto>::const_iterator i=fotos.begin();i!=fotos.end();i++)
    {
        ret+=i->second.size;
    }
    return ret;
}



int user_fotos::load_from_db(const string & table_name) const
{
    MUTEX_INSPECTOR;

    unsigned int uid=id;
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
            f.id=atoi(v[i][0]);
            f.orig_fn=v[i][1];
            f.descr=remove_tags(v[i][2]);
            f.size=atoi(v[i][3]);
            f.ext=v[i][4];
//            f.CONTAINER(uid)=uid;
            oscar_buffer b(v[i][5].data(),v[i][5].size());
            b>>f.rates;
            p->fotos[atoi(v[i][0])]=f;
        }
    }
    string pf=d.dbh->select_1Q((QUERY)"select primary_photo from tbl_users where id=?"<<uid);
    p->primary=atoi(pf);

    return 0;
}


out_oscar_buffer & operator<<(out_oscar_buffer &b, const __foto &f)
{
    b<<f.id<<f.descr<<f.orig_fn<<f.ext<<f.size<<f.rates;
    return b;
}
oscar_buffer & operator>>(oscar_buffer &b,  __foto &f)
{
    b>>f.id>>f.descr>>f.orig_fn>>f.ext>>f.size>>f.rates;
    return b;

}

string thumb_big_url(unsigned int pid)
{
	return (string)"http://tusovka.tomsk.ru:88/thumbs-big" +SPLITTER+ __new_cache_dir(pid)+SPLITTER+itostring(pid)+".jpeg";
}
string thumb_small_url(unsigned int pid)
{
	return (string)"http://tusovka.tomsk.ru:88/thumbs-small" +SPLITTER+ __new_cache_dir(pid)+SPLITTER+itostring(pid)+".jpeg";
}

string thumb_big(unsigned int pid)
{
	return global_config.var_dir.get()+SPLITTER+ "thumbs-big" +SPLITTER+ __new_cache_dir(pid)+SPLITTER+itostring(pid)+".jpeg";
}
string thumb_small(unsigned int pid)
{
	return global_config.var_dir.get()+SPLITTER+ "thumbs-small" +SPLITTER+ __new_cache_dir(pid)+SPLITTER+itostring(pid)+".jpeg";
}
void foto_remove(unsigned int pid)
{
    string pn="rm -f -R ";
    pn+=thumb_small(pid)+" "+thumb_big(pid);
    system(pn.c_str());
	//st_dbh d;
	//d.dbh->real_queryQ((QUERY)"delete from photos where id=?"<<pid);
}
/*string foto_pn_cache(unsigned int pid, const string& ext, const string& meth, const string& scale)
{
    string pn=global_config.var_dir.get()+SPLITTER+ "photo_cache" +SPLITTER+ __new_cache_dir(pid)+SPLITTER+itostring(pid)+"-"+meth+scale+"."+ext;
    return pn;
}
*/
/*string foto_pn(unsigned int pid, const string& ext)
{
    string pn=new_cache_dir("photos",pid)+SPLITTER +itostring(pid)+"."+ext;
    return pn;
}*/
string date2mysql_short(time_t t);
/*string foto_pn_copy(const DB_id& uid,unsigned int pid, const string& ext)
{
    char pn[300];
    pn[0]=0;
    snprintf(pn,sizeof(pn)-1,"%s/removed_fotos-%s/%d-%d.%s",global_config.var_dir.get().c_str(),date2mysql_short(time(NULL)).c_str(),CONTAINER(uid),pid,ext.c_str());
    return pn;
}*/


void user_fotos::pack(out_oscar_buffer &b) const
{
    b<<fotos<<primary;
}
void user_fotos::unpack(oscar_buffer &b)
{
    b>>fotos>>primary;
}

void user_fotos::on_id_not_exists(const string &tbname, unsigned int _id)
{
    logErr2("invalid call on_id_not_exists %s %d %s",tbname.c_str(),_id,_DMI().c_str());
    throw cError("invalid call on_id_not_exists %s %d %s",tbname.c_str(),_id,_DMI().c_str());
}


