#ifndef DB_VAR_BX_BANADMIN_H__
#define DB_VAR_BX_BANADMIN_H__
#include <vector>
#include <string>
#include "str_lib.h"
#include "PTR.h"
#include <time.h>
#ifndef __CLAN
#include "mysql_extens.h"
#include "_QUERY.h"
#endif
#include "db_id_type.h"
#include "oscar_buffer.h"

_mutex* select_table_mutex(const string& tbname);
void exec_sql(const string &s);

template <class T>
class db_var
{
    bool __changed;
    T __container;
public:
    db_var(): __changed(false) {}
    void load(const T& c)const {
        (T&)__container=c;
    }
    operator const T&()const {
        return __container;
    }
    const T* operator ->() const {
        return  &__container;
    }
    T& dbset(const T& c) {
        __container=c;
        __changed=true;
        return __container;
    }
    const T& get() const {
        return __container;
    }
    T& ref()  {
        __changed=true;
        return __container;
    }
#ifndef __CLAN
    void update_str(vector<string>&v, const char *rowname) const
    {
        if (__changed)
        {
            QUERY q;
            q<<"?='?'"<<rowname<<__container;
            v.push_back(q.prepare());
            (bool&)__changed=false;
        }
    }
    void update_bin(vector<string>&v, const char *rowname) const
    {
        if (__changed)
        {
            string s;
            s<<rowname<<"='"<<MES(as_binary(__container))<<"'";
            v.push_back(s);
            (bool&)__changed=false;
        }
    }
    void update_strtime(vector<string>&v, const char *rowname) const
    {
        if (__changed)
        {
            QUERY q;
            q<<"?=FROM_UNIXTIME(?)"<<rowname<<__container;
            v.push_back(q.prepare());
            (bool&)__changed=false;
        }
    }
    void update_uchar(vector<string>&v, const char *rowname) const
    {
        if (__changed)
        {
            string s;
            s<<rowname<<"='"<<MES(string((char*)&__container,1))<<"'";
            v.push_back(s);
            (bool&)__changed=false;
        }

    }
#endif
};

class db_row: public base_container
{
private:
    db_id_type id;
public:
    time_t __last_update_time;

    db_row();
    void set_db_row_id(unsigned int _id) {
        id=_id;
    }
    void set_db_row_id(const string &_id) {
        id=_id;
    }
    void set_db_row_id(const db_id_type &_id) {
        id=_id;
    }
    db_id_type get_db_row_id()const {
        return id;
    }

};


enum DBMAP_DBTYPE
{
    DBMAP_MYSQL,
    DBMAP_GDBM,
    DBMAP_PROFILE
};
enum DBMAP_IDTYPE
{
    DBMAP_AUTOID,
    DBMAP_REFID
};
db_id_type db_map_on_id0(const string &tbname,DBMAP_DBTYPE,DBMAP_IDTYPE);
void db_map_on_idN_not_exists(const string &tbname, const db_id_type& id,DBMAP_DBTYPE,DBMAP_IDTYPE);

class db_map_base
{
protected:
    _mutex Mutex;
public:
    string table_name;
    DBMAP_DBTYPE dbmap_dbtype;
    DBMAP_IDTYPE dbmap_idtype;
    virtual ~db_map_base() {}
    db_map_base(const string &tablen,DBMAP_DBTYPE _dbmap_dbtype,DBMAP_IDTYPE _dbmap_idtype);
    virtual void purge(time_t update_timeout, time_t drop_timeout)=0;
    virtual size_t __xx_size()=0;
};

template <class T>
class db_map:public db_map_base
{
    map < db_id_type, PTR_getter < T > >container;
    time_t last_drop_time;
    time_t last_update_time;
public:
    db_map(const string & tablen, DBMAP_DBTYPE _dbmap_dbtype, DBMAP_IDTYPE _dbmap_idtype)
            : db_map_base(tablen, _dbmap_dbtype, _dbmap_idtype),last_drop_time(time(NULL))
    {

    }
    ~db_map()
    {
    }
    void init(const db_id_type & id,oscar_buffer &b)
    {
        T *bb = new T;
        bb->unpack(b);
        {
            M_LOCK(Mutex);
            PTR_getter < T > bbb(bb);
            container.insert(pair < db_id_type, PTR_getter < T > >(id, bbb));
        }

    }
    PTR_getter < T > find_by_id(const db_id_type & id/*, FBI_TYPE fbit*/)
    {

        PTR_getter < T > b(NULL);
        if (id.id.size() != 0) {
            M_LOCK(Mutex);
#ifdef WIN32
            map < db_id_type, PTR_getter < T > >::iterator  i = container.find(id);
#else
            typeof( container.find(id)) i= container.find(id);
#endif
            if (i != container.end())
            {
                return i->second;
            }
        }

        if (id.id.size() == 0) {

            if (dbmap_idtype != DBMAP_AUTOID)
                throw cError(table_name + " dbmap_idtype != DBMAP_AUTOID " );

            T *bb = new T;
            if (!bb)
                throw cError(table_name + " !bb");
            db_id_type _id = db_map_on_id0(table_name, dbmap_dbtype, dbmap_idtype);
            bb->set_db_row_id(_id);
            PTR_getter < T > bbb(bb);
            {
                M_LOCK(Mutex);
                if (!container.count(_id)) {
                    container.insert(pair < db_id_type, PTR_getter < T > >(_id, bbb));
                }
                else throw cError("dbmap insert count(id)!=0");
            }

            return bbb;
        }
        if (!b) {

            T *bb = new T;
            if (!bb)
                throw cError(table_name + " !bb" );
            bb->set_db_row_id(id);
            {
                if (bb->load_from_db(table_name)) {
                    if (dbmap_idtype != DBMAP_REFID)
                        throw cError(table_name + " dbmap_idtype != DBMAP_REFID " );
                    {
                        db_map_on_idN_not_exists(table_name, id, dbmap_dbtype, dbmap_idtype);
                    }
                }
            }
            PTR_getter < T > bbb(bb);
            {
                M_LOCK(Mutex);
                if (!container.count(id)) {
                    container.insert(pair < db_id_type, PTR_getter < T > >(id, bb));
                }
                else throw cError("dbmap insert count(id)!=0");
            }
            return bbb;
        }
        return NULL;
    }
    PTR_getter < T > get(const db_id_type & id)
    {


        PTR_getter < T > b(NULL);
        if (id.id.size() != 0) {
            M_LOCK(Mutex);
#ifdef WIN32
            map < db_id_type, PTR_getter < T > >::iterator  i=container.find(id);
#else
            typeof(container.find(id))i = container.find(id);
#endif
            if (i != container.end())
                return i->second;
        }
        return NULL;
    }

    PTR_getter < T > find_by_id_no_create(const db_id_type & id)
    {


        PTR_getter < T > b(NULL);
        if (id.id.size() != 0) {
            M_LOCK(Mutex);
            typeof(container.find(id))i = container.find(id);
            if (i != container.end())
                return i->second;
        }

        if (id.id.size() == 0) {
            throw cError(table_name + " id.id.size() == 0 " );
        }
        if (!b) {

            T *bb = new T;
            if (!bb)
                throw cError(table_name + " !bb" );
            bb->set_db_row_id(id);
            {
                if (bb->load_from_db(table_name)) {
                    delete bb;
                    return NULL;
                }
            }
            PTR_getter < T > bbb(bb);
            {
                M_LOCK(Mutex);
                if (!container.count(id)) {
                    container.insert(pair < db_id_type, PTR_getter < T > >(id, bbb));
                }
                else throw cError("dbmap insert count(id)!=0");
            }

            return bbb;
        }
        return NULL;
    }
    void purge(time_t update_timeout, time_t drop_timeout)
    {

        if (time(NULL)-last_update_time<=update_timeout) return;

        last_update_time=time(NULL);

//    unsigned csize;
        vector < db_id_type > vdel;
        vector<db_id_type> c_copy;
        {
            M_LOCK(Mutex);
#ifdef WIN32
            map < db_id_type, PTR_getter < T > >::iterator i;
#else
            typeof(container.begin())i;
#endif

            for (i = container.begin(); i != container.end(); i++)
            {
                c_copy.push_back(i->first);
            }
        }
        time_t t = time(NULL);
        for (unsigned i=0;i<c_copy.size();i++)
        {

            if (c_copy[i].id.size() == 0)
                continue;

            PTR_getter < T > __P=NULL;
            {
                M_LOCK(Mutex);
#ifdef WIN32
                map < db_id_type, PTR_getter < T > >::iterator it=container.find(c_copy[i]);
#else
                typeof(container.find(c_copy[i])) it=container.find(c_copy[i]);
#endif

                if (it!=container.end()) __P=it->second;
            }
            string update_sql;
            bool need_update=false;
            if (__P)
            {
                {
                    PTR_getter_lock_write_no_access< T > br(__P);
                    if (br->__last_change_time && t - br->__last_update_time > update_timeout)
                    {
                        need_update=true;
                        //       update_sql = br->update_to_db(table_name);
                        br->__last_change_time = 0;
                        br->__last_update_time = t;

                    }
                }
                if (need_update)
                {
#ifndef WIN32
                    update_sql=update_to_db(__P,table_name);
                    if (update_sql.size() && dbmap_dbtype != DBMAP_MYSQL)
                        throw cError(table_name + " update_sql.size()&& dbmap_dbtype!=DBMAP_MYSQL " );
#endif
                }
            }
            if (update_sql.size()) {
                exec_sql(update_sql);
            }

        }
        if (time(NULL)-last_drop_time>drop_timeout)
        {
            last_drop_time=time(NULL);
            M_LOCK(Mutex);
#ifdef WIN32
            for (map < db_id_type, PTR_getter < T > >::iterator i = container.begin(); i != container.end(); i++)
#else
            for (typeof(container.begin()) i = container.begin(); i != container.end(); i++)
#endif
            {


                if (i->first.id.size() == 0)
                    continue;
                PTR_getter < T > b = i->second;

                if (b) {

                    bool cond;
                    {
                        PTR_getter_lock_read_no_access < T > br(b);
                        cond=br->__last_access_time && (t - br->__last_access_time > drop_timeout)
                             && br->get_ref_count() == 3;
                    }

                    if (cond) {
                        vdel.push_back(i->first);
                    }
                }
            }
            for (unsigned i=0;i<vdel.size();i++)
                container.erase(vdel[i]);
        }
    }
    void make_1st_update(const db_id_type & id)
    {

        PTR_getter < T > b(find_by_id(id));


        if (b) {
//        M_LOCK(Mutex);
            string update_sql;
            {
                PTR_getter_lock_write_no_access < T > br(b);
//            update_sql = br->update_to_db(table_name);
                br->__last_change_time = 0;
                br->__last_update_time = time(NULL);

            }
            update_sql=update_to_db(b,table_name);
            if (update_sql.size() && dbmap_dbtype != DBMAP_MYSQL)
                throw cError(table_name + " update_sql.size()&& dbmap_dbtype!=DBMAP_MYSQL " );
            if (update_sql.size()) {
                exec_sql(update_sql);
            }

        }
    }
    void make_1st_update_no_create(const db_id_type & id)
    {

        PTR_getter < T > b(find_by_id_no_create(id));
        if (b) {
            //       M_LOCK(Mutex);
            string update_sql;
            {

                PTR_getter_lock_write_no_access < T > br(b);
                {
                    br->__last_change_time = 0;
                    br->__last_update_time = time(NULL);
                }
            }
            update_sql = update_to_db(b,table_name);
            if (update_sql.size() && dbmap_dbtype != DBMAP_MYSQL)
                throw cError(table_name + " update_sql.size()&& dbmap_dbtype!=DBMAP_MYSQL " );
            if (update_sql.size()) {
                exec_sql(update_sql);
            }

        }
    }


    size_t __xx_size()
    {
        M_LOCK(Mutex);
        return container.size();
    }

};
#ifndef WIN32
void db_put(const string & tn, const string& key, const string& val, bool erase_old);
string db_get(const string & tn, const string& key, bool erase_old);
void db_erase(const string & tn, const string& key, bool erase_old);
#endif
#endif
