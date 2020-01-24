#ifndef USER_PROFILE___H
#define USER_PROFILE___H

#include <string>
#include <map>
using namespace std;

class user_profile: public db_row
{
public:
    string update_to_db(const string& table_name) const;
    int load_from_db(const string & table_name) ;
    user_profile();
    ~user_profile();

    string icq;
    string city;
    string info;
    string homepage;
    string tel;
    string b_day;
    int b_mon;
    string b_year;
    string fname;
    string lname;
    string email;

    time_t reg_date;

    unsigned int level;

    string login;
    string pass;

    int vote_balls;
    int db_privileges;/*orig privileges in database*/

    map<unsigned int,user_status> status;
private:
    int gender;
public:
    void set_gender(unsigned char g);
    unsigned char get_gender() const;

    void pack(out_oscar_buffer &b) const;
    void unpack(oscar_buffer &b);

};
extern db_map<user_profile> user_profiles;

#endif
