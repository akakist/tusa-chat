#include "stdafx.h"
#include <string>

using namespace std;
#include "user.h"
#include "utils.h"
#include "db_var.h"
#include "user_stat.h"
#include "DR_types.h"
user_stat::user_stat()
{

    last_date=0;
    v_count=0;
    m_count=0;
    t_count=0;
    kick_count=0;
    kicked_count=0;


}
user_stat::~user_stat() {}
string update_to_db(const PTR_getter<user_stat>&__U,const string& table_name)
{
    return "";
}

#ifdef __CLAN

int user_stat::load_from_db(const string& table_name)  // 0 - no error
{
    DB_id id;
    id.container=get_db_row_id().as_int();
    string r=clan_data_request(DR_user_stat,id);
    oscar_buffer bb(r.data(),r.size());
    unpack(bb);
    return 0;
}
#else
int user_stat::load_from_db(const string& table_name)  // 0 - no error
{
    unsigned int uid=get_db_row_id().as_int();
    if (uid==0) {
        logErr2("uid==0 || uid>UNREG_BASE (%d) %s",uid,"");
        throw cError("if(get_db_row_id().as_int()==0) || uid>UNREG_BASE");
    }
    st_dbh d;
    vector<string> v=d.dbh->select_1_rowQ((QUERY)
                                          "select UNIX_TIMESTAMP(last_date),last_ip,v_count,m_count,t_count,kick_count,kicked_count,last_pip "
                                          "from ? "
                                          "where refid=?"<<table_name<<get_db_row_id().as_int());
    if (v.size()!=8) {
        return -1;
    }
    last_date=atoi(v[0]);
    last_ip=v[1];
    v_count=atoi(v[2]);
    m_count=atoi(v[3]);
    t_count=atoi(v[4]);
    kick_count=atoi(v[5]);
    kicked_count=atoi(v[6]);
    last_pip=v[7];

    return 0;
}
#endif
void user_stat::pack(out_oscar_buffer &b) const
{
    b<<last_date<<
    last_ip<<
    last_pip<<
    v_count<<
    m_count<<
    t_count<<
    kick_count<<
    kicked_count;

}
void user_stat::unpack(oscar_buffer &b)
{
    b>>last_date>>
    last_ip>>
    last_pip>>
    v_count>>
    m_count>>
    t_count>>
    kick_count>>
    kicked_count;
}
