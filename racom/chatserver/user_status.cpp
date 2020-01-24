#include "stdafx.h"
#include <string>
using namespace std;
#include "oscar_buffer.h"
#include "user_status.h"
bool operator==(const user_status &s1, const user_status &s2)
{
    if (s1.name != s2.name)return false;
    if (s1.pic != s2.pic)return false;
    if (s1.id != s2.id)return false;
    if (s1.disable_invite != s2.disable_invite)return false;
    if (s1.uniq != s2.uniq)return false;
    return true;
}
bool user_status::operator!=(const user_status& a) const
{
    if (a.name!= name) return true;
    if (a.pic!=pic) return true;
    if (a.id!=id) return true;
    if (a.disable_invite!=disable_invite)return true;
    if (a.uniq!=uniq)return true;
    return false;
}
out_oscar_buffer & operator<<(out_oscar_buffer&b, const user_status &n)
{
    b<<n.name<<n.pic<<n.id<<n.disable_invite<<n.uniq;
    return b;
}

oscar_buffer & operator>>(oscar_buffer&b, user_status &n)
{
    b>>n.name>>n.pic>>n.id>>n.disable_invite>>n.uniq;
    return b;
}
