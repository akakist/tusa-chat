#ifndef NICK_VEC___H
#define NICK_VEC___H
#include <string>
#include <map>
using namespace std;
#include "user_nick.h"
#include "db_var.h"
class nick_vec : public db_row
{
public:
    string update_to_db(const string& table_name) const;
    int load_from_db(const string & table_name);

    nick_vec();
    ~nick_vec();
    map<unsigned int,user_nick> u_nicks;

    void pack(out_oscar_buffer &b) const;
    void unpack(oscar_buffer &b);
};
extern db_map<nick_vec> nick_vecs;

#endif
