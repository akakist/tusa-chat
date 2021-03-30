#ifndef ignoreSDTATANICK_VEC___H
#define ignoreSDTATANICK_VEC___H
#include <string>
#include <map>
using namespace std;

class ignore_vec : public db_row
{
public:
    string update_to_db(const string& table_name) const;
    int load_from_db(const string & table_name);

    ignore_vec();
    ~ignore_vec();
    set<DB_id> ignore;
    void pack(out_oscar_buffer &b) const;
    void unpack(oscar_buffer &b);

};
extern db_map<ignore_vec> ignore_vecs;

#endif
