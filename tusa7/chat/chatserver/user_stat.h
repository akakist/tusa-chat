#ifndef USER_STAT__HHH
#define USER_STAT__HHH
#include <string>

class user_stat: public db_row
{
public:
    string update_to_db(const string& table_name) const;
    int load_from_db(const string & table_name);
    user_stat();
    ~user_stat();

    time_t last_date;
    string last_ip;
    string last_pip;
    int v_count;
    int m_count;
    time_t t_count;
    unsigned int kick_count;
    unsigned int kicked_count;
    void pack(out_oscar_buffer &b) const;
    void unpack(oscar_buffer &b);

};


extern db_map<user_stat> user_stats;


#endif
