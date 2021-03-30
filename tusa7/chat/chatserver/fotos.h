#ifndef photo_323PROFILE__H___
#define photo_323PROFILE__H___
#include <map>
#include <set>
#include <string>
#include "db_var.h"
using namespace std;
struct __foto
{
    string descr,orig_fn,ext;
    unsigned int size;
    unsigned int id;
    DB_id uid;
    map<DB_id,int> rates;
};
class user_fotos: public db_row
{
public:
    map<unsigned int, __foto> fotos;
    unsigned int index2id(unsigned int index) const;
    unsigned int getsize() const;
    void reload$();
    int load_from_db(const string & table_name) const;

    void pack(out_oscar_buffer &b) const;
    void unpack(oscar_buffer &b);
};
extern db_map<user_fotos> users_fotos;
string foto_pn(const DB_id& uid, unsigned int fid,const string &ext);

out_oscar_buffer & operator<<(out_oscar_buffer&b, const __foto &n);
oscar_buffer & operator>>(oscar_buffer&b, __foto &n);

#endif
