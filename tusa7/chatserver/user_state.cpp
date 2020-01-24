#include "stdafx.h"
#include <string>
using namespace std;
#include "user.h"
#include "utils.h"
#include "db_var.h"
#include "user_stat.h"
bool user_state::operator!=(const user_state& a) const
{
    if (a.channel!=channel)return true;
    if (a.nick!=nick) return true;
    if (a.status!=status) return true;
    return false;
}
user_state::user_state() {
    status.id=UNDEF;
    nick.id=UNDEF;
}


out_oscar_buffer & operator<<(out_oscar_buffer&b, const user_state& n)
{//;
    b<<n.channel<<n.status<<n.nick<<n.voice;
    return b;
}
oscar_buffer & operator>>(oscar_buffer&b, user_state& n)
{//;
    b>>n.channel>>n.status>>n.nick>>n.voice;
    return b;
}

