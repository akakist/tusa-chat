#ifndef DB_VAR_MAPSBX_BANADMIN_H__
#define DB_VAR_MAPSBX_BANADMIN_H__
#include <vector>
#include <string>
#include "str_lib.h"
#include "_QUERY.h"
#include "PTR.h"
#include <time.h>
#include "mysql_extens.h"
class __dbmaps
{
private:
    map<string/*classname*/, map<string/*path*/,db_map_base*> > container;
    _mutex  Mutex;
    string full_path(const string & classname, const string & path);
public:
    __dbmaps():Mutex("__dbmaps::Mutex") {}
    void purge(time_t update_timeout, time_t drop_timeout);
    template <class T>
    PTR_getter < T > find(const db_id_type & id, const string & classname, const string & path)
    {
        db_map < T > *db;
        {
            M_LOCK(Mutex);
            if (container[classname].count(path)) {
                db = (db_map < T > *)container[classname][path];
            }
            else {
                db = new db_map < T > (full_path(classname,path), DBMAP_GDBM, DBMAP_REFID);
                container[classname][path] = db;
            }
        }
        return db->find_by_id(id);
    }
    template <class T>
    unsigned int count(const db_id_type & id, const string & classname, const string & path)
    {
        db_map < T > *db;
        {
            M_LOCK(Mutex);
            if (container[classname].count(path)) {
                db = (db_map < T > *)container[classname][path];
            }
            else {
                db = new db_map < T > (full_path(classname,path), DBMAP_GDBM, DBMAP_REFID);
                container[classname][path] = db;
            }
        }
        return db->count(id);
    }
};


#endif