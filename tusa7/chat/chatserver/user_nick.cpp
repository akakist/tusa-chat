#include "stdafx.h"
#include <string>
using namespace std;
#include "oscar_buffer.h"
#include "DB_id.h"
#include "user_nick.h"
#include "user.h"
#include "utils.h"
user_nick::user_nick(const string &n,unsigned int i, const DB_id &_uid, bool rs, double cst)
{
    name=n;
    id=i;
    uid=_uid;
    ready_to_sale=rs;
    cost=cst;
//    cost=0;
}
user_nick::user_nick()
{
    name="";
    id=user_state::UNDEF;
    uid.container=user_state::UNDEF;
    ready_to_sale=false;
    cost=0;

}
bool NICK_EXISTS(const DB_id& uid,const string &nick)
{


    PGLR(nick_vec, u,nick_vecs.find_by_id(uid));
    string n=str_nick(nick);
    for (map<unsigned int,user_nick>::const_iterator i=u->u_nicks.begin();i!=u->u_nicks.end();i++) {
        if (str_nick(i->second.name)==n) return true;
    }
    return false;

}

user_nick GET_NICK(const user_pair &__U,unsigned int n)
{
    PGLR(nick_vec, u,nick_vecs.find_by_id(user$id(__U)));

    user_nick nn;
    if (u->u_nicks.count(n))
    {
        return u->u_nicks.find(n)->second;
    }
    if (!u->u_nicks.count(n) && u->u_nicks.size())
        return u->u_nicks.begin()->second;

    return nn;
}
user_nick GET_NICK(const user_pair &__U,const string& n)
{
    PGLR(nick_vec, u,nick_vecs.find_by_id(user$id(__U)));

    user_nick nn;
    string N=str_nick(n);
    for (map<unsigned int,user_nick>::const_iterator i=u->u_nicks.begin();i!=u->u_nicks.end();i++)
    {
        if (N==str_nick(i->second.name)) return i->second;
    }
    if (u->u_nicks.size())
        return u->u_nicks.begin()->second;

    return nn;
}
unsigned int GET_CNICK_ID(const user_pair&__U)
{

    {
        PGLR(user_set, u,__U.us);
        return u->last_nick_id;
    }
    return 0;
}

string GET_CNICK(const user_pair&__U)
{

    {
        PGLR(user_set, u,__U.us);
        return u->last_nick;
    }
    return "";
}

string GET_CNICK_DBID(const DB_id& uid)
{
    {
        PGLR(user_set, u,user_sets.find_by_id(uid));
        return u->last_nick;
    }
    return "";
}

bool user_nick::operator!=(const user_nick& a) const
{
    if (a.name!=name)return true;
    if (a.id!=id)return true;
    if (a.uid!=uid)return true;
    return false;
}
out_oscar_buffer & operator<<(out_oscar_buffer&b, const user_nick &n)
{
    b<<n.uid<<n.id<<n.name<<n.ready_to_sale<<n.cost;
    return b;
}
oscar_buffer & operator>>(oscar_buffer&b, user_nick &n)
{
    b>>n.uid>>n.id>>n.name>>n.ready_to_sale>>n.cost;
    return b;
}
int operator < (const user_nick& a, const user_nick& b) {
    return str_nick(a.name)<str_nick(b.name);
}
