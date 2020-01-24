#include "stdafx.h"
#include <string>
#include "db_var.h"
#include "ignore_vec.h"
#include "user.h"
#include "DR_types.h"
ignore_vec::ignore_vec() {}
ignore_vec::~ignore_vec() {}
#ifdef __CLAN

int ignore_vec::load_from_db(const string & table_name)
{
    DB_id id;
    id.container=get_db_row_id().as_int();
    string r=clan_data_request(DR_ignore_vec,id);
    oscar_buffer bb(r.data(),r.size());
    unpack(bb);
    return 0;
}
#else
int ignore_vec::load_from_db(const string & table_name)
{
    unsigned int uid=get_db_row_id().as_int();
    if (uid==0) {
        logErr2("uid==0 || uid>UNREG_BASE (%d) %s",uid,"");
        throw cError("if(get_db_row_id().as_int()==0) || uid>UNREG_BASE");
    }

    st_dbh d;

    vector<string> v=d.dbh->select_1_columnQ((QUERY)"select cuid from ignores where uid=?"<<get_db_row_id().as_int());
    for (unsigned i=0;i<v.size();i++)
    {
        DB_id id;
        id.container=atoi(v[i]);
        ignore.insert(id);
    }
    return 0;
}
#endif
string update_to_db(const PTR_getter<ignore_vec> &__U,const string& table_name)
{
    return "";
}
void ignore_vec::pack(out_oscar_buffer &b) const
{
    b<<ignore;
}
void ignore_vec::unpack(oscar_buffer &b)
{
    b>>ignore;
}
