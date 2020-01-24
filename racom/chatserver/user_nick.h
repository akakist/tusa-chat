#ifndef USER_NICK___H
#define USER_NICK___H
#include <string>

using namespace std;
class user_nick
{
public:
    string name;
    unsigned int id;
    DB_id uid;
    bool ready_to_sale;
    double cost;
    user_nick();


    user_nick(const string &n,unsigned int i, const DB_id&, bool, double);
    bool operator!=(const user_nick&) const;
};
int operator < (const user_nick& a, const user_nick& b);

out_oscar_buffer & operator<<(out_oscar_buffer&b, const user_nick &n);
oscar_buffer & operator>>(oscar_buffer&b, user_nick &n);

struct user_pair;
string GET_CNICK(const user_pair&__U);
string GET_CNICK_DBID(const DB_id& uid);
unsigned int GET_CNICK_ID(const user_pair&__U);
user_nick GET_NICK(const user_pair &__U,unsigned int n);
user_nick GET_NICK(const user_pair &__U,const string & n);
bool NICK_EXISTS(const DB_id& uid,const string &nick);

#endif
