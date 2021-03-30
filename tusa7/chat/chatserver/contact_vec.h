#ifndef CONTACTSDTATANICK_VEC___H
#define CONTACTSDTATANICK_VEC___H
#include <string>
#include <map>
using namespace std;

class contact_vec : public db_row
{
public:
    string update_to_db(const string& table_name) const;
    int load_from_db(const string & table_name);
    contact_vec();
    ~contact_vec();
    set<DB_id> contact;
    void pack(out_oscar_buffer &b) const;
    void unpack(oscar_buffer &b);
};
extern db_map<contact_vec> contact_vecs;

#endif
