#include "stdafx.h"
#include <string>
#include "db_var.h"
#include "contact_vec.h"
#include "user.h"
#include "DR_types.h"
contact_vec::contact_vec() {}
contact_vec::~contact_vec() {}
int contact_vec::load_from_db(const string & table_name)
{

    unsigned int uid=get_db_row_id().as_int();
    if (uid==0) {
        logErr2("uid==0 || uid>UNREG_BASE (%d) %s",uid,"");
        throw cError("if(get_db_row_id().as_int()==0) || uid>UNREG_BASE");
    }

    st_dbh d;

    vector<string> v=d.dbh->select_1_columnQ((QUERY)"select cuid from contact where uid=?"<<get_db_row_id().as_int());
    for (unsigned i=0;i<v.size();i++)
    {
        DB_id id;
        id.container=atoi(v[i].c_str());
        contact.insert(id);
    }

    return 0;

}
string update_to_db(const PTR_getter<contact_vec> &__U,const string& table_name)
{
    return "";
}
void contact_vec::pack(out_oscar_buffer &b) const
{
    b<<contact;
}
void contact_vec::unpack(oscar_buffer &b)
{
    b>>contact;
}
